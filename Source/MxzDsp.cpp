//----------------------------------------------------------
// name: "mxzero"
//
// Code generated with Faust 0.9.96 (http://faust.grame.fr)
//----------------------------------------------------------

/* link with : "" */
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
#define FAUSTCLASS MxzDsp
#endif

class MxzDsp : public dsp {
  private:
	float 	fRec11[3];
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fConst0;
	float 	fConst1;
	FAUSTFLOAT 	fslider0;
	float 	fRec12[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec13[2];
	float 	fRec7[3];
	FAUSTFLOAT 	fslider2;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec16[2];
	float 	fConst2;
	float 	fConst3;
	float 	fRec17[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec18[2];
	float 	fVec0[2];
	FAUSTFLOAT 	fslider6;
	float 	fRec19[2];
	float 	fRec6[2];
	float 	fRec5[2];
	float 	fRec4[2];
	FAUSTFLOAT 	fslider7;
	float 	fRec20[2];
	float 	fRec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("name", "mxzero");
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.0");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = min(1.92e+05f, max(1.0f, (float)fSamplingFreq));
		fConst1 = (3.1415927f / fConst0);
		fConst2 = expf((0 - (25.0f / fConst0)));
		fConst3 = (1.0f - fConst2);
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 1.6e+04f;
		fslider1 = 1.0f;
		fslider2 = -6e+01f;
		fslider3 = 0.0f;
		fslider4 = 1.0f;
		fslider5 = 4.0f;
		fslider6 = 1.0f;
		fslider7 = -3.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<3; i++) fRec11[i] = 0;
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fRec17[i] = 0;
		for (int i=0; i<2; i++) fRec18[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec19[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fRec20[i] = 0;
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
	virtual MxzDsp* clone() {
		return new MxzDsp();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;
	}
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("0x00");
		ui_interface->addHorizontalSlider("curve", &fslider4, 1.0f, 0.1f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("drive", &fslider5, 4.0f, -1e+01f, 1e+01f, 0.001f);
		ui_interface->addHorizontalSlider("feedback", &fslider2, -6e+01f, -6e+01f, -24.0f, 1.0f);
		ui_interface->addHorizontalSlider("filterType", &fslider6, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("filterfc", &fslider0, 1.6e+04f, 1e+02f, 1.6e+04f, 1.0f);
		ui_interface->addHorizontalSlider("filterq", &fslider1, 1.0f, 1.0f, 8.0f, 0.001f);
		ui_interface->addHorizontalSlider("level", &fslider7, -3.0f, -12.0f, 12.0f, 1.0f);
		ui_interface->addHorizontalSlider("offset", &fslider3, 0.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.005f * float(fslider0));
		float 	fSlow1 = (0.005f * float(fslider1));
		float 	fSlow2 = (0.005f * powf(10,(0.05f * float(fslider2))));
		float 	fSlow3 = (0.005f * float(fslider3));
		float 	fSlow4 = (0.005f * float(fslider4));
		float 	fSlow5 = (0.005f * float(fslider5));
		float 	fSlow6 = (0.005f * float(fslider6));
		float 	fSlow7 = (0.005f * powf(10,(0.05f * float(fslider7))));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			fRec11[0] = (((float)input0[i] + (1.0637765f * fRec11[1])) - (0.36209202f * fRec11[2]));
			fRec10[0] = (((0.00048638252f * (fRec11[2] + fRec11[0])) + ((0.61464167f * fRec10[1]) + (0.0009343176f * fRec11[1]))) - (0.5686961f * fRec10[2]));
			fRec9[0] = (((2.3153434f * (fRec10[2] + fRec10[0])) + ((0.19564603f * fRec9[1]) + (2.447349f * fRec10[1]))) - (0.7792284f * fRec9[2]));
			fRec8[0] = (((5.509348f * fRec9[1]) + (3.7421112f * (fRec9[2] + fRec9[0]))) - ((0.014306352f * fRec8[1]) + (0.93285143f * fRec8[2])));
			fRec12[0] = (fSlow0 + (0.995f * fRec12[1]));
			float fTemp0 = tanf((fConst1 * fRec12[0]));
			float fTemp1 = (1.0f / fTemp0);
			fRec13[0] = (fSlow1 + (0.995f * fRec13[1]));
			float fTemp2 = (1.0f / fRec13[0]);
			float fTemp3 = (((fTemp1 + fTemp2) / fTemp0) + 1);
			fRec7[0] = (((1.4299138f * fRec8[1]) + (1.6742295f * (fRec8[2] + fRec8[0]))) - ((((((fTemp1 - fTemp2) / fTemp0) + 1) * fRec7[2]) + (2 * ((1 - (1.0f / faustpower<2>(fTemp0))) * fRec7[1]))) / fTemp3));
			fRec14[0] = (fSlow2 + (0.995f * fRec14[1]));
			float fTemp4 = ((((2.0f * fRec7[1]) + (fRec7[0] + fRec7[2])) / fTemp3) + (fRec4[1] * fRec14[0]));
			fRec15[0] = (fSlow3 + (0.995f * fRec15[1]));
			fRec16[0] = (fSlow4 + (0.995f * fRec16[1]));
			float fTemp5 = fabsf(fTemp4);
			fRec17[0] = max(fTemp5, ((fConst2 * fRec17[1]) + (fConst3 * fTemp5)));
			fRec18[0] = (fSlow5 + (0.995f * fRec18[1]));
			float fTemp6 = tanhf((fRec16[0] * tanhf((fRec17[0] + (fTemp4 * fRec18[0])))));
			float fTemp7 = tanhf(fRec16[0]);
			float fTemp8 = ((fTemp4 * (1.0f - fRec15[0])) + (0.24f * ((fTemp6 * fRec15[0]) / fTemp7)));
			fVec0[0] = fTemp8;
			fRec19[0] = (fSlow6 + (0.995f * fRec19[1]));
			fRec6[0] = ((fVec0[0] * ((fRec19[0] * ((fTemp6 / fTemp7) + -1)) + 1.0f)) + ((fVec0[1] * (fRec19[0] + (((1.0f - fRec19[0]) * fTemp6) / fTemp7))) + ((0 - ((fRec19[0] * fTemp6) / fTemp7)) * fRec6[1])));
			fRec5[0] = (((0.995f * fRec5[1]) + fRec6[0]) - fRec6[1]);
			fRec4[0] = fRec5[0];
			fRec20[0] = (fSlow7 + (0.995f * fRec20[1]));
			fRec3[0] = (((1.0637765f * fRec3[1]) + (4.0f * (fRec4[0] * fRec20[0]))) - (0.36209202f * fRec3[2]));
			fRec2[0] = ((((0.00048638252f * (fRec3[2] + fRec3[0])) + (0.61464167f * fRec2[1])) + (0.0009343176f * fRec3[1])) - (0.5686961f * fRec2[2]));
			fRec1[0] = ((((2.3153434f * (fRec2[2] + fRec2[0])) + (0.19564603f * fRec1[1])) + (2.447349f * fRec2[1])) - (0.7792284f * fRec1[2]));
			fRec0[0] = (((3.7421112f * (fRec1[2] + fRec1[0])) + (5.509348f * fRec1[1])) - ((0.014306352f * fRec0[1]) + (0.93285143f * fRec0[2])));
			output0[i] = (FAUSTFLOAT)((1.6742295f * (fRec0[2] + fRec0[0])) + (1.4299138f * fRec0[1]));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec20[1] = fRec20[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fRec6[1] = fRec6[0];
			fRec19[1] = fRec19[0];
			fVec0[1] = fVec0[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
			fRec11[2] = fRec11[1]; fRec11[1] = fRec11[0];
		}
	}
};



