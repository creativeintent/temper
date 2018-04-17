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

    void setColours (Colour strokeColour, Colour fillStartColour, Colour fillStopColour);

    enum {
        kFFTOrder = 12,
        kFFTSize = 4096, // 2^12
        kOutputSize = 2048, // 4096 / 2
    };

private:
    float m_fifo [kFFTSize];
    float m_fftData [2 * kFFTSize];
    float m_outputData [kOutputSize];

    unsigned int m_fifoIndex;
    bool m_fftBlockReady;

    juce::dsp::FFT m_forwardFFT;
    juce::dsp::WindowingFunction<float> m_window;

    Colour m_strokeColour;
    Colour m_fillStartColour;
    Colour m_fillStopColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectroscopeComponent)
};


#endif  // SPECTROSCOPECOMPONENT_H_INCLUDED
