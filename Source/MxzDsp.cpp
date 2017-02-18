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
	FAUSTFLOAT 	fslider0;
	float 	fRec3[2];
	FAUSTFLOAT 	fslider1;
	float 	fRec4[2];
	float 	fVec0[2];
	FAUSTFLOAT 	fslider2;
	float 	fRec5[2];
	FAUSTFLOAT 	fslider3;
	float 	fRec6[2];
	float 	fRec2[2];
	FAUSTFLOAT 	fslider4;
	float 	fRec7[2];
	float 	fRec1[2];
	float 	fRec0[2];
	FAUSTFLOAT 	fslider5;
	float 	fRec8[2];
	int fSamplingFreq;

  public:
	virtual void metadata(Meta* m) { 
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.0");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("name", "mxzero");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "0.0");
	}

	virtual int getNumInputs() { return 1; }
	virtual int getNumOutputs() { return 1; }
	static void classInit(int samplingFreq) {
	}
	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
	}
	virtual void instanceResetUserInterface() {
		fslider0 = 0.5f;
		fslider1 = 0.0f;
		fslider2 = 1.0f;
		fslider3 = 0.0f;
		fslider4 = 0.5f;
		fslider5 = 0.5f;
	}
	virtual void instanceClear() {
		for (int i=0; i<2; i++) fRec3[i] = 0;
		for (int i=0; i<2; i++) fRec4[i] = 0;
		for (int i=0; i<2; i++) fVec0[i] = 0;
		for (int i=0; i<2; i++) fRec5[i] = 0;
		for (int i=0; i<2; i++) fRec6[i] = 0;
		for (int i=0; i<2; i++) fRec2[i] = 0;
		for (int i=0; i<2; i++) fRec7[i] = 0;
		for (int i=0; i<2; i++) fRec1[i] = 0;
		for (int i=0; i<2; i++) fRec0[i] = 0;
		for (int i=0; i<2; i++) fRec8[i] = 0;
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
		ui_interface->addHorizontalSlider("drive", &fslider2, 1.0f, -1e+01f, 1e+01f, 0.001f);
		ui_interface->addHorizontalSlider("filterType", &fslider4, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("mix", &fslider5, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("offset", &fslider1, 0.0f, -1.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("smoothing", &fslider0, 0.5f, 0.0f, 1.0f, 0.001f);
		ui_interface->addHorizontalSlider("transferType", &fslider3, 0.0f, 0.0f, 3.0f, 0.001f);
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
			fRec3[0] = (fSlow0 + (0.995f * fRec3[1]));
			fRec4[0] = (fSlow1 + (0.995f * fRec4[1]));
			float fTemp0 = (float)input0[i];
			fVec0[0] = fTemp0;
			fRec5[0] = (fSlow2 + (0.995f * fRec5[1]));
			float fTemp1 = tanhf((fRec4[0] + (fVec0[0] * fRec5[0])));
			float fTemp2 = faustpower<2>(fTemp1);
			float fTemp3 = ((2 * fTemp2) + -1);
			fRec6[0] = (fSlow3 + (0.995f * fRec6[1]));
			float fTemp4 = (1 - (2 * (fTemp2 * (0 - (2 * (fTemp3 + -1))))));
			fRec2[0] = ((fRec2[1] * fRec3[0]) + ((((fTemp3 * max((float)0, (1 - fabsf(fRec6[0])))) + (max((float)0, (1 - fabsf((fRec6[0] + -2)))) * fTemp4)) + (fTemp1 * ((max((float)0, (1 - fabsf((fRec6[0] + -1)))) * ((2 * fTemp3) + -1)) + (max((float)0, (1 - fabsf((fRec6[0] + -3)))) * (1 - (2 * (fTemp3 - fTemp4))))))) * (1.0f - fRec3[0])));
			fRec7[0] = (fSlow4 + (0.995f * fRec7[1]));
			fRec1[0] = (((1.0f - ((1 - fRec2[0]) * fRec7[0])) * fVec0[0]) + ((((fRec2[0] * (1.0f - fRec7[0])) + fRec7[0]) * fVec0[1]) + ((0 - (fRec2[0] * fRec7[0])) * fRec1[1])));
			fRec0[0] = ((fRec1[0] + (0.995f * fRec0[1])) - fRec1[1]);
			fRec8[0] = (fSlow5 + (0.995f * fRec8[1]));
			output0[i] = (FAUSTFLOAT)((fRec0[0] * fRec8[0]) + ((1.0f - fRec8[0]) * fVec0[0]));
			// post processing
			fRec8[1] = fRec8[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			fRec7[1] = fRec7[0];
			fRec2[1] = fRec2[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fVec0[1] = fVec0[0];
			fRec4[1] = fRec4[0];
			fRec3[1] = fRec3[0];
		}
	}
};



