/*
  ==============================================================================

    SpectroscopeComponent.h
    Created: 8 Apr 2017 12:46:51pm
    Author:  Nick Thompson

  ==============================================================================
*/

#ifndef SPECTROSCOPECOMPONENT_H_INCLUDED
#define SPECTROSCOPECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SpectroscopeComponent    : public Component,
                                 private Timer
{
public:
    SpectroscopeComponent();
    ~SpectroscopeComponent();

    void paint (Graphics&) override;
    void resized() override;
    void timerCallback() override;

    void pushBuffer (AudioSampleBuffer& buffer);
    inline void pushSample (float sample);
    inline float windowSample (float sample, int sampleIndex, int windowSize);
    void setBaseColour (Colour c);

    enum {
        kFFTOrder = 10,
        kFFTSize = 1024, // 2^10
        kOutputSize = 512, // 1024 / 2
    };

private:
    float m_fifo [kFFTSize];
    float m_fftData [2 * kFFTSize];
    float m_outputData [kOutputSize];

    unsigned int m_fifoIndex;
    bool m_fftBlockReady;

    FFT m_forwardFFT;
    Colour m_baseColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectroscopeComponent)
};


#endif  // SPECTROSCOPECOMPONENT_H_INCLUDED
