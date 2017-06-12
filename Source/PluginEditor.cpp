/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.0.2

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
StereoDelayAudioProcessorEditor::StereoDelayAudioProcessorEditor (StereoDelayAudioProcessor& ownerProc)
    : AudioProcessorEditor(ownerProc), processor(ownerProc)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (BypassBtn = new TextButton ("Bypass Button"));
    BypassBtn->setButtonText (TRANS("Bypass"));
    BypassBtn->addListener (this);
    BypassBtn->setColour (TextButton::buttonColourId, Colour (0xff307085));

    addAndMakeVisible (DelayTimeSld = new Slider ("Delay Time Slider"));
    DelayTimeSld->setRange (0, 10, 0);
    DelayTimeSld->setSliderStyle (Slider::LinearHorizontal);
    DelayTimeSld->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    DelayTimeSld->addListener (this);

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Delay Time")));
    label->setFont (Font ("Rockwell", 16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centred);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 350);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

StereoDelayAudioProcessorEditor::~StereoDelayAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    BypassBtn = nullptr;
    DelayTimeSld = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void StereoDelayAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void StereoDelayAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    BypassBtn->setBounds ((getWidth() / 2) + -75, 240, 150, 24);
    DelayTimeSld->setBounds (0, 72, proportionOfWidth (1.0000f), 24);
    label->setBounds (0, 45, proportionOfWidth (1.0000f), 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void StereoDelayAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == BypassBtn)
    {
        //[UserButtonCode_BypassBtn] -- add your button handler code here..
        //[/UserButtonCode_BypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void StereoDelayAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == DelayTimeSld)
    {
        //[UserSliderCode_DelayTimeSld] -- add your slider handling code here..
        //[/UserSliderCode_DelayTimeSld]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="StereoDelayAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="StereoDelayAudioProcessor&amp; ownerProc"
                 variableInitialisers="AudioProcessorEditor(ownerProc), processor(ownerProc)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="200" initialHeight="350">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="Bypass Button" id="ba2c685e2aad071b" memberName="BypassBtn"
              virtualName="" explicitFocusOrder="0" pos="-75C 240 150 24" bgColOff="ff307085"
              buttonText="Bypass" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Delay Time Slider" id="13f69adbd312b242" memberName="DelayTimeSld"
          virtualName="" explicitFocusOrder="0" pos="0 72 100% 24" min="0"
          max="10" int="0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="new label" id="a4c72bdb57082eb4" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 45 100% 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Rockwell" fontsize="16" kerning="0"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
