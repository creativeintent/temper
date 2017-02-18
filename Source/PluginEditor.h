/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class MxzeroAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    MxzeroAudioProcessorEditor (MxzeroAudioProcessor&, AudioProcessorValueTreeState&);
    ~MxzeroAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MxzeroAudioProcessor& processor;

    AudioProcessorValueTreeState& m_vts;

    // Sliders and listeners
    Slider driveSlider;
    ScopedPointer<SliderAttachment> driveAttachment;

    Slider offsetSlider;
    ScopedPointer<SliderAttachment> offsetAttachment;

    Slider smoothingSlider;
    ScopedPointer<SliderAttachment> smoothingAttachment;

    Slider filterTypeSlider;
    ScopedPointer<SliderAttachment> filterTypeAttachment;

    Slider transferTypeSlider;
    ScopedPointer<SliderAttachment> transferTypeAttachment;

    Slider mixSlider;
    ScopedPointer<SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MxzeroAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
