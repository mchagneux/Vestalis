/*
  ==============================================================================

    BottomPane.h
    Created: 16 Jan 2022 6:26:19pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BottomPane  : public juce::Component
{
public:
    BottomPane(juce::UndoManager& um);
    ~BottomPane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton undoButton;
    juce::TextButton redoButton;
    juce::UndoManager& undoManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomPane)
};
