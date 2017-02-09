/*
  ==============================================================================

    FaustUIBridge.cpp
    Created: 9 Feb 2017 5:59:55pm
    Author:  Nick Thompson

  ==============================================================================
*/

#include "FaustUIBridge.h"

FaustUIBridge::FaustUIBridge(AudioProcessorValueTreeState& vts)
: valueTreeState(vts)
{
}

FaustUIBridge::~FaustUIBridge()
{
}

void FaustUIBridge::addHorizontalSlider(const char *label, float *zone, float init, float min, float max, float step)
{
    // Create the AudioProcessor parameter
    valueTreeState.createAndAddParameter(label, label, String(), NormalisableRange<float>(min, max), init, nullptr, nullptr);

    // Attach the listener to keep the internal dsp values up to date
    FaustUIBridgeListener* l = new FaustUIBridgeListener(zone);
    listeners.add(l);
    valueTreeState.addParameterListener(label, l);
}
