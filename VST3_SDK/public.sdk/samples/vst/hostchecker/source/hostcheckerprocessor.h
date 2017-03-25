//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.6
//
// Category    : Examples
// Filename    : public.sdk/samples/vst/hostchecker/source/hostcheckerprocessor.h
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

#pragma once

#include "hostcheck.h"
#include "logevents.h"

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vstbypassprocessor.h"
#include "pluginterfaces/vst/ivstprefetchablesupport.h"

namespace Steinberg {
namespace Vst {

//-----------------------------------------------------------------------------
class HostCheckerProcessor : public AudioEffect,
                             public IAudioPresentationLatency,
                             public IPrefetchableSupport
{
public:
	HostCheckerProcessor ();

	tresult PLUGIN_API initialize (FUnknown* context) override;
	tresult PLUGIN_API process (ProcessData& data) override;
	tresult PLUGIN_API setupProcessing (ProcessSetup& setup) override;
	tresult PLUGIN_API setActive (TBool state) override;
	tresult PLUGIN_API notify (IMessage* message) override;
	uint32 PLUGIN_API getTailSamples () override { return mLatency; }

	tresult PLUGIN_API setState (IBStream* state) override;
	tresult PLUGIN_API getState (IBStream* state) override;

	static FUnknown* createInstance (void*)
	{
		return (IAudioProcessor*)new HostCheckerProcessor ();
	}
	void sendLogEventMessage (const LogEvent& logEvent);

	//---IAudioPresentationLatency------------
	virtual tresult PLUGIN_API setAudioPresentationLatencySamples (
	    BusDirection dir, int32 busIndex, uint32 latencyInSamples) override;

	//---IPrefetchableSupport------------------------------
	virtual tresult PLUGIN_API getPrefetchableSupport (
	    PrefetchableSupport& prefetchable /*out*/) override;

	DEFINE_INTERFACES
		DEF_INTERFACE (IAudioPresentationLatency)
		DEF_INTERFACE (IPrefetchableSupport)
	END_DEFINE_INTERFACES (AudioEffect)
	REFCOUNT_METHODS (AudioEffect)

	static FUID cid;

protected:
	void addLogEvent (Steinberg::int32 logId);
	void informLatencyChanged ();

	HostCheck mHostCheck;

	BypassProcessor mBypassProcessor;
	float mLastBlockMarkerValue = 0.5;

	int32 mNumNoteOns = 0;
	uint32 mLatency = 0;
	uint32 mWantedLatency = 0;
	bool mGeneratePeaks = false;
	bool mBypass = false;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
