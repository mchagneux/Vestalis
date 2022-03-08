#pragma once

#include <JuceHeader.h>
#include "ControlsPane.h"
#include "VisualParameters.h"
#include "Visualizer.h"
#include "TopPane.h"
#include "BottomPane.h"
#include "Identifiers.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ValueTree app;

    std::unique_ptr<ControlsPane> controlsPane;
    BottomPane bottomPane;
    std::unique_ptr<TopPane> topPane;
    Visualizer visualizer;
    std::unique_ptr<VisualParametersPane> visualParametersPane;

    juce::OSCReceiver oscReceiver;
    juce::UndoManager undoManager;

    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
