/*
  ==============================================================================

    SpectroscopeComponent.cpp
    Created: 8 Apr 2017 12:46:51pm
    Author:  Nick Thompson

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectroscopeComponent.h"

//==============================================================================
SpectroscopeComponent::SpectroscopeComponent()
:   m_fifoIndex(0),
    m_fftBlockReady(false),
    m_forwardFFT(kFFTOrder, false)
{
    zeromem(m_outputData, sizeof(m_outputData));
    setSize(700, 200);
    startTimerHz(60);
}

SpectroscopeComponent::~SpectroscopeComponent()
{
}

void SpectroscopeComponent::paint (Graphics& g)
{
    const float width = (float) getWidth();
    const float height = (float) getHeight();
    const float xScale = width / (float) kFFTSize;

    Path p;
    p.startNewSubPath(0.0f, 0.0f);

    for (int i = 0; i < kFFTSize; ++i)
    {
        const float x = (float) i * xScale;
        const float y = height - height * m_outputData[i];
        p.lineTo(x, y);
    }

    g.setColour(Colours::black);
    g.fillAll();
    g.setColour(Colours::green);
    g.strokePath(p, PathStrokeType(1.0f));
}

void SpectroscopeComponent::resized()
{
}

void SpectroscopeComponent::timerCallback()
{
    if (m_fftBlockReady)
    {
        // Compute the frequency transform
        m_forwardFFT.performFrequencyOnlyForwardTransform(m_fftData);

        // Copy the frequency bins into the output data buffer, taking
        // max(output[i], fftData[i]) for each bin.
        FloatVectorOperations::max(m_outputData, m_outputData, m_fftData, kFFTSize);

        m_fftBlockReady = false;
    }

    // Decay the output bin magnitudes
    for (int i = 0; i < kFFTSize; ++i)
        m_outputData[i] *= 0.707f;

    repaint();
}

void SpectroscopeComponent::pushBuffer(AudioSampleBuffer &buffer)
{
    if (buffer.getNumChannels() > 0)
    {
        const int numSamples = buffer.getNumSamples();
        const float* channelData = buffer.getReadPointer(0);

        for (int i = 0; i < numSamples; ++i)
            pushSample(channelData[i]);
    }
}

inline void SpectroscopeComponent::pushSample(float sample)
{
    // When we wrap around the fifo table, we copy the data into the
    // FFT buffer and prepare to perform the transform.
    if (m_fifoIndex == kFFTSize)
    {
        if (!m_fftBlockReady)
        {
            zeromem(m_fftData, sizeof(m_fftData));
            memcpy(m_fftData, m_fifo, sizeof(m_fifo));
            m_fftBlockReady = true;
        }

        m_fifoIndex = 0;
    }

    m_fifo[m_fifoIndex++] = sample;
}
