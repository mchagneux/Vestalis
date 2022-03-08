/*
  ==============================================================================

    ControlsPane.h
    Created: 16 Jan 2022 1:03:06pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ValueTreeObjectList.h"
#include "Controls.h"
#include "Identifiers.h"
//==============================================================================
/*
*/

class ControlsPane  : public juce::Component

{

public:
    ControlsPane(const juce::ValueTree& controlsTree, juce::UndoManager& undoManager, juce::OSCReceiver& or);
    ~ControlsPane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton addOSCControlButton;
    juce::TextButton addManualControlButton;
    juce::ValueTree state;
    juce::UndoManager& undoManager;
    std::unique_ptr<ControlList> controlList;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsPane)
};
