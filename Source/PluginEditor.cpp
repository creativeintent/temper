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
    addAndMakeVisible(m_main = new MainComponent(m_vts));
    addAndMakeVisible(m_viz = new SpectroscopeComponent());
    setSize (700, 352);
    setLookAndFeel(&laf);
}

MxzeroAudioProcessorEditor::~MxzeroAudioProcessorEditor()
{
}

//==============================================================================
void MxzeroAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::black);
}

void MxzeroAudioProcessorEditor::resized()
{
    m_main->setBounds(0, 0, 700, 152);
    m_viz->setBounds(0, 152, 700, 200);
}
