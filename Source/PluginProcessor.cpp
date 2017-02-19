/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "MxzDsp.cpp"


//==============================================================================
MxzeroAudioProcessor::MxzeroAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                  ),
m_params (*this, nullptr)
#else
: m_params (*this, nullptr)
#endif
{
    m_restriction = new RestrictionProcessor();
    m_bridge = new FaustUIBridge(m_params);
    m_lastKnownSampleRate = 0.0;

    // Initialize the dsp units
    for (int i = 0; i < getTotalNumInputChannels(); ++i)
    {
        MxzDsp* dsp = new MxzDsp();
        dsp->buildUserInterface(m_bridge);
        m_dsps.add(dsp);
    }

    // Initialize the AudioProcessorValueTreeState root
    ValueTree root (Identifier("MXZ"));
    m_params.state = root;

    // Verify the installation
    m_restriction->validateRegistration();
}

MxzeroAudioProcessor::~MxzeroAudioProcessor()
{
}

//==============================================================================
const String MxzeroAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MxzeroAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MxzeroAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double MxzeroAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MxzeroAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MxzeroAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MxzeroAudioProcessor::setCurrentProgram (int index)
{
}

const String MxzeroAudioProcessor::getProgramName (int index)
{
    return String();
}

void MxzeroAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MxzeroAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    if (m_lastKnownSampleRate == 0.0)
        for (int i = 0; i < m_dsps.size(); ++i)
            m_dsps.getUnchecked(i)->init(sampleRate);
    else
        for (int i = 0; i < m_dsps.size(); ++i)
            m_dsps.getUnchecked(i)->instanceConstants(sampleRate);

    m_restriction->prepareToPlay(samplesPerBlock, sampleRate);
    m_lastKnownSampleRate = sampleRate;
}

void MxzeroAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MxzeroAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MxzeroAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Hand the guts of the processing off to the Faust implementation
    float** channelData = buffer.getArrayOfWritePointers();
    const int numSamples = buffer.getNumSamples();

    for (int i = 0; i < totalNumInputChannels; ++i)
        m_dsps.getUnchecked(i)->compute(numSamples, channelData + i, channelData + i);

#if ! JUCE_DEBUG
    // After the Faust processing, add the demo restriction to the output stream
    m_restriction->processBlock(buffer);
#endif
}

//==============================================================================
bool MxzeroAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MxzeroAudioProcessor::createEditor()
{
    return new MxzeroAudioProcessorEditor (*this, m_params);
}

//==============================================================================
void MxzeroAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (m_params.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MxzeroAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName (m_params.state.getType()))
            m_params.state = ValueTree::fromXml (*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MxzeroAudioProcessor();
}
