/*
  ==============================================================================

    RestrictionProcessor.cpp
    Created: 15 Feb 2017 10:03:51pm
    Author:  Nick Thompson

  ==============================================================================
*/

#include "RestrictionProcessor.h"

const double kFreq = 0.05; // Twenty second period.
const double kDuty = 0.75; // Fifteen seconds of audio, five seconds of silence.

//==============================================================================
RestrictionProcessor::RestrictionProcessor()
{
    m_smoothing = new LinearSmoothedValue<float>();
    m_alpha = 1.0f;
}

//==============================================================================
void RestrictionProcessor::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    m_sampleRate = sampleRate;
    m_delta = kFreq / m_sampleRate;
    m_currentAngle = 0.0;
    m_smoothing->reset(sampleRate, 1.0);
}

void RestrictionProcessor::releaseResources() {}

void RestrictionProcessor::processBlock(AudioSampleBuffer &buffer)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    float** channelData = buffer.getArrayOfWritePointers();

    for (int j = 0; j < numSamples; ++j)
    {
        const float targetGain = static_cast<float>(m_currentAngle <= kDuty);

        m_smoothing->setValue(targetGain);
        const float gain = m_smoothing->getNextValue();

        for (int i = 0; i < numChannels; ++i)
        {
            const float in = channelData[i][j];
            channelData[i][j] = m_alpha * gain * in + (1.0f - m_alpha) * in;
        }

        m_currentAngle = fmod(m_currentAngle + m_delta, 1.0);
    }
}

//==============================================================================
File RestrictionProcessor::getKeyFile()
{
    File reg = File::getSpecialLocation(File::userApplicationDataDirectory)
        .getChildFile("Application Support")
        .getChildFile("Creative Intent")
        .getChildFile("mxzero.key");

    if (!reg.existsAsFile())
        reg.create();

    DBG("Accessing key file:");
    DBG(reg.getFullPathName());
    return reg;
}

StringArray RestrictionProcessor::getValidKeyHashes()
{
    int size;
    const char* p = BinaryData::getNamedResource("public_keys", size);

    String keyFile(p, size);
    StringArray keys;

    keys.addTokens(keyFile, "\n", String());
    return keys;
}

void RestrictionProcessor::validateRegistration()
{
    File reg = getKeyFile();
    String key = reg.loadFileAsString().trim();

    SHA256 hash(key.toUTF8());

    StringArray validHashes = getValidKeyHashes();
    String digest = hash.toHexString();

    for (int i = 0; i < validHashes.size(); i++)
    {
        if (validHashes.getReference(i).equalsIgnoreCase(digest))
        {
            DBG("Validation successful! Unlocking...");
            m_alpha = 0.0f;
            break;
        }
    }
}