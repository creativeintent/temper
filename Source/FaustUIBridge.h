/*
  ==============================================================================

    FaustUIBridge.h
    Created: 9 Feb 2017 5:59:55pm
    Author:  Nick Thompson

  ==============================================================================
*/

#ifndef FAUSTUIBRIDGE_H_INCLUDED
#define FAUSTUIBRIDGE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "faust/gui/UI.h"

class FaustUIBridgeListener : public AudioProcessorValueTreeState::Listener
{
public:
    FaustUIBridgeListener(float* zone) : m_zone(zone) {};
    virtual ~FaustUIBridgeListener() override {};

    virtual void parameterChanged (const String& parameterID, float newValue) override
    {
        *m_zone = newValue;
    };

private:
    float* m_zone;
};

//==============================================================================
/**
 This struct associates an AudioProcessorParameter id with a FaustUIBridgeListener
 object which as been attached to the valueTreeState.
 */
struct ParameterListenerPair
{
    //==============================================================================
    /** Constructor.

     @param parameterId    The String Id of the AudioProcessorParameter.

     @param listener       The attached FaustUIBridgeListener.
     */
    ParameterListenerPair(String parameterId, FaustUIBridgeListener* listener)
        : paramId(parameterId), listener(listener) {};

    String paramId;
    FaustUIBridgeListener* listener;
};

class FaustUIBridge : public UI
{

public:

    FaustUIBridge(AudioProcessorValueTreeState& vts);

    virtual ~FaustUIBridge() override;

    // -- widget's layouts

    virtual void openTabBox(const char* label) override {};
    virtual void openHorizontalBox(const char* label) override {};
    virtual void openVerticalBox(const char* label) override {};
    virtual void closeBox() override {};

    // -- active widgets

    virtual void addButton(const char* label, FAUSTFLOAT* zone) override {};
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) override {};
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {};
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override;
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) override {};

    // -- passive widgets

    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override {};
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) override {};

    // -- metadata declarations

    virtual void declare(FAUSTFLOAT*, const char*, const char*) override {};

private:
    // A reference to the AudioProcessor's value tree so that we can map the faust
    // UI parameters to AudioProcessor parameters.
    AudioProcessorValueTreeState& valueTreeState;

    // Maintain an array associating AudioProcessorParameters to the Listeners that have been
    // installed on those parameters.
    Array<ParameterListenerPair> listenerAssignments;

    // And an array of listeners to ensure the mapping between internal value tree values
    // match the float* zone members of the faust implementation.
    OwnedArray<AudioProcessorValueTreeState::Listener> listeners;
};

#endif  // FAUSTUIBRIDGE_H_INCLUDED
