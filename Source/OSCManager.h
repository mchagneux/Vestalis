/*
  ==============================================================================

    OSCManager.h
    Created: 5 Mar 2022 5:49:57pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Identifiers.h"
//==============================================================================
/*
*/
class OSCManager : public juce::Component, public juce::Value::Listener

{
public:
    OSCManager(const juce::ValueTree& os, juce::UndoManager& um, juce::OSCReceiver& or):oscState(os), 
                                                                                        undoManager(um), 
                                                                                        oscReceiver(or)    
    {
        oscConnectionState.referTo(oscState.getPropertyAsValue(IDs::STATE, &undoManager));
        oscConnectionState.addListener(this);

        oscPortLabel.setText("OSC Port", juce::dontSendNotification);
        oscPortLabel.attachToComponent(&oscPortLabelInput, true);
        oscPortLabelInput.setEditable(true);
        oscPortLabelInput.setText(oscState.getProperty(IDs::OSC_PORT), juce::dontSendNotification);
        oscPortLabelInput.onTextChange = [this]
        {
            disconnect();
            oscState.setProperty(IDs::OSC_PORT, oscPortLabelInput.getText(), &undoManager);
        };
        oscConnectDisconnectButton.setButtonText(getConnectDisconnectText());
        oscConnectDisconnectButton.onClick = [this]
        {
            if (!oscConnectionState.getValue()) {
                connect();
            }

            else
            {
                disconnect();
            }
           
        };
        addAndMakeVisible(oscPortLabel);
        addAndMakeVisible(oscPortLabelInput);
        addAndMakeVisible(oscConnectDisconnectButton);

        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
    }

    ~OSCManager() override
    {

    }

    juce::String getConnectDisconnectText() 
    {
        if (oscConnectionState.getValue()) { return "Disconnect";}
        else { return "Connect"; }
    }
    void valueChanged(juce::Value& value) {
        oscConnectDisconnectButton.setButtonText(getConnectDisconnectText());
    }

    
    void connect() 
    {
        if (oscReceiver.connect(oscState.getProperty(IDs::OSC_PORT))) { oscConnectionState.setValue(true); }

    }

    void disconnect()
    {
        if (oscReceiver.disconnect()) { oscConnectionState.setValue(false); }

    }
    
    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        //g.drawText ("OSCManager", getLocalBounds(),
        //            juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        auto area = getLocalBounds();
        oscPortLabelInput.setBounds(area.removeFromTop(getHeight() / 2).removeFromRight(getWidth()/2));
        oscConnectDisconnectButton.setBounds(area.reduced(area.getWidth() / 4, area.getHeight() / 4));

    }

private:
    juce::OSCReceiver& oscReceiver;
    juce::UndoManager& undoManager;
    juce::ValueTree oscState;
    juce::Value oscConnectionState;
    juce::Label oscPortLabel;
    juce::Label oscPortLabelInput;
    juce::TextButton oscConnectDisconnectButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCManager)
};
