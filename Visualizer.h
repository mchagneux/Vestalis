/*
  ==============================================================================

    Visualizer.h
    Created: 16 Jan 2022 1:12:30pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Visualizer  : public juce::Component
{
public:
    Visualizer();
    ~Visualizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Visualizer)
};
