/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent (AudioProcessorValueTreeState& vts)
    : m_vts(vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (m_cutoffSlider = new Slider ("Cutoff"));
    m_cutoffSlider->setRange (0, 10, 0);
    m_cutoffSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_cutoffSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_resoSlider = new Slider ("Resonance"));
    m_resoSlider->setRange (0, 10, 0);
    m_resoSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_resoSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_driveSlider = new Slider ("Drive"));
    m_driveSlider->setRange (0, 10, 0);
    m_driveSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_driveSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_curveSlider = new Slider ("Curve"));
    m_curveSlider->setRange (0, 10, 0);
    m_curveSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_curveSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_biasSlider = new Slider ("Bias"));
    m_biasSlider->setRange (0, 10, 0);
    m_biasSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_biasSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_feedbackSlider = new Slider ("Feedback"));
    m_feedbackSlider->setRange (0, 10, 0);
    m_feedbackSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_feedbackSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_gainSlider = new Slider ("Level"));
    m_gainSlider->setRange (0, 10, 0);
    m_gainSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    m_gainSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);

    addAndMakeVisible (m_filterGroup = new GroupComponent ("Filter Group",
                                                           TRANS("Filter")));

    addAndMakeVisible (m_distortionGroup = new GroupComponent ("Distortion Group",
                                                               TRANS("Distortion")));

    addAndMakeVisible (m_outputGroup = new GroupComponent ("Output Group",
                                                           TRANS("Output")));

    addAndMakeVisible (m_cutoffLabel = new Label ("Cutoff Label",
                                                  TRANS("Cutoff")));
    m_cutoffLabel->setFont (Font (15.00f, Font::plain));
    m_cutoffLabel->setJustificationType (Justification::centred);
    m_cutoffLabel->setEditable (false, false, false);
    m_cutoffLabel->setColour (TextEditor::textColourId, Colours::black);
    m_cutoffLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_resoLabel = new Label ("Resonance Label",
                                                TRANS("Resonance")));
    m_resoLabel->setFont (Font (15.00f, Font::plain));
    m_resoLabel->setJustificationType (Justification::centred);
    m_resoLabel->setEditable (false, false, false);
    m_resoLabel->setColour (TextEditor::textColourId, Colours::black);
    m_resoLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_driveLabel = new Label ("Drive Label",
                                                 TRANS("Drive")));
    m_driveLabel->setFont (Font (15.00f, Font::plain));
    m_driveLabel->setJustificationType (Justification::centred);
    m_driveLabel->setEditable (false, false, false);
    m_driveLabel->setColour (TextEditor::textColourId, Colours::black);
    m_driveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_curveLabel = new Label ("Curve Label",
                                                 TRANS("Curve")));
    m_curveLabel->setFont (Font (15.00f, Font::plain));
    m_curveLabel->setJustificationType (Justification::centred);
    m_curveLabel->setEditable (false, false, false);
    m_curveLabel->setColour (TextEditor::textColourId, Colours::black);
    m_curveLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_biasLabel = new Label ("Bias Label",
                                                TRANS("Bias")));
    m_biasLabel->setFont (Font (15.00f, Font::plain));
    m_biasLabel->setJustificationType (Justification::centred);
    m_biasLabel->setEditable (false, false, false);
    m_biasLabel->setColour (TextEditor::textColourId, Colours::black);
    m_biasLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_feedbackLabel = new Label ("Feedback Label",
                                                    TRANS("Feedback")));
    m_feedbackLabel->setFont (Font (15.00f, Font::plain));
    m_feedbackLabel->setJustificationType (Justification::centred);
    m_feedbackLabel->setEditable (false, false, false);
    m_feedbackLabel->setColour (TextEditor::textColourId, Colours::black);
    m_feedbackLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (m_gainLabel = new Label ("Gain Label",
                                                TRANS("Level")));
    m_gainLabel->setFont (Font (15.00f, Font::plain));
    m_gainLabel->setJustificationType (Justification::centred);
    m_gainLabel->setEditable (false, false, false);
    m_gainLabel->setColour (TextEditor::textColourId, Colours::black);
    m_gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 152);


    //[Constructor] You can add your own custom stuff here..
    filterFreqAttachment = new SliderAttachment(m_vts, "filterfc", *m_cutoffSlider);
    filterResoAttachment = new SliderAttachment(m_vts, "filterq", *m_resoSlider);
    driveAttachment = new SliderAttachment(m_vts, "drive", *m_driveSlider);
    curveAttachment = new SliderAttachment(m_vts, "curve", *m_curveSlider);
    offsetAttachment = new SliderAttachment(m_vts, "offset", *m_biasSlider);
    feedbackAttachment = new SliderAttachment(m_vts, "feedback", *m_feedbackSlider);
    levelAttachment = new SliderAttachment(m_vts, "level", *m_gainSlider);

    m_cutoffSlider->setTextValueSuffix("Hz");
    m_feedbackSlider->setTextValueSuffix("dB");
    m_gainSlider->setTextValueSuffix("dB");
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    m_cutoffSlider = nullptr;
    m_resoSlider = nullptr;
    m_driveSlider = nullptr;
    m_curveSlider = nullptr;
    m_biasSlider = nullptr;
    m_feedbackSlider = nullptr;
    m_gainSlider = nullptr;
    m_filterGroup = nullptr;
    m_distortionGroup = nullptr;
    m_outputGroup = nullptr;
    m_cutoffLabel = nullptr;
    m_resoLabel = nullptr;
    m_driveLabel = nullptr;
    m_curveLabel = nullptr;
    m_biasLabel = nullptr;
    m_feedbackLabel = nullptr;
    m_gainLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff7d7d7d));

    g.setColour (Colours::black);
    g.setFont (Font (15.00f, Font::plain));
    g.drawText (TRANS("Creative Intent // MXZero (Beta)"),
                491, 123, 200, 30,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    m_cutoffSlider->setBounds (10, 24, 80, 80);
    m_resoSlider->setBounds (110, 24, 80, 80);
    m_driveSlider->setBounds (210, 24, 80, 80);
    m_curveSlider->setBounds (310, 24, 80, 80);
    m_biasSlider->setBounds (410, 24, 80, 80);
    m_feedbackSlider->setBounds (510, 24, 80, 80);
    m_gainSlider->setBounds (610, 24, 80, 80);
    m_filterGroup->setBounds (0, 4, 200, 120);
    m_distortionGroup->setBounds (200, 4, 300, 120);
    m_outputGroup->setBounds (500, 4, 200, 120);
    m_cutoffLabel->setBounds (10, 96, 80, 20);
    m_resoLabel->setBounds (110, 96, 80, 20);
    m_driveLabel->setBounds (210, 96, 80, 20);
    m_curveLabel->setBounds (310, 96, 80, 20);
    m_biasLabel->setBounds (410, 96, 80, 20);
    m_feedbackLabel->setBounds (510, 96, 80, 20);
    m_gainLabel->setBounds (610, 96, 80, 20);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component" constructorParams="AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="m_vts(vts)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="700"
                 initialHeight="152">
  <BACKGROUND backgroundColour="ff7d7d7d">
    <TEXT pos="491 123 200 30" fill="solid: ff000000" hasStroke="0" text="Creative Intent // MXZero (Beta)"
          fontname="Default font" fontsize="15" bold="0" italic="0" justification="36"/>
  </BACKGROUND>
  <SLIDER name="Cutoff" id="80edd5c38c704dd5" memberName="m_cutoffSlider"
          virtualName="" explicitFocusOrder="0" pos="10 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Resonance" id="3bb5cf0ab68e9733" memberName="m_resoSlider"
          virtualName="" explicitFocusOrder="0" pos="110 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Drive" id="9909e31099819864" memberName="m_driveSlider"
          virtualName="" explicitFocusOrder="0" pos="210 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Curve" id="a56ea73f883bdf8f" memberName="m_curveSlider"
          virtualName="" explicitFocusOrder="0" pos="310 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Bias" id="a1e434d9a7eda8a0" memberName="m_biasSlider" virtualName=""
          explicitFocusOrder="0" pos="410 24 80 80" min="0" max="10" int="0"
          style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox" textBoxEditable="0"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1" needsCallback="0"/>
  <SLIDER name="Feedback" id="ecd475fce33f4b83" memberName="m_feedbackSlider"
          virtualName="" explicitFocusOrder="0" pos="510 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <SLIDER name="Level" id="bf47d1ef820213ea" memberName="m_gainSlider"
          virtualName="" explicitFocusOrder="0" pos="610 24 80 80" min="0"
          max="10" int="0" style="RotaryHorizontalVerticalDrag" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="0"/>
  <GROUPCOMPONENT name="Filter Group" id="a5abb9239816a691" memberName="m_filterGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 4 200 120" title="Filter"/>
  <GROUPCOMPONENT name="Distortion Group" id="35556008a08fe332" memberName="m_distortionGroup"
                  virtualName="" explicitFocusOrder="0" pos="200 4 300 120" title="Distortion"/>
  <GROUPCOMPONENT name="Output Group" id="14e24b16b0bac5ae" memberName="m_outputGroup"
                  virtualName="" explicitFocusOrder="0" pos="500 4 200 120" title="Output"/>
  <LABEL name="Cutoff Label" id="8c36484c7dd57b99" memberName="m_cutoffLabel"
         virtualName="" explicitFocusOrder="0" pos="10 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Cutoff" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Resonance Label" id="cc33e12b86f2a86a" memberName="m_resoLabel"
         virtualName="" explicitFocusOrder="0" pos="110 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Resonance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Drive Label" id="195ded46976233cb" memberName="m_driveLabel"
         virtualName="" explicitFocusOrder="0" pos="210 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Drive" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Curve Label" id="30073a37efa500cc" memberName="m_curveLabel"
         virtualName="" explicitFocusOrder="0" pos="310 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Curve" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Bias Label" id="e8a8527f3f6976cf" memberName="m_biasLabel"
         virtualName="" explicitFocusOrder="0" pos="410 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Bias" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Feedback Label" id="5547950683b7ca1f" memberName="m_feedbackLabel"
         virtualName="" explicitFocusOrder="0" pos="510 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Feedback" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Gain Label" id="719d91e31d43fa34" memberName="m_gainLabel"
         virtualName="" explicitFocusOrder="0" pos="610 96 80 20" edTextCol="ff000000"
         edBkgCol="0" labelText="Level" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
