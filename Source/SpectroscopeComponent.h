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
class SpectroscopeComponent    : public Component
{
public:
    SpectroscopeComponent();
    ~SpectroscopeComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectroscopeComponent)
};


#endif  // SPECTROSCOPECOMPONENT_H_INCLUDED
