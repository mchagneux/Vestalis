/*
  ==============================================================================

    BottomPane.cpp
    Created: 16 Jan 2022 6:26:19pm
    Author:  mchag

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BottomPane.h"

//==============================================================================
BottomPane::BottomPane(juce::UndoManager& um): undoManager(um)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    undoButton.setButtonText("Undo");
    redoButton.setButtonText("Redo");
    undoButton.onClick = [this] {
        undoManager.undo();
    };
    redoButton.onClick = [this] {undoManager.redo();};
    addAndMakeVisible(undoButton);
    addAndMakeVisible(redoButton);
    
}

BottomPane::~BottomPane()
{
}

void BottomPane::paint (juce::Graphics& g)
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

void BottomPane::resized()
{
    auto buttonAreaWidth = getWidth() / 2; 

    int marginX = 0.2 * buttonAreaWidth;
    int marginY = 0.2 * getHeight();

    auto area = getLocalBounds();
    undoButton.setBounds(area.removeFromLeft(buttonAreaWidth).reduced(marginX, marginY));    
    redoButton.setBounds(area.reduced(marginX, marginY));
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
