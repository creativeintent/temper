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
    setColour(Slider::rotarySliderFillColourId, Colour::fromRGBA(226, 115, 0, 255));
}

Font MxzLookAndFeel::getLabelFont(Label &)
{
    return Font(Typeface::createSystemTypefaceFor(BinaryData::MontserratLight_otf,
                                                  BinaryData::MontserratLight_otfSize)).withPointHeight(10);
}

void MxzLookAndFeel::drawLabel(Graphics& g, Label& l)
{
    Colour labelColour = Colour::fromRGB(149, 89, 17);
    Font labelFont = getLabelFont(l);

    g.setColour(labelColour);
    g.setFont(labelFont);

    Rectangle<int> textArea (l.getBorderSize().subtractedFrom (l.getLocalBounds()));

    g.drawFittedText (l.getText(), textArea, l.getJustificationType(),
                      jmax (1, (int) (textArea.getHeight() / labelFont.getHeight())),
                      l.getMinimumHorizontalScale());
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

    Font readoutFont = Font(Typeface::createSystemTypefaceFor(BinaryData::MontserratLight_otf,
                                                              BinaryData::MontserratLight_otfSize)).withPointHeight(14);

    g.setFont(readoutFont);

    // Draw the readout
    Colour readoutColour = Colour::fromRGB(254, 173, 29).withAlpha(isMouseOver ? 1.0f : 0.9f);
    g.setColour(readoutColour);

    String sliderVal;
    if (slider.getValue() >= 1000)
    {
        const float roundedVal = floorf(slider.getValue() / 100) * 0.1;
        sliderVal = String(roundedVal) + "kHz";
    }
    else
    {
        const float roundedVal = floorf(slider.getValue() * 10) * 0.1;
        sliderVal = slider.getTextFromValue(roundedVal);
    }

    g.drawText(sliderVal, centreX - radius, centreY - 10.0f, rw, 24.0f, Justification::centred);

    // Draw the track
    g.setColour (slider.findColour (Slider::rotarySliderOutlineColourId));

    Path track;
    track.addArc(rx, ry, rw, rw, rotaryStartAngle, rotaryEndAngle, true);
    g.strokePath(track, PathStrokeType(3.0f));

    // Draw the slider position
    Colour sliderFillStart = Colour::fromRGBA(245, 121, 35, 255).withAlpha(isMouseOver ? 1.0f : 0.9f);
    Colour sliderFillStop = Colour::fromRGBA(255, 184, 23, 255).withAlpha(isMouseOver ? 1.0f : 0.9f);
    ColourGradient sliderFill = ColourGradient(sliderFillStart,
                                               (float) x,
                                               (float) 0,
                                               sliderFillStop,
                                               (float) width,
                                               (float) 0,
                                               false);

    g.setGradientFill(sliderFill);

    Path filledArc;
    filledArc.addArc(rx, ry, rw, rw, rotaryStartAngle, angle, true);
    PathStrokeType(3.0f).createStrokedPath(filledArc, filledArc);
    g.fillPath(filledArc);
}