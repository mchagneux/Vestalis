/*
  ==============================================================================

    VisualParameter.h
    Created: 8 Mar 2022 11:03:14pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Identifiers.h"
//==============================================================================
/*
*/
class VisualParameter  : public juce::Component,
                        public juce::Value::Listener, 
                        public juce::ValueTree::Listener
{
public:
    VisualParameter(const juce::ValueTree& v, juce::UndoManager& um): state(v), undoManager(um), controlsState(v.getRoot().getChildWithName(IDs::CONTROLS))
    {
        controlsState.addListener(this);
        parameterNameLabel.setText(v.getProperty(IDs::VISUAL_PARAMETER_NAME), juce::dontSendNotification);
        receivedValue.setText("<received-value>", juce::dontSendNotification);
        receivedValue.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(parameterNameLabel);
        fillDropDown();
        addAndMakeVisible(availableControlsDropDown);
        addAndMakeVisible(receivedValue);
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~VisualParameter() override
    {
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
    }

    void resized() override
    {
        auto area = getLocalBounds();
        auto parameterNameArea = area.removeFromLeft(getWidth() / 2);
        auto dropDownArea = area.removeFromTop(2 * getHeight() / 3).removeFromBottom(getHeight() / 3);
        auto receivedValueArea = getLocalBounds().removeFromBottom(getHeight() / 3);
        parameterNameLabel.setBounds(parameterNameArea.reduced(parameterNameArea.getWidth() / 4, parameterNameArea.getHeight() / 4));
        availableControlsDropDown.setBounds(dropDownArea.reduced(dropDownArea.getWidth() / 4, dropDownArea.getHeight() / 3));

        receivedValue.setBounds(receivedValueArea.reduced(receivedValueArea.getWidth() / 4, receivedValueArea.getHeight() / 4));
        
    }

    
    void fillDropDown() {
        int item_id = 0;
        for (auto control : controlsState)
        {
            availableControlsDropDown.addItem(control.getProperty(IDs::CONTROL_NAME), ++item_id);
        }
    }

    void valueChanged(juce::Value& value)
    {

    }

    void addControlToDropDown() 
    {

    }

    void removeControlFromDropDown()
    {

    }

    void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override { addControlToDropDown(); }
    void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) override { removeControlFromDropDown(); }

    void valueTreeChildOrderChanged(juce::ValueTree&, int, int) override {}
    void valueTreeParentChanged(juce::ValueTree&) override {}
    void valueTreeRedirected(juce::ValueTree&) override {}

juce::ValueTree state;

private:
    juce::ValueTree controlsState;
    juce::Value controlValueToListenTo; 
    juce::UndoManager& undoManager;
    juce::Label parameterNameLabel;
    juce::Label receivedValue;
    juce::ComboBox availableControlsDropDown;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualParameter)
};
