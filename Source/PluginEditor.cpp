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
    addAndMakeVisible (driveSlider);
    driveSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    driveAttachment = new SliderAttachment(m_vts, "drive", driveSlider);

    addAndMakeVisible(offsetSlider);
    offsetSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    offsetAttachment = new SliderAttachment(m_vts, "offset", offsetSlider);

    addAndMakeVisible(smoothingSlider);
    smoothingSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    smoothingAttachment = new SliderAttachment(m_vts, "smoothing", smoothingSlider);

    addAndMakeVisible(filterTypeSlider);
    filterTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    filterTypeAttachment = new SliderAttachment(m_vts, "filterType", filterTypeSlider);

    addAndMakeVisible(transferTypeSlider);
    transferTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    transferTypeAttachment = new SliderAttachment(m_vts, "transferType", transferTypeSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 200);
}

MxzeroAudioProcessorEditor::~MxzeroAudioProcessorEditor()
{
}

//==============================================================================
void MxzeroAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);
}

void MxzeroAudioProcessorEditor::resized()
{
    // Lay out the slider components
    Rectangle<int> r (getLocalBounds());

    driveSlider.setBounds(r.removeFromLeft(100));
    offsetSlider.setBounds(r.removeFromLeft(100));
    smoothingSlider.setBounds(r.removeFromLeft(100));
    filterTypeSlider.setBounds(r.removeFromLeft(100));
    transferTypeSlider.setBounds(r.removeFromLeft(100));
}
