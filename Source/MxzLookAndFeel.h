/*
  ==============================================================================

    MxzLookAndFeel.h
    Created: 1 Mar 2017 8:15:08pm
    Author:  Nick Thompson

  ==============================================================================
*/

#ifndef MXZLOOKANDFEEL_H_INCLUDED
#define MXZLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class MxzLookAndFeel : public LookAndFeel_V2
{
public:
    MxzLookAndFeel();

    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider&) override;
};

#endif  // MXZLOOKANDFEEL_H_INCLUDED
