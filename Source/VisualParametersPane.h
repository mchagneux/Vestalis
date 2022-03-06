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
    VisualParametersPane();
    ~VisualParametersPane() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualParametersPane)
};
