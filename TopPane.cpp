/*
  ==============================================================================

    TopPane.cpp
    Created: 16 Jan 2022 1:14:29pm
    Author:  mchag

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TopPane.h"

//==============================================================================
TopPane::TopPane(const juce::ValueTree& v, juce::UndoManager& um, juce::OSCReceiver& oR): oscState(v), 
                                                                                        undoManager(um),
                                                                                        oscReceiver(oR)

{
    oscConnectionState.referTo(oscState.getPropertyAsValue(IDs::STATE, &undoManager));
    oscConnectionState.addListener(this);

    setOscStateLabelText();

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    appTitleLabel.setText("VESTALIS", juce::dontSendNotification);
    appTitleLabel.setJustificationType(juce::Justification::centred);
    manageOSCButton.setButtonText("Manage OSC");
    manageOSCButton.onClick = [this]
    {
        auto oscManager = std::make_unique<OSCManager>(oscState, undoManager, oscReceiver);
        oscManager->setSize(4 * getHeight(), 3 * getHeight());
        auto& calloutForOscManager = juce::CallOutBox::launchAsynchronously(std::move(oscManager), manageOSCButton.getScreenBounds(), nullptr);

    };
    manageShaderButton.setButtonText("Manage shader");
    addAndMakeVisible(appTitleLabel);
    addAndMakeVisible(manageShaderButton);
    addAndMakeVisible(manageOSCButton);
    addAndMakeVisible(oscConnectionStateLabel);



}

TopPane::~TopPane()
{
}

void TopPane::paint (juce::Graphics& g)
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

void TopPane::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    auto area = getLocalBounds();
    auto width = getWidth();
    int appTitleAreaWidth = 0.4 * getWidth();
    int buttonsAreaWidth = (width - appTitleAreaWidth) / 2;
    int buttonsMarginX = (0.5 * buttonsAreaWidth) / 2;
    int buttonsMarginY = (0.4 * getHeight()) / 2;
    manageOSCButton.setBounds(area.removeFromLeft(buttonsAreaWidth).reduced(buttonsMarginX,buttonsMarginY));
    oscConnectionStateLabel.attachToComponent(&manageOSCButton, true);
    appTitleLabel.setBounds(area.removeFromLeft(appTitleAreaWidth));
    manageShaderButton.setBounds(area.reduced(buttonsMarginX,buttonsMarginY));
    
}
