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
    addAndMakeVisible(bandpassFreqSlider);
    bandpassFreqSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    bandpassFreqAttachment = new SliderAttachment(m_vts, "bandpassfc", bandpassFreqSlider);

    addAndMakeVisible(bandpassResoSlider);
    bandpassResoSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    bandpassResoAttachment = new SliderAttachment(m_vts, "bandpassq", bandpassResoSlider);

    addAndMakeVisible (driveSlider);
    driveSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    driveAttachment = new SliderAttachment(m_vts, "drive", driveSlider);

    addAndMakeVisible(offsetSlider);
    offsetSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    offsetAttachment = new SliderAttachment(m_vts, "offset", offsetSlider);

    addAndMakeVisible(filterTypeSlider);
    filterTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    filterTypeAttachment = new SliderAttachment(m_vts, "filterType", filterTypeSlider);

    addAndMakeVisible(transferTypeSlider);
    transferTypeSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    transferTypeAttachment = new SliderAttachment(m_vts, "transferType", transferTypeSlider);

    addAndMakeVisible(mixSlider);
    mixSlider.setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    mixAttachment = new SliderAttachment(m_vts, "mix", mixSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 200);
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

    bandpassFreqSlider.setBounds(r.removeFromLeft(100));
    bandpassResoSlider.setBounds(r.removeFromLeft(100));
    driveSlider.setBounds(r.removeFromLeft(100));
    offsetSlider.setBounds(r.removeFromLeft(100));
    filterTypeSlider.setBounds(r.removeFromLeft(100));
    transferTypeSlider.setBounds(r.removeFromLeft(100));
    mixSlider.setBounds(r.removeFromLeft(100));
}
