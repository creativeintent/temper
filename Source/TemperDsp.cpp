//----------------------------------------------------------
// name: "temper"
//
// Code generated with Faust 0.9.100 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with  */
#include <math.h>
#ifndef FAUSTPOWER
#define FAUSTPOWER
#include <cmath>
template <int N> inline int faustpower(int x)              { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline int faustpower<0>(int x)            { return 1; }
template <> 	 inline int faustpower<1>(int x)            { return x; }
template <> 	 inline int faustpower<2>(int x)            { return x*x; }
template <int N> inline float faustpower(float x)            { return faustpower<N/2>(x) * faustpower<N-N/2>(x); } 
template <> 	 inline float faustpower<0>(float x)          { return 1; }
template <> 	 inline float faustpower<1>(float x)          { return x; }
template <> 	 inline float faustpower<2>(float x)          { return x*x; }
#endif
/************************************************************************
 ************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

    This is sample code. This file is provided as an example of minimal
    FAUST architecture file. Redistribution and use in source and binary
    forms, with or without modification, in part or in full are permitted.
    In particular you can create a derived work of this FAUST architecture
    and distribute that work under terms of your choice.

    This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/
 
#include <math.h>
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

using std::max;
using std::min;

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  


#ifndef FAUSTCLASS 
#define FAUSTCLASS TemperDsp
#endif

class TemperDsp : public ::dsp {
  private:
	FAUSTFLOAT 	fslider0;
	float 	fRec7[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec8[2];
	float 	fRec13[3];
	float 	fRec12[3];
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider2;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec15[2];
	float 	fRec9[3];
	float 	fConst2;
	float 	fConst3;
	float 	fRec16[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec18[2];
	float 	fVec0[2];
	float 	fRec6[2];
	float 	fRec5[2];
	float 	fRec4[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec19[2];
	float 	fRec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
		m->declare("name", "temper");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1e+03f, (float)fSamplingFreq));
		fConst1 = (3.1415927f / fConst0);
		fConst2 = expf((0 - (25.0f / fConst0)));
		fConst3 = (1.0f - fConst2);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.0f;
		fslider1 = -6e+01f;
		fslider2 = 1.6e+04f;
		fslider3 = 1.0f;
		fslider4 = 4.0f;
		fslider5 = 1.0f;
		fslider6 = -3.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<3; i++) fRec3[i] = 0;
		for (int i=0; i<3; i++) fRec2[i] = 0;
		for (int i=0; i<3; i++) fRec1[i] = 0;
		for (int i=0; i<3; i++) fRec0[i] = 0;
	}
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}
	virtual TemperDsp* clone() {
		return new TemperDsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("temper");
		ui_interface->addHorizontalSlider("Curve", &fslider5, 1.0f, 0.1f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("Cutoff", &fslider2, 1.6e+04f, 1e+02f, 1.6e+04f, 1.0f);
		ui_interface->addHorizontalSlider("Drive", &fslider4, 4.0f, -1e+01f, 1e+01f, 0.001f);
		ui_interface->addHorizontalSlider("Feedback", &fslider1, -6e+01f, -6e+01f, -24.0f, 1.0f);
		ui_interface->addHorizontalSlider("Level", &fslider6, -3.0f, -24.0f, 24.0f, 1.0f);
		ui_interface->addHorizontalSlider("Resonance", &fslider3, 1.0f, 1.0f, 8.0f, 0.001f);
		ui_interface->addHorizontalSlider("Saturation", &fslider0, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.005f * float(fslider0));
		float 	fSlow1 = (0.005f * powf(10,(0.05f * float(fslider1))));
		float 	fSlow2 = (0.005f / tanf((fConst1 * float(fslider2))));
		float 	fSlow3 = (0.005f * float(fslider3));
		float 	fSlow4 = (0.005f * float(fslider4));
		float 	fSlow5 = (0.005f * float(fslider5));
		float 	fSlow6 = (0.005f * powf(10,(0.05f * float(fslider6))));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			fRec7[0] = (fSlow0 + (0.995f * fRec7[1]));
			fRec8[0] = (fSlow1 + (0.995f * fRec8[1]));
			fRec13[0] = (((1.0637765f * fRec13[1]) + (float)input0[i]) - (0.36209202f * fRec13[2]));
			fRec12[0] = ((((0.0009343176f * fRec13[1]) + (0.00048638252f * (fRec13[0] + fRec13[2]))) + (0.61464167f * fRec12[1])) - (0.5686961f * fRec12[2]));
			fRec11[0] = ((((2.447349f * fRec12[1]) + (2.3153434f * (fRec12[0] + fRec12[2]))) + (0.19564603f * fRec11[1])) - (0.7792284f * fRec11[2]));
			fRec10[0] = (((5.509348f * fRec11[1]) + (3.7421112f * (fRec11[0] + fRec11[2]))) - ((0.014306352f * fRec10[1]) + (0.93285143f * fRec10[2])));
			fRec14[0] = (fSlow2 + (0.995f * fRec14[1]));
			fRec15[0] = (fSlow3 + (0.995f * fRec15[1]));
			float fTemp0 = (1.0f / fRec15[0]);
			float fTemp1 = ((fRec14[0] * (fRec14[0] + fTemp0)) + 1);
			fRec9[0] = (((1.4299138f * fRec10[1]) + (1.6742295f * (fRec10[2] + fRec10[0]))) - (((fRec9[2] * ((fRec14[0] * (fRec14[0] - fTemp0)) + 1)) + (2 * (fRec9[1] * (1 - faustpower<2>(fRec14[0]))))) / fTemp1));
			float fTemp2 = ((fRec8[0] * fRec4[1]) + ((fRec9[2] + (fRec9[0] + (2.0f * fRec9[1]))) / fTemp1));
			float fTemp3 = fabsf(fTemp2);
			fRec16[0] = max(fTemp3, ((fConst2 * fRec16[1]) + (fConst3 * fTemp3)));
			fRec17[0] = (fSlow4 + (0.995f * fRec17[1]));
			float fTemp4 = min((float)3, max((float)-3, (fRec16[0] + (fRec17[0] * fTemp2))));
			fRec18[0] = (fSlow5 + (0.995f * fRec18[1]));
			float fTemp5 = faustpower<2>(fRec18[0]);
			float fTemp6 = (fTemp5 * faustpower<2>(fTemp4));
			float fTemp7 = (fTemp6 + 27);
			float fTemp8 = ((9 * fTemp5) + 27);
			float fTemp9 = (((9 * fTemp6) + 27) * (fTemp5 + 27));
			float fTemp10 = (((1.0f - fRec7[0]) * fTemp2) + (0.24f * ((((fRec7[0] * fTemp4) * fTemp7) * fTemp8) / fTemp9)));
			fVec0[0] = fTemp10;
			float fTemp11 = ((fTemp4 * fTemp7) * fTemp8);
			fRec6[0] = (fVec0[1] + ((fRec6[1] * (0 - (0.24f * (fTemp11 / fTemp9)))) + (0.24f * ((fTemp11 * fVec0[0]) / fTemp9))));
			fRec5[0] = ((fRec6[0] + (0.995f * fRec5[1])) - fRec6[1]);
			fRec4[0] = fRec5[0];
			fRec19[0] = (fSlow6 + (0.995f * fRec19[1]));
			fRec3[0] = (((4.0f * (fRec4[0] * fRec19[0])) + (1.0637765f * fRec3[1])) - (0.36209202f * fRec3[2]));
			fRec2[0] = (((0.61464167f * fRec2[1]) + ((0.0009343176f * fRec3[1]) + (0.00048638252f * (fRec3[0] + fRec3[2])))) - (0.5686961f * fRec2[2]));
			fRec1[0] = (((0.19564603f * fRec1[1]) + ((2.447349f * fRec2[1]) + (2.3153434f * (fRec2[0] + fRec2[2])))) - (0.7792284f * fRec1[2]));
			fRec0[0] = (((5.509348f * fRec1[1]) + (3.7421112f * (fRec1[0] + fRec1[2]))) - ((0.014306352f * fRec0[1]) + (0.93285143f * fRec0[2])));
			output0[i] = (FAUSTFLOAT)((1.4299138f * fRec0[1]) + (1.6742295f * (fRec0[0] + fRec0[2])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec19[1] = fRec19[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fVec0[1] = fVec0[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
			fRec12[2] = fRec12[1]; fRec12[1] = fRec12[0];
			fRec13[2] = fRec13[1]; fRec13[1] = fRec13[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
		}
	}
};



