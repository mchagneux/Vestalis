/*
  ==============================================================================

    TopPane.h
    Created: 16 Jan 2022 1:14:29pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Identifiers.h"
#include "OSCManager.h" 
#include "ShaderControls.h"
//==============================================================================
/*
*/
class TopPane  : public juce::Component, public juce::Value::Listener
{
public:
    TopPane(const juce::ValueTree& v, juce::UndoManager& um, juce::OSCReceiver& oR);
    ~TopPane() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setOscStateLabelText() {
        juce::String text;
        auto isConnected = oscConnectionState.getValue();
        if (isConnected) { text = juce::String("Connected to UDP port ") + oscState.getProperty(IDs::OSC_PORT).toString() ; }
        else { text = "Disconnected"; }
        auto textColour = isConnected ? juce::Colours::green : juce::Colours::red;
        oscConnectionStateLabel.setText(text, juce::dontSendNotification);
        oscConnectionStateLabel.setFont(juce::Font(15.00f, juce::Font::bold));
        oscConnectionStateLabel.setColour(juce::Label::textColourId, textColour);
        oscConnectionStateLabel.setJustificationType(juce::Justification::centredRight);
    }
    void valueChanged(juce::Value& value) {
        setOscStateLabelText();
    }

private:
    juce::OSCReceiver& oscReceiver;
    juce::ValueTree oscState;
    juce::ValueTree shaderState;
    juce::Value oscConnectionState;
    juce::UndoManager& undoManager;
    juce::TextButton manageShaderButton;
    juce::TextButton manageOSCButton;
    juce::Label oscConnectionStateLabel;
    juce::Label appTitleLabel;
    Component::SafePointer<ShaderControlsWindow> shaderControlsWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopPane)
};
