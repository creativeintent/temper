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
	float 	fRec10[3];
	float 	fRec9[3];
	float 	fRec8[3];
	float 	fRec7[3];
	float 	fConst0;
	FAUSTFLOAT 	fslider0;
	float 	fRec11[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec12[2];
	float 	fRec6[3];
	FAUSTFLOAT 	fslider2;
	float 	fRec13[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec14[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec15[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec16[2];
	float 	fVec0[2];
	float 	fRec5[2];
	float 	fRec4[2];
	float 	fRec3[3];
	float 	fRec2[3];
	float 	fRec1[3];
	float 	fRec0[3];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("name", "mxzero");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = (3.1415927f / min(1.92e+05f, max(1.0f, (float)fSamplingFreq)));
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 8e+03f;
		fslider1 = 0.1f;
		fslider2 = 1.0f;
		fslider3 = 0.1f;
		fslider4 = 0.0f;
		fslider5 = 1.0f;
	}
	virtual void instanceClear() {
		for (int i=0; i<3; i++) fRec10[i] = 0;
		for (int i=0; i<3; i++) fRec9[i] = 0;
		for (int i=0; i<3; i++) fRec8[i] = 0;
		for (int i=0; i<3; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec11[i] = 0;
		for (int i=0; i<2; i++) fRec12[i] = 0;
		for (int i=0; i<3; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec13[i] = 0;
		for (int i=0; i<2; i++) fRec14[i] = 0;
		for (int i=0; i<2; i++) fRec15[i] = 0;
		for (int i=0; i<2; i++) fRec16[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
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
		ui_interface->addHorizontalSlider("curve", &fslider3, 0.1f, 0.1f, 4.0f, 0.001f);
		ui_interface->addHorizontalSlider("drive", &fslider5, 1.0f, -1e+01f, 1e+01f, 0.001f);
		ui_interface->addHorizontalSlider("filterType", &fslider2, 1.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("filterfc", &fslider0, 8e+03f, 2e+01f, 1.8e+04f, 1.0f);
		ui_interface->addHorizontalSlider("filterq", &fslider1, 0.1f, 0.1f, 8.0f, 0.001f);
		ui_interface->addHorizontalSlider("offset", &fslider4, 0.0f, 0.0f, 1.0f, 0.001f);
		ui_interface->closeBox();
	}
	virtual void compute (int count, FAUSTFLOAT** input, FAUSTFLOAT** output) {
		float 	fSlow0 = (0.005f * float(fslider0));
		float 	fSlow1 = (0.005f * float(fslider1));
		float 	fSlow2 = (0.005f * float(fslider2));
		float 	fSlow3 = (0.005f * float(fslider3));
		float 	fSlow4 = (0.005f * float(fslider4));
		float 	fSlow5 = (0.005f * float(fslider5));
		FAUSTFLOAT* input0 = input[0];
		FAUSTFLOAT* output0 = output[0];
		for (int i=0; i<count; i++) {
			fRec10[0] = (((1.0637765f * fRec10[1]) + (float)input0[i]) - (0.36209202f * fRec10[2]));
			fRec9[0] = (((0.00048638252f * (fRec10[2] + fRec10[0])) + ((0.61464167f * fRec9[1]) + (0.0009343176f * fRec10[1]))) - (0.5686961f * fRec9[2]));
			fRec8[0] = (((2.3153434f * (fRec9[2] + fRec9[0])) + ((0.19564603f * fRec8[1]) + (2.447349f * fRec9[1]))) - (0.7792284f * fRec8[2]));
			fRec7[0] = (((5.509348f * fRec8[1]) + (3.7421112f * (fRec8[2] + fRec8[0]))) - ((0.014306352f * fRec7[1]) + (0.93285143f * fRec7[2])));
			fRec11[0] = (fSlow0 + (0.995f * fRec11[1]));
			float fTemp0 = tanf((fConst0 * fRec11[0]));
			float fTemp1 = (1.0f / fTemp0);
			fRec12[0] = (fSlow1 + (0.995f * fRec12[1]));
			float fTemp2 = (1.0f / fRec12[0]);
			float fTemp3 = (((fTemp1 + fTemp2) / fTemp0) + 1);
			fRec6[0] = (((1.4299138f * fRec7[1]) + (1.6742295f * (fRec7[2] + fRec7[0]))) - (((fRec6[2] * (((fTemp1 - fTemp2) / fTemp0) + 1)) + (2 * (fRec6[1] * (1 - (1.0f / faustpower<2>(fTemp0)))))) / fTemp3));
			float fTemp4 = (fRec6[0] + (fRec6[2] + (2.0f * fRec6[1])));
			fRec13[0] = (fSlow2 + (0.995f * fRec13[1]));
			fRec14[0] = (fSlow3 + (0.995f * fRec14[1]));
			fRec15[0] = (fSlow4 + (0.995f * fRec15[1]));
			fRec16[0] = (fSlow5 + (0.995f * fRec16[1]));
			float fTemp5 = tanhf((fRec14[0] * tanhf((fRec15[0] + ((fRec16[0] * fTemp4) / fTemp3)))));
			float fTemp6 = tanhf(fRec14[0]);
			fVec0[0] = (fTemp4 / fTemp3);
			fRec5[0] = (((fTemp4 * ((fRec13[0] * ((fTemp5 / fTemp6) + -1)) + 1.0f)) / fTemp3) + ((fVec0[1] * (fRec13[0] + (((1.0f - fRec13[0]) * fTemp5) / fTemp6))) + (fRec5[1] * (0 - ((fRec13[0] * fTemp5) / fTemp6)))));
			fRec4[0] = (((0.995f * fRec4[1]) + fRec5[0]) - fRec5[1]);
			fRec3[0] = (((1.0637765f * fRec3[1]) + fRec4[0]) - (0.36209202f * fRec3[2]));
			fRec2[0] = ((((0.61464167f * fRec2[1]) + (0.0009343176f * fRec3[1])) + (0.00048638252f * (fRec3[2] + fRec3[0]))) - (0.5686961f * fRec2[2]));
			fRec1[0] = ((((0.19564603f * fRec1[1]) + (2.447349f * fRec2[1])) + (2.3153434f * (fRec2[2] + fRec2[0]))) - (0.7792284f * fRec1[2]));
			fRec0[0] = (((5.509348f * fRec1[1]) + (3.7421112f * (fRec1[2] + fRec1[0]))) - ((0.014306352f * fRec0[1]) + (0.93285143f * fRec0[2])));
			output0[i] = (FAUSTFLOAT)((1.4299138f * fRec0[1]) + (1.6742295f * (fRec0[2] + fRec0[0])));
			// post processing
			fRec0[2] = fRec0[1]; fRec0[1] = fRec0[0];
			fRec1[2] = fRec1[1]; fRec1[1] = fRec1[0];
			fRec2[2] = fRec2[1]; fRec2[1] = fRec2[0];
			fRec3[2] = fRec3[1]; fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec6[2] = fRec6[1]; fRec6[1] = fRec6[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec7[2] = fRec7[1]; fRec7[1] = fRec7[0];
			fRec8[2] = fRec8[1]; fRec8[1] = fRec8[0];
			fRec9[2] = fRec9[1]; fRec9[1] = fRec9[0];
			fRec10[2] = fRec10[1]; fRec10[1] = fRec10[0];
		}
	}
};



