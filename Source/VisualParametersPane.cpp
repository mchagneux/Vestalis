/*
  ==============================================================================

    VisualParametersPane.cpp
    Created: 16 Jan 2022 1:02:44pm
    Author:  mchag

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VisualParametersPane.h"

//==============================================================================
VisualParametersPane::VisualParametersPane(const juce::ValueTree& vPState, const juce::ValueTree& cState, juce::UndoManager& um):                                                                                                   visualParametersState(vPState),
                                                                                            controlsState(cState),
                                                                                            undoManager(um)
{

}

VisualParametersPane::~VisualParametersPane()
{
}

void VisualParametersPane::paint (juce::Graphics& g)
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
    g.drawText("VisualParametersPane", getLocalBounds(), juce::Justification::centred);
}

void VisualParametersPane::resized()
{

}
