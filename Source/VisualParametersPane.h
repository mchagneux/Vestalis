/*
  ==============================================================================

    VisualParametersPane.h
    Created: 16 Jan 2022 1:02:44pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class VisualParametersPane  : public juce::Component
{
public:
    VisualParametersPane(const juce::ValueTree& vPState, const juce::ValueTree& cState, juce::UndoManager& um);
    ~VisualParametersPane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ValueTree controlsState;
    juce::ValueTree visualParametersState;
    juce::UndoManager& undoManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualParametersPane)
};
