/*
  ==============================================================================

    MxzLookAndFeel.cpp
    Created: 1 Mar 2017 8:15:09pm
    Author:  Nick Thompson

  ==============================================================================
*/

#include "MxzLookAndFeel.h"

MxzLookAndFeel::MxzLookAndFeel()
{
    setColour(Slider::rotarySliderFillColourId, Colours::orange);
}

void MxzLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                       const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    const float radius = jmin (width / 2, height / 2) - 2.0f;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;
    const float rw = radius * 2.0f;
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();

    g.setFont(Font("Avenir", 22.0, 0));

    // Draw the readout
    g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));

    const float roundedVal = floorf(slider.getValue() * 10) * 0.1;
    String sliderVal = slider.getTextFromValue(roundedVal);
    g.drawText(sliderVal, centreX - radius, centreY - 8.0f, rw, 24.0f, Justification::centred);

    // Draw the track
    g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));

    Path track;
    track.addArc(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, true);
    g.strokePath(track, PathStrokeType(4.0f));

    // Draw the slider position
    g.setColour (slider.findColour (Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));

    Path filledArc;
    filledArc.addArc(rx, ry, rw, rw, rotaryStartAngle, angle, true);
    g.strokePath(filledArc, PathStrokeType(4.0f));
}