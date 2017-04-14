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
    addAndMakeVisible(m_vizPre = new SpectroscopeComponent());
    addAndMakeVisible(m_vizPost = new SpectroscopeComponent());

    m_vizPost->setBaseColour(Colours::orange);

    setSize (744, 476);
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
    m_main->setBounds(0, 0, 744, 476);
    m_vizPre->setBounds(0, 152, 700, 200);
    m_vizPost->setBounds(0, 152, 700, 200);
}
