/* ------------------------------------------------------------
name: "temper"
Code generated with Faust 2.79.3 (https://faust.grame.fr)
Compilation options: -a minimal-effect.cpp -lang cpp -ct 1 -cn TemperDsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __TemperDsp_H__
#define  __TemperDsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-effect.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/
 
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

using std::max;
using std::min;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS TemperDsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float TemperDsp_faustpower2_f(float value) {
	return value * value;
}

class TemperDsp : public ::dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	float fRec0[2];
	FAUSTFLOAT fHslider1;
	float fRec4[2];
	FAUSTFLOAT fHslider2;
	float fRec5[2];
	FAUSTFLOAT fHslider3;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fRec6[2];
	float fRec7[3];
	FAUSTFLOAT fHslider4;
	float fRec8[2];
	FAUSTFLOAT fHslider5;
	float fRec9[2];
	float fConst2;
	float fConst3;
	float fRec10[2];
	FAUSTFLOAT fHslider6;
	float fRec11[2];
	float fVec0[2];
	float fRec3[2];
	float fRec2[2];
	float fRec1[2];
	
 public:
	TemperDsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.2.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-a minimal-effect.cpp -lang cpp -ct 1 -cn TemperDsp -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("filename", "temper.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("name", "temper");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 3.1415927f / fConst0;
		fConst2 = std::exp(-(25.0f / fConst0));
		fConst3 = 1.0f - fConst2;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(-3.0f);
		fHslider1 = FAUSTFLOAT(1.0f);
		fHslider2 = FAUSTFLOAT(1.0f);
		fHslider3 = FAUSTFLOAT(2e+04f);
		fHslider4 = FAUSTFLOAT(-6e+01f);
		fHslider5 = FAUSTFLOAT(4.0f);
		fHslider6 = FAUSTFLOAT(1.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec4[l1] = 0.0f;
		}
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			fRec5[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		for (int l4 = 0; l4 < 3; l4 = l4 + 1) {
			fRec7[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec8[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec9[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec10[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec11[l8] = 0.0f;
		}
		for (int l9 = 0; l9 < 2; l9 = l9 + 1) {
			fVec0[l9] = 0.0f;
		}
		for (int l10 = 0; l10 < 2; l10 = l10 + 1) {
			fRec3[l10] = 0.0f;
		}
		for (int l11 = 0; l11 < 2; l11 = l11 + 1) {
			fRec2[l11] = 0.0f;
		}
		for (int l12 = 0; l12 < 2; l12 = l12 + 1) {
			fRec1[l12] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual TemperDsp* clone() {
		return new TemperDsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("temper");
		ui_interface->addHorizontalSlider("Curve", &fHslider1, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.1f), FAUSTFLOAT(4.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Cutoff", &fHslider3, FAUSTFLOAT(2e+04f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(2e+04f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("Drive", &fHslider5, FAUSTFLOAT(4.0f), FAUSTFLOAT(-1e+01f), FAUSTFLOAT(1e+01f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Feedback", &fHslider4, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(-6e+01f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("Level", &fHslider0, FAUSTFLOAT(-3.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("Resonance", &fHslider2, FAUSTFLOAT(1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(8.0f), FAUSTFLOAT(0.001f));
		ui_interface->addHorizontalSlider("Saturation", &fHslider6, FAUSTFLOAT(1.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.001f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = 0.005f * std::pow(1e+01f, 0.05f * float(fHslider0));
		float fSlow1 = 0.005f * float(fHslider1);
		float fSlow2 = 0.005f * float(fHslider2);
		float fSlow3 = 0.005f / std::tan(fConst1 * float(fHslider3));
		float fSlow4 = 0.005f * std::pow(1e+01f, 0.05f * float(fHslider4));
		float fSlow5 = 0.005f * float(fHslider5);
		float fSlow6 = 0.005f * float(fHslider6);
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow0 + 0.995f * fRec0[1];
			fRec4[0] = fSlow1 + 0.995f * fRec4[1];
			float fTemp0 = TemperDsp_faustpower2_f(fRec4[0]);
			fRec5[0] = fSlow2 + 0.995f * fRec5[1];
			float fTemp1 = 1.0f / fRec5[0];
			fRec6[0] = fSlow3 + 0.995f * fRec6[1];
			float fTemp2 = fRec6[0] * (fRec6[0] + fTemp1) + 1.0f;
			fRec7[0] = float(input0[i0]) - (fRec7[2] * (fRec6[0] * (fRec6[0] - fTemp1) + 1.0f) + 2.0f * fRec7[1] * (1.0f - TemperDsp_faustpower2_f(fRec6[0]))) / fTemp2;
			fRec8[0] = fSlow4 + 0.995f * fRec8[1];
			float fTemp3 = fRec8[0] * fRec1[1] + (fRec7[2] + fRec7[0] + 2.0f * fRec7[1]) / fTemp2;
			fRec9[0] = fSlow5 + 0.995f * fRec9[1];
			float fTemp4 = std::fabs(fTemp3);
			fRec10[0] = std::max<float>(fTemp4, fConst2 * fRec10[1] + fConst3 * fTemp4);
			float fTemp5 = std::min<float>(3.0f, std::max<float>(-3.0f, fRec10[0] + fRec9[0] * fTemp3));
			float fTemp6 = fTemp0 * TemperDsp_faustpower2_f(fTemp5);
			float fTemp7 = (9.0f * fTemp6 + 27.0f) * (fTemp0 + 27.0f);
			float fTemp8 = 9.0f * fTemp0 + 27.0f;
			float fTemp9 = fTemp6 + 27.0f;
			fRec11[0] = fSlow6 + 0.995f * fRec11[1];
			float fTemp10 = (1.0f - fRec11[0]) * fTemp3 + 0.24f * (fRec11[0] * fTemp5 * fTemp9 * fTemp8 / fTemp7);
			fVec0[0] = fTemp10;
			fRec3[0] = fVec0[1] - 0.24f * (fTemp5 * fTemp9 * fTemp8 * (fRec3[1] - fTemp10) / fTemp7);
			fRec2[0] = fRec3[0] + 0.995f * fRec2[1] - fRec3[1];
			fRec1[0] = fRec2[0];
			output0[i0] = FAUSTFLOAT(4.0f * fRec1[0] * fRec0[0]);
			fRec0[1] = fRec0[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec8[1] = fRec8[0];
			fRec9[1] = fRec9[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fVec0[1] = fVec0[0];
			fRec3[1] = fRec3[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// Factory API
::dsp* createTemperDsp() { return new TemperDsp(); }

/******************* END minimal-effect.cpp ****************/

#endif
