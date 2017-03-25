//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.6
//
// Category    : Examples
// Filename    : public.sdk/samples/vst/hostchecker/source/hostcheckerprocessor.cpp
// Created by  : Steinberg, 04/2012
// Description :
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2015, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this
//     software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "hostcheckerprocessor.h"
#include "hostcheckercontroller.h"

#include "pluginterfaces/base/ustring.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioprocessoralgo.h"

namespace Steinberg {
namespace Vst {

#define kMaxLatency 8192

//-----------------------------------------------------------------------------
FUID HostCheckerProcessor::cid (0x23FC190E, 0x02DD4499, 0xA8D2230E, 0x50617DA3);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
HostCheckerProcessor::HostCheckerProcessor ()
{
	mLatency = 256;

	setControllerClass (HostCheckerController::cid);
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::initialize (FUnknown* context)
{
	tresult result = AudioEffect::initialize (context);
	if (result == kResultOk)
	{
		addAudioInput (USTRING ("Audio Input"), SpeakerArr::kStereo);
		addAudioOutput (USTRING ("Audio Output"), SpeakerArr::kStereo);
		addEventInput (USTRING ("Event Input"), 1);

		mHostCheck.setComponent (this);
	}
	return result;
}

//------------------------------------------------------------------------
void HostCheckerProcessor::addLogEvent (Steinberg::int32 logId)
{
	mHostCheck.getEventLogger ().addLogEvent (logId);
}

//-----------------------------------------------------------------------------
void HostCheckerProcessor::sendLogEventMessage (const LogEvent& logEvent)
{
	IMessage* message = allocateMessage ();
	FReleaser msgReleaser (message);
	if (message)
	{
		message->setMessageID ("LogEvent");
		IAttributeList* attributes = message->getAttributes ();
		if (attributes)
		{
			ASSERT (logEvent.id >= 0);
			attributes->setInt ("ID", logEvent.id);
			attributes->setInt ("Count", logEvent.count);
			sendMessage (message);
		}
	}
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::setAudioPresentationLatencySamples (
    BusDirection dir, int32 busIndex, uint32 latencyInSamples)
{
	addLogEvent (kLogIdAudioPresentationLatencySamplesSupported);
	return kResultTrue;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::getPrefetchableSupport (
    PrefetchableSupport& prefetchable /*out*/)
{
	addLogEvent (kLogIdIPrefetchableSupportSupported);
	prefetchable = kIsYetPrefetchable;
	return kResultTrue;
}

//-----------------------------------------------------------------------------
void HostCheckerProcessor::informLatencyChanged ()
{
	IMessage* newMsg = allocateMessage ();
	if (newMsg)
	{
		newMsg->setMessageID ("Latency");
		Steinberg::Vst::IAttributeList* attr = newMsg->getAttributes ();
		if (attr)
		{
			attr->setFloat ("Value", mWantedLatency);
		}
		sendMessage (newMsg);
	}
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::process (ProcessData& data)
{
	mHostCheck.validate (data);

	Algo::foreach (data.inputParameterChanges, [&] (IParamValueQueue& paramQueue) {
		Algo::foreachLast (paramQueue, [&] (ParamID id, int32 sampleOffset, ParamValue value) {
			if (id == kBypassTag)
			{
				mBypassProcessor.setActive (value > 0);
			}
			else if (id == kLatencyTag)
			{
				mWantedLatency = value * kMaxLatency;
				informLatencyChanged ();
			}
			else if (id == kParam1Tag)
			{
			}
			else if (id == kParam2Tag)
			{
				mGeneratePeaks = value > 0;
			}
		});
	});

	if (mBypassProcessor.isActive ())
	{
		mBypassProcessor.process (data);
	}
	else if (data.numSamples && data.numOutputs)
	{
		Algo::clear32 (data.outputs, data.numSamples);

		if (mGeneratePeaks)
		{
			for (int32 i = 0; i < data.outputs[0].numChannels; i++)
			{
				data.outputs[0].channelBuffers32[i][0] = mLastBlockMarkerValue;
			}
			mLastBlockMarkerValue = -mLastBlockMarkerValue;

			data.outputs[0].silenceFlags = 0x0;

			const float kMaxNotesToDisplay = 5.f;

			// check event
			Algo::foreach (data.inputEvents, [&] (Event& event) {
				switch (event.type)
				{
					case Event::kNoteOnEvent:
						mNumNoteOns++;
						data.outputs[0].channelBuffers32[0][event.sampleOffset] =
						    mNumNoteOns / kMaxNotesToDisplay;
						break;
					case Event::kNoteOffEvent:
						data.outputs[0].channelBuffers32[1][event.sampleOffset] =
						    -mNumNoteOns / kMaxNotesToDisplay;
						mNumNoteOns--;
						break;
					default: break;
				}
			});
		}
		else
			data.outputs[0].silenceFlags = 0x3;
	}

	const EventLogger::Codes& errors = mHostCheck.getEventLogs ();
	EventLogger::Codes::const_iterator iter = errors.begin ();
	while (iter != errors.end ())
	{
		if ((*iter).fromProcessor)
			sendLogEventMessage ((*iter));
		++iter;
	}
	return kResultOk;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::setupProcessing (ProcessSetup& setup)
{
	mHostCheck.setProcessSetup (setup);
	return AudioEffect::setupProcessing (setup);
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::setActive (TBool state)
{
	if (!state)
		mBypassProcessor.reset ();
	else
	{
		mLatency = mWantedLatency;

		// prepare bypass
		mBypassProcessor.setup (*this, processSetup, mLatency);
	}
	mLastBlockMarkerValue = 0.5f;
	mNumNoteOns = 0;

	return AudioEffect::setActive (state);
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::notify (IMessage* message)
{
	if (!message)
		return kInvalidArgument;

	if (FIDStringsEqual (message->getMessageID (), "Parameter"))
	{
		int64 paramId = -1;
		if (message->getAttributes ()->getInt ("ID", paramId) == kResultOk)
		{
			mHostCheck.addParameter (paramId);
		}
	}

	return kResultOk;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::setState (IBStream* state)
{
	FUnknownPtr<IStreamAttributes> stream (state);
	if (stream)
	{
		IAttributeList* list = stream->getAttributes ();
		if (list)
		{
			addLogEvent (kLogIdIAttributeListInSetStateSupported);
		}
	}

	float saved = 0.f;
	if (state->read (&saved, sizeof (float)) != kResultOk)
	{
		return kResultFalse;
	}

#if BYTEORDER == kBigEndian
	SWAP_32 (toSave)
#endif
	if (saved != 12345.67f)
	{
		ASSERT (false)
	}

	uint32 latency = mLatency;
	if (state->read (&latency, sizeof (uint32)) == kResultOk)
	{
#if BYTEORDER == kBigEndian
		SWAP_32 (latency)
#endif
	}

	uint32 bypass;
	if (state->read (&bypass, sizeof (uint32)) == kResultOk)
	{
#if BYTEORDER == kBigEndian
		SWAP_32 (bypass)
#endif
		mBypassProcessor.setActive (bypass > 0);
	}

	if (latency != mLatency)
	{
		mLatency = latency;
		informLatencyChanged ();
	}

	return kResultOk;
}

//-----------------------------------------------------------------------------
tresult PLUGIN_API HostCheckerProcessor::getState (IBStream* state)
{
	if (!state)
		return kResultFalse;

	float toSave = 12345.67f;
	uint32 latency = mLatency;
	uint32 bypass = mBypassProcessor.isActive () ? 1 : 0;

#if BYTEORDER == kBigEndian
	SWAP_32 (toSave);
	SWAP_32 (latency);
	SWAP_32 (bypass);
#endif

	state->write (&toSave, sizeof (float));
	state->write (&latency, sizeof (uint32));
	state->write (&bypass, sizeof (uint32));

	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
