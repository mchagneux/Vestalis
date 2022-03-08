/*
  ==============================================================================

    ControlsPane.cpp
    Created: 16 Jan 2022 1:03:06pm
    Author:  mchag

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ControlsPane.h"

//==============================================================================
ControlsPane::ControlsPane(const juce::ValueTree& controlsTree, juce::UndoManager& um, juce::OSCReceiver& or) : state(controlsTree), undoManager(um)
{
    addAndMakeVisible(*(controlList = std::make_unique<ControlList>(state, undoManager, or)));

    addOSCControlButton.setButtonText("Add OSC control");
    addOSCControlButton.onClick = [this] 
    { 
        undoManager.beginNewTransaction("Add OSC control");
        juce::ValueTree newOSCControl(IDs::OSC_CONTROL);
        newOSCControl.setProperty(IDs::OSC_ADDRESS, "/juce/address", nullptr);
        newOSCControl.setProperty(IDs::CONTROL_NAME, "<control-name>", nullptr);
        state.appendChild(newOSCControl, &undoManager);
    };

    addManualControlButton.setButtonText("Add manual control");
    addManualControlButton.onClick = [this]
    {

        undoManager.beginNewTransaction("Add manual control");
        juce::ValueTree newManualControl(IDs::MANUAL_CONTROL);
        newManualControl.setProperty(IDs::CONTROL_NAME, "<control-name>", nullptr);
        state.appendChild(newManualControl, &undoManager);
    };
    addAndMakeVisible(addOSCControlButton);
    addAndMakeVisible(addManualControlButton);

}

ControlsPane::~ControlsPane()
{
}

void ControlsPane::paint (juce::Graphics& g)
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

void ControlsPane::resized()

{
    double controlsAreaRelativeHeight = 0.95;
    auto area = getLocalBounds();
    controlList->setBounds(area.removeFromTop(controlsAreaRelativeHeight * getHeight()));
    int marginX = 0.05 * getWidth();
    int marginY = 0.2 * area.getHeight();
    addOSCControlButton.setBounds(area.removeFromLeft(getWidth()/2).reduced(marginX, marginY));
    addManualControlButton.setBounds(area.removeFromLeft(getWidth() / 2).reduced(marginX, marginY));

}
