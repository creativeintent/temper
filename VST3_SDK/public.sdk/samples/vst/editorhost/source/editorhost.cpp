//-----------------------------------------------------------------------------
// Flags       : clang-format auto
// Project     : VST SDK
//
// Category    : EditorHost
// Filename    : public.sdk/samples/vst/editorhost/source/editorhost.cpp
// Created by  : Steinberg 09.2016
// Description : Example of opening a plug-in editor
//
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2017, Steinberg Media Technologies GmbH, All Rights Reserved
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

#include "public.sdk/samples/vst/editorhost/source/editorhost.h"
#include "public.sdk/samples/vst/editorhost/source/platform/appinit.h"
#include "public.sdk/source/vst/hosting/hostclasses.h"
#include "base/source/fcommandline.h"
#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/gui/iplugview.h"
#include "pluginterfaces/gui/iplugviewcontentscalesupport.h"
#include "pluginterfaces/vst/ivstaudioprocessor.h"
#include "pluginterfaces/vst/ivsteditcontroller.h"
#include "pluginterfaces/vst/vsttypes.h"
#include <cstdio>
#include <iostream>

//------------------------------------------------------------------------
namespace Steinberg {
FUnknown* gStandardPluginContext = new Vst::HostApplication ();

namespace Vst {
namespace EditorHost {

static AppInit gInit (std::make_unique<App> ());

//------------------------------------------------------------------------
class WindowController : public IWindowController, public IPlugFrame, public IPlugFrameIdle
{
public:
	WindowController (const IPtr<IPlugView>& plugView);
	~WindowController () noexcept override;

	void onShow (IWindow& w) override;
	void onClose (IWindow& w) override;
	void onResize (IWindow& w, Size newSize) override;
	Size constrainSize (IWindow& w, Size requestedSize) override;
	void onContentScaleFactorChanged (IWindow& window, float newScaleFactor) override;
	void onIdle () override;

	// IPlugFrame
	tresult PLUGIN_API resizeView (IPlugView* view, ViewRect* newSize) override;

	// IPlugFrameIdle
	tresult PLUGIN_API addIdleHandler (IPlugViewIdleHandler* handler) override;
	tresult PLUGIN_API removeIdleHandler (IPlugViewIdleHandler* handler) override;

private:
	using IdleHandlers = std::vector<IPlugViewIdleHandler*>;

	tresult PLUGIN_API queryInterface (const TUID _iid, void** obj) override
	{
		if (FUnknownPrivate::iidEqual (_iid, IPlugFrameIdle::iid))
		{
			*obj = static_cast<IPlugFrameIdle*> (this);
			return kResultTrue;
		}
		return kNoInterface;
	}
	uint32 PLUGIN_API addRef () override { return 1000; }
	uint32 PLUGIN_API release () override { return 1000; }

	IPtr<IPlugView> plugView;
	IWindow* window {nullptr};
	bool resizeViewRecursionGard {false};
	IdleHandlers idleHandlers;
};

//------------------------------------------------------------------------
class ComponentHandler : public IComponentHandler
{
public:
	tresult PLUGIN_API beginEdit (ParamID id) override { return kNotImplemented; }
	tresult PLUGIN_API performEdit (ParamID id, ParamValue valueNormalized) override
	{
		return kNotImplemented;
	}
	tresult PLUGIN_API endEdit (ParamID id) override { return kNotImplemented; }
	tresult PLUGIN_API restartComponent (int32 flags) override { return kNotImplemented; }

private:
	tresult PLUGIN_API queryInterface (const TUID _iid, void** obj) override
	{
		return kNoInterface;
	}
	uint32 PLUGIN_API addRef () override { return 1000; }
	uint32 PLUGIN_API release () override { return 1000; }
};

static ComponentHandler gComponentHandler;

//------------------------------------------------------------------------
App::~App () noexcept
{
}

//------------------------------------------------------------------------
void App::openEditor (const std::string& path, VST3::Optional<VST3::UID> effectID, uint32 flags)
{
	std::string error;
	module = VST3::Hosting::Module::create (path, error);
	if (!module)
	{
		std::string reason = "Could not create Module for file:";
		reason += path;
		reason += "\nError: ";
		reason += error;
		IPlatform::instance ().kill (-1, reason);
	}
	auto factory = module->getFactory ();
	for (auto& classInfo : factory.classInfos ())
	{
		if (classInfo.category () == kVstAudioEffectClass)
		{
			if (effectID)
			{
				if (*effectID != classInfo.ID ())
					continue;
			}
			plugProvider = owned (new PlugProvider (factory, classInfo, true));
			break;
		}
	}
	if (!plugProvider)
	{
		std::string error;
		if (effectID)
			error =
			    "No VST3 Audio Module Class with UID " + effectID->toString () + " found in file ";
		else
			error = "No VST3 Audio Module Class found in file ";
		error += path;
		IPlatform::instance ().kill (-1, error);
	}

	auto editController = plugProvider->getController ();
	if (!editController)
	{
		IPlatform::instance ().kill (
		    -1,
		    std::string ("No EditController found (needed for allowing editor) in file ") + path);
	}
	editController->release (); // plugProvider does an addRef

	if (flags & kSetComponentHandler)
		editController->setComponentHandler (&gComponentHandler);

	createViewAndShow (editController);

	if (flags & kSecondWindow)
		createViewAndShow (editController);
}

//------------------------------------------------------------------------
void App::createViewAndShow (IEditController* controller)
{
	auto view = owned (controller->createView (ViewType::kEditor));
	if (!view)
	{
		IPlatform::instance ().kill (-1, "EditController does not provide its own editor");
	}

	ViewRect plugViewSize {};
	auto result = view->getSize (&plugViewSize);
	if (result != kResultTrue)
	{
		IPlatform::instance ().kill (-1, "Could not get editor view size");
	}

	auto viewRect = ViewRectToRect (plugViewSize);

	auto window = IPlatform::instance ().createWindow ("Editor", viewRect.size,
	                                                   view->canResize () == kResultTrue,
	                                                   std::make_shared<WindowController> (view));
	if (!window)
	{
		IPlatform::instance ().kill (-1, "Could not create window");
	}

	window->show ();
}

//------------------------------------------------------------------------
void App::init (const std::vector<std::string>& cmdArgs)
{
	if (cmdArgs.empty ())
	{
		auto helpText = R"(
usage: EditorHost [options] pluginPath

options:

--componentHandler
	set optional component handler on edit controller

--secondWindow
	create a second window

--uid UID
	use effect class with unique class ID==UID
)";

		IPlatform::instance ().kill (0, helpText);
	}

