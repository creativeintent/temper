//-----------------------------------------------------------------------------
// Flags       : clang-format auto
// Project     : VST SDK
//
// Category    : EditorHost
// Filename    : public.sdk/samples/vst/editorhost/source/platform/linux/runloop.cpp
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
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "public.sdk/samples/vst/editorhost/source/platform/linux/runloop.h"
#include <chrono>
#include <iostream>

//------------------------------------------------------------------------
namespace Steinberg {
namespace Vst {
namespace EditorHost {
namespace {

//------------------------------------------------------------------------
int pause (int milliSeconds)
{
	struct timeval timeOut;
	if (milliSeconds > 0)
	{
		timeOut.tv_usec = (milliSeconds % (unsigned long)1000) * 1000;
		timeOut.tv_sec = milliSeconds / (unsigned long)1000;

		select (0, nullptr, nullptr, nullptr, &timeOut);
	}
	return (milliSeconds > 0 ? milliSeconds : 0);
}

//------------------------------------------------------------------------
static constexpr int kMinEventLoopRate = 16; // 60Hz
static RunLoop::IdleID idleIdCounter {};

//------------------------------------------------------------------------
} // anonymous

//------------------------------------------------------------------------
RunLoop& RunLoop::instance ()
{
	static RunLoop gInstance;
	return gInstance;
}

//------------------------------------------------------------------------
void RunLoop::setDisplay (Display* display)
{
	this->display = display;
}

//------------------------------------------------------------------------
void RunLoop::registerWindow (XID window, const EventCallback& callback)
{
	map.emplace (window, callback);
}

//------------------------------------------------------------------------
void RunLoop::unregisterWindow (XID window)
{
	auto it = map.find (window);
	if (it == map.end ())
		return;
	map.erase (it);
}

//------------------------------------------------------------------------
auto RunLoop::registerIdle (const IdleCallback& callback) -> IdleID
{
	auto id = ++idleIdCounter;
	idle.emplace_back (id, callback);
	return id;
}

//------------------------------------------------------------------------
void RunLoop::unregisterIdle (IdleID id)
{
	for (auto it = idle.begin (); it != idle.end (); ++it)
	{
		if (it->first == id)
		{
			idle.erase (it);
			break;
		}
	}
}

//------------------------------------------------------------------------
void RunLoop::start ()
{
	using namespace std::chrono;
	using clock = high_resolution_clock;

	running = true;
	XEvent event {};
	while (running && !map.empty ())
	{
		auto count = XPending (display);
		auto startTime = clock::now ();
		for (auto i = 0; i < count; ++i)
		{
			XNextEvent (display, &event);
			auto it = map.find (event.xany.window);
			if (it != map.end ())
			{
				it->second (event);
				if (event.type == DestroyNotify)
				{
					map.erase (it);
				}
			}
			else
			{
				XPutBackEvent (display, &event);
				break;
			}
		}
		for (auto& entry : idle)
		{
			entry.second ();
		}

		std::cout.flush ();

		// prevent running faster than a given rate
		auto duration = duration_cast<milliseconds> (clock::now () - startTime).count ();
		if (duration < kMinEventLoopRate)
			pause (kMinEventLoopRate - duration);
	}
}

//------------------------------------------------------------------------
void RunLoop::stop ()
{
	running = false;
}

//------------------------------------------------------------------------
} // EditorHost
} // Vst
} // Steinberg
