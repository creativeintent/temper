/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MxzLookAndFeel.h"
#include "PluginProcessor.h"
#include "MainComponent.h"
#include "SpectroscopeComponent.h"

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

    //==============================================================================
    ScopedPointer<SpectroscopeComponent> m_viz;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MxzeroAudioProcessor& processor;
    MxzLookAndFeel laf;
    AudioProcessorValueTreeState& m_vts;

    ScopedPointer<MainComponent> m_main;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MxzeroAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