	VST3::Optional<VST3::UID> uid;
	uint32 flags {};
	for (auto it = cmdArgs.begin (), end = cmdArgs.end (); it != end; ++it)
	{
		if (*it == "--componentHandler")
			flags |= kSetComponentHandler;
		else if (*it == "--secondWindow")
			flags |= kSecondWindow;
		else if (*it == "--uid")
		{
			if (++it != end)
				uid = VST3::UID::fromString (*it);
			if (!uid)
				IPlatform::instance ().kill (-1, "wrong argument to --uid");
		}
	}

	openEditor (cmdArgs.back (), std::move (uid), flags);
}

//------------------------------------------------------------------------
WindowController::WindowController (const IPtr<IPlugView>& plugView) : plugView (plugView)
{
}

//------------------------------------------------------------------------
WindowController::~WindowController () noexcept
{
}

//------------------------------------------------------------------------
void WindowController::onShow (IWindow& w)
{
	window = &w;
	if (!plugView)
		return;

	auto platformWindow = window->getNativePlatformWindow ();
	if (plugView->isPlatformTypeSupported (platformWindow.type) != kResultTrue)
	{
		IPlatform::instance ().kill (-1, std::string ("PlugView does not support platform type:") +
		                                     platformWindow.type);
	}

	plugView->setFrame (this);

	if (plugView->attached (platformWindow.ptr, platformWindow.type) != kResultTrue)
	{
		IPlatform::instance ().kill (-1, "Attaching PlugView failed");
	}
}

//------------------------------------------------------------------------
void WindowController::onClose (IWindow& w)
{
	if (plugView)
	{
		plugView->setFrame (nullptr);
		if (plugView->removed () != kResultTrue)
		{
			IPlatform::instance ().kill (-1, "Removing PlugView failed");
		}
	}
	window = nullptr;

	// TODO maybe quit only when the last window is closed
	IPlatform::instance ().quit ();
}

//------------------------------------------------------------------------
void WindowController::onResize (IWindow& w, Size newSize)
{
	ViewRect r {};
	r.right = newSize.width;
	r.bottom = newSize.height;
	if (plugView)
		plugView->onSize (&r);
}

//------------------------------------------------------------------------
Size WindowController::constrainSize (IWindow& w, Size requestedSize)
{
	ViewRect r {};
	r.right = requestedSize.width;
	r.bottom = requestedSize.height;
	if (plugView && plugView->checkSizeConstraint (&r) != kResultTrue)
	{
		plugView->getSize (&r);
	}
	requestedSize.width = r.right - r.left;
	requestedSize.height = r.bottom - r.top;
	return requestedSize;
}

//------------------------------------------------------------------------
void WindowController::onContentScaleFactorChanged (IWindow& window, float newScaleFactor)
{
	FUnknownPtr<IPlugViewContentScaleSupport> css (plugView);
	if (css)
	{
		css->setContentScaleFactor (newScaleFactor);
	}
}

//------------------------------------------------------------------------
tresult PLUGIN_API WindowController::resizeView (IPlugView* view, ViewRect* newSize)
{
	if (newSize == nullptr || view == nullptr || view != plugView)
		return kInvalidArgument;
	if (!window)
		return kInternalError;
	if (resizeViewRecursionGard)
		return kResultFalse;
	resizeViewRecursionGard = true;
	Size size {newSize->right - newSize->left, newSize->bottom - newSize->top};
	window->resize (size);
	resizeViewRecursionGard = false;
	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API WindowController::addIdleHandler (IPlugViewIdleHandler* handler)
{
	auto pos = std::find (idleHandlers.begin (), idleHandlers.end (), handler);
	if (pos != idleHandlers.end ())
		return kInvalidArgument; // already added
	idleHandlers.emplace_back (handler);
	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API WindowController::removeIdleHandler (IPlugViewIdleHandler* handler)
{
	auto pos = std::find (idleHandlers.begin (), idleHandlers.end (), handler);
	if (pos == idleHandlers.end ())
		return kInvalidArgument;
	idleHandlers.erase (pos);
	return kResultTrue;
}

//------------------------------------------------------------------------
void WindowController::onIdle ()
{
	for (auto& obj : idleHandlers)
		obj->onPlugViewIdle ();
}

//------------------------------------------------------------------------
} // EditorHost
} // Vst
} // Steinberg
