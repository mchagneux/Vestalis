/*
  ==============================================================================

    VisualParameters.h
    Created: 8 Mar 2022 10:55:16pm
    Author:  mchag

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VisualParameter.h"

//==============================================================================
/*
*/




class VisualParametersList : public juce::Component,
                            public ValueTreeObjectList<VisualParameter>
{
public:
    VisualParametersList(const juce::ValueTree& vPState, juce::UndoManager& um) : ValueTreeObjectList<VisualParameter>(vPState), undoManager(um)

    {
        rebuildObjects();
    };
    ~VisualParametersList() override {
        deleteAllObjects();
    };

    void paint(juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour(juce::Colours::grey);
        g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

        g.setColour(juce::Colours::white);
        g.setFont(14.0f);
    }
    void resized() override
    {
        //This method is where you should set the bounds of any child
        //components that your component contains..
        auto area = getLocalBounds();
        auto parameterHeight = getHeight() / juce::jmax(1, objects.size());
        for (auto* parameter : objects) {
            parameter->setBounds(area.removeFromTop(parameterHeight));
        }

    }

    bool isSuitableType(const juce::ValueTree& valueTree) const
    {
        return valueTree.hasType(IDs::VISUAL_PARAMETER);
    };

    VisualParameter* createNewObject(const juce::ValueTree& valueTree)
    {
        if (isSuitableType(valueTree)) {
            auto* visualParameter = new VisualParameter(valueTree, undoManager);
            addAndMakeVisible(visualParameter);
            return visualParameter;

        }
    };

    void deleteObject(VisualParameter* visualParameter)
    {
        delete visualParameter;
    };
    void newObjectAdded(VisualParameter*)
    {
        resized();
    };
    void objectRemoved(VisualParameter*)
    {
        resized();
    };
    void objectOrderChanged()
    {
        resized();
    };


private:
    juce::UndoManager& undoManager;


};

class VisualParametersPane  : public juce::Component
{
public:
    VisualParametersPane(const juce::ValueTree& vPState, juce::UndoManager& um): visualParametersState(vPState), 
                                                                                 undoManager(um)
    {
        visualParametersList = std::make_unique<VisualParametersList>(visualParametersState, undoManager);
        addAndMakeVisible(*visualParametersList);
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~VisualParametersPane() override
    {
    }

    void paint (juce::Graphics& g) override
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
        g.drawText ("VisualParameters", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        visualParametersList->setBounds(getLocalBounds());
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    std::unique_ptr<VisualParametersList> visualParametersList;
    juce::ValueTree visualParametersState;
    juce::UndoManager& undoManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VisualParametersPane)
};
