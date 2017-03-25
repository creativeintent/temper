//-----------------------------------------------------------------------------
// Project     : VST SDK
// Version     : 3.6.6
//
// Category    : Examples
// Filename    : public.sdk/samples/vst/hostchecker/source/hostchecker.h
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

#include "public.sdk/source/vst/vsteditcontroller.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "eventlogdatabrowsersource.h"

#include "base/source/fstring.h"
#include "base/source/tdictionary.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "hostcheck.h"
#include "logevents.h"
#include "pluginterfaces/vst/ivstchannelcontextinfo.h"
#include "pluginterfaces/vst/ivstrepresentation.h"
#include "pluginterfaces/vst/ivstnoteexpression.h"
#include "pluginterfaces/vst/ivstprefetchablesupport.h"

namespace Steinberg {
namespace Vst {

enum
{
	kParam1Tag = 1000,
	kParam2Tag,
	kLatencyTag,
	kBypassTag
};

//-----------------------------------------------------------------------------
class HostCheckerController : public EditControllerEx1,
							  public VSTGUI::VST3EditorDelegate,
							  public ChannelContext::IInfoListener,
							  public IXmlRepresentationController,
							  public IMidiMapping,
							  public INoteExpressionController
{
public:
	tresult PLUGIN_API initialize (FUnknown* context) override;
	tresult PLUGIN_API terminate () override;
	
	tresult PLUGIN_API setComponentState (IBStream* state) override;
	tresult PLUGIN_API getUnitByBus (MediaType type, BusDirection dir, int32 busIndex,
									 int32 channel, UnitID& unitId /*out*/) override;
	tresult PLUGIN_API setComponentHandler (IComponentHandler* handler) override;
	int32 PLUGIN_API getUnitCount () override;
	tresult PLUGIN_API setParamNormalized (ParamID tag, ParamValue value) override;
	
	tresult beginEdit (ParamID tag) override;
	tresult endEdit (ParamID tag) override;

	IPlugView* PLUGIN_API createView (FIDString name) override;
	tresult PLUGIN_API notify (IMessage* message) override;
	tresult PLUGIN_API connect (IConnectionPoint* other) override;

	VSTGUI::CView* createCustomView (VSTGUI::UTF8StringPtr name,
									 const VSTGUI::UIAttributes& attributes,
									 const VSTGUI::IUIDescription* description,
									 VSTGUI::VST3Editor* editor) override;

	//---from IEditController2-------
	tresult PLUGIN_API setKnobMode (KnobMode mode) override;
	tresult PLUGIN_API openHelp (TBool /*onlyCheck*/) override;
	tresult PLUGIN_API openAboutBox (TBool /*onlyCheck*/) override;

	//---ChannelContext::IInfoListener-------
	tresult PLUGIN_API setChannelContextInfos (IAttributeList* list) override;

	//---IXmlRepresentationController--------
	tresult PLUGIN_API getXmlRepresentationStream (RepresentationInfo& info /*in*/,
														   IBStream* stream /*out*/) override;

	//---IMidiMapping---------------------------
	tresult PLUGIN_API getMidiControllerAssignment (int32 busIndex, int16 channel,
															CtrlNumber midiControllerNumber,
															ParamID& id /*out*/) override;

	//---INoteExpressionController----------------------
	int32 PLUGIN_API getNoteExpressionCount (int32 busIndex, int16 channel) override;
	tresult PLUGIN_API getNoteExpressionInfo (int32 busIndex, int16 channel,
													  int32 noteExpressionIndex,
													  NoteExpressionTypeInfo& info /*out*/) override;
	tresult PLUGIN_API getNoteExpressionStringByValue (
		int32 busIndex, int16 channel, NoteExpressionTypeID id,
		NoteExpressionValue valueNormalized /*in*/, String128 string /*out*/) override;
	tresult PLUGIN_API getNoteExpressionValueByString (
		int32 busIndex, int16 channel, NoteExpressionTypeID id, const TChar* string /*in*/,
		NoteExpressionValue& valueNormalized /*out*/) override;

	DEFINE_INTERFACES
		DEF_INTERFACE (IMidiMapping)
		DEF_INTERFACE (IXmlRepresentationController)
		DEF_INTERFACE (ChannelContext::IInfoListener)
		DEF_INTERFACE (INoteExpressionController)
	END_DEFINE_INTERFACES (EditControllerEx1)
	REFCOUNT_METHODS (EditControllerEx1)

	static FUnknown* createInstance (void*)
	{
		return (IEditController*)new HostCheckerController ();
	}
	static FUID cid;

protected:
	void addFeatureLog (int32 iD);

	OwningPointer<CDataBrowser> mDataBrowser;
	OwningPointer<EventLogDataBrowserSource> mDataSource;
	
	bool mLatencyInEdit = false;
	ParamValue mWantedLatency = 0.0;
};

//------------------------------------------------------------------------
} // namespace Vst
} // namespace Steinberg
