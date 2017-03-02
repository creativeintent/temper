/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MxzeroAudioProcessorEditor::MxzeroAudioProcessorEditor (MxzeroAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), m_vts(vts)
{
    // Connect the sliders
    addAndMakeVisible(filterFreqSlider);
    filterFreqSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    filterFreqSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    filterFreqAttachment = new SliderAttachment(m_vts, "filterfc", filterFreqSlider);

    addAndMakeVisible(filterResoSlider);
    filterResoSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    filterResoSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    filterResoAttachment = new SliderAttachment(m_vts, "filterq", filterResoSlider);

    addAndMakeVisible (driveSlider);
    driveSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    driveSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    driveAttachment = new SliderAttachment(m_vts, "drive", driveSlider);

    addAndMakeVisible(offsetSlider);
    offsetSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    offsetSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    offsetAttachment = new SliderAttachment(m_vts, "offset", offsetSlider);

//    addAndMakeVisible(filterTypeSlider);
//    filterTypeSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
//    filterTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
//    filterTypeAttachment = new SliderAttachment(m_vts, "filterType", filterTypeSlider);

    addAndMakeVisible(transferTypeSlider);
    transferTypeSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    transferTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    transferTypeAttachment = new SliderAttachment(m_vts, "curve", transferTypeSlider);

    addAndMakeVisible(mixSlider);
    mixSlider.setTextBoxStyle(Slider::NoTextBox, true, 80, 20);
    mixSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    mixAttachment = new SliderAttachment(m_vts, "mix", mixSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (744, 476);
    setLookAndFeel(&laf);
}

MxzeroAudioProcessorEditor::~MxzeroAudioProcessorEditor()
{
}

//==============================================================================
void MxzeroAudioProcessorEditor::paint (Graphics& g)
{
    Image bg = ImageCache::getFromMemory(BinaryData::Background_png, BinaryData::Background_pngSize);
    g.drawImageAt(bg.rescaled(744, 476), 0, 0);
}

void MxzeroAudioProcessorEditor::resized()
{
    const int knobWidth = 178 * 0.5;
    const int halfKnobWidth = knobWidth * 0.5;

    // Left side knobs
    filterFreqSlider.setBounds(75 - halfKnobWidth, 157 - halfKnobWidth, knobWidth, knobWidth);
    filterResoSlider.setBounds(75 - halfKnobWidth, 352 - halfKnobWidth, knobWidth, knobWidth);

    // Center knobs
    driveSlider.setBounds(219 - halfKnobWidth, 250 - halfKnobWidth, knobWidth, knobWidth);
    transferTypeSlider.setBounds(528 - halfKnobWidth, 250 - halfKnobWidth, knobWidth, knobWidth);
    offsetSlider.setBounds(380 - halfKnobWidth, 380 - halfKnobWidth, knobWidth, knobWidth);

    // Right side knobs
    mixSlider.setBounds(674 - halfKnobWidth, 157 - halfKnobWidth, knobWidth, knobWidth);

    // TODO: Maybe nixing this?
    // filterTypeSlider.setBounds(r.removeFromLeft(100));
}
