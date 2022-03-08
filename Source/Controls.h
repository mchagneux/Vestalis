/*
  ==============================================================================

    Controls.h
    Created: 23 Jan 2022 2:15:50pm
    Author:  mchag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ValueTreeObjectList.h"
#include "Identifiers.h"


//struct ValueTreePropertyChangeListener : public juce::ValueTree::Listener
//{
//    void valueTreeChildAdded(juce::ValueTree&, juce::ValueTree&) override {}
//    void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) override {}
//    void valueTreeChildOrderChanged(juce::ValueTree&, int, int) override {}
//    void valueTreeParentChanged(juce::ValueTree&) override {}
//    void valueTreeRedirected(juce::ValueTree&) override {}
//};


struct Control : public juce::Component, 
                 private juce::ValueTree::Listener
               
{
    Control(const juce::ValueTree& v, juce::UndoManager& um): state(v), undoManager(um)
    {
        state.addListener(this);
        deleteButton.setButtonText("Delete");
        deleteButton.onClick = [this] 
        { 
            undoManager.beginNewTransaction("Delete control");
            state.getParent().removeChild(state, &undoManager); 
        };
        controlNameLabel.setEditable(true);
        controlNameLabel.setJustificationType(juce::Justification::centred);
        controlNameLabel.onTextChange = [this] 
        { 
            undoManager.beginNewTransaction("Change control name");
            state.setProperty(IDs::CONTROL_NAME, controlNameLabel.getText(), &undoManager); 
        };
        if (!state.hasProperty(IDs::CONTROL_NAME)) { setInitControlName(); }
        controlNameLabel.setText(v.getProperty(IDs::CONTROL_NAME).toString(), juce::dontSendNotification);
        controlNameLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(controlNameLabel);
        addAndMakeVisible(deleteButton);
    }
    ~Control() override
    {

    }
    void setInitControlName()
    {
        state.setProperty(IDs::CONTROL_NAME, "Control " + juce::String(state.getParent().getNumChildren()), nullptr);
    }

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

    void resized() override {
        auto componentHeight = getHeight() / 4;
        auto marginY = componentHeight / 4;
        auto marginX = getWidth() / 4;
        controlNameLabel.setBounds(getLocalBounds().removeFromTop(componentHeight).reduced(marginX, marginY));
        deleteButton.setBounds(getLocalBounds().removeFromBottom(componentHeight).reduced(marginX, marginY));
    }


    void valueTreePropertyChanged(juce::ValueTree& v, const juce::Identifier& i) override
    {
        if (v == state && i == IDs::CONTROL_NAME) 
        {
            controlNameLabel.setText(v.getProperty(IDs::CONTROL_NAME).toString(), juce::dontSendNotification);
            repaint();
        }
    }


juce::ValueTree state;
juce::UndoManager& undoManager;

private: 
    juce::Label controlNameLabel;
    juce::TextButton deleteButton;
};

struct ManualControl : public Control,
                       private juce::Slider::Listener {

    ManualControl(const juce::ValueTree& v, juce::UndoManager& um) : Control(v, um)
    {
        slider.addListener(this);
        addAndMakeVisible(slider);

    }

    ~ManualControl() override
    {

    }

    void sliderValueChanged(juce::Slider * slider) override
    {

    }

    void resized() override {
        Control::resized();
        auto area = getLocalBounds();
        slider.setBounds(getLocalBounds().reduced(0, getHeight() / 4));
    }


private: 
    juce::Slider slider; 
};

struct OSCControl : public Control, 
                    private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>,
                    private juce::Value::Listener
{
   
    OSCControl(const juce::ValueTree& v, juce::UndoManager& um, juce::OSCReceiver& or) : Control(v, um), oscReceiver(or)
    {
        if (!state.hasProperty(IDs::OSC_ADDRESS)) { setInitOSCAddress(); }
        oscAddress.referTo(state.getPropertyAsValue(IDs::OSC_ADDRESS, &undoManager));
        oscAddress.addListener(this);

        oscReceiver.addListener(this, oscAddress.getValue().toString());

        oscAddressLabel.setText("OSC address:", juce::dontSendNotification);
        oscAddressLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(oscAddressLabel);


        oscAddressInput.setEditable(true);
        oscAddressInput.setJustificationType(juce::Justification::centred);
        oscAddressInput.setText(oscAddress.getValue(), juce::dontSendNotification);
        oscAddressInput.onTextChange = [this]
        {
            undoManager.beginNewTransaction("Change OSC address...");
            oscAddress = oscAddressInput.getText();
        };
        addAndMakeVisible(oscAddressInput);

        oscContentLabel.setJustificationType(juce::Justification::centred);
        addAndMakeVisible(oscContentLabel);

    }

    ~OSCControl() override
    {
        oscReceiver.removeListener(this);
    }
    void oscMessageReceived(const juce::OSCMessage& message) 
    {
        oscContentLabel.setText(juce::String(message[0].getFloat32()), juce::dontSendNotification);
    }

    void valueChanged(juce::Value& value)
    {
        oscContentLabel.setText("", juce::dontSendNotification);
        oscReceiver.removeListener(this);
        oscReceiver.addListener(this, value.getValue().toString());
    }



    void resized() override 
    {
        Control::resized();
        auto area = getLocalBounds();
        area.removeFromTop(getHeight() / 4);
        auto oscAddressPartsArea = area.removeFromTop(getHeight() / 4);
        oscAddressLabel.setBounds(oscAddressPartsArea.removeFromLeft(getWidth() / 2).reduced(0, oscAddressPartsArea.getHeight() / 4));
        oscAddressInput.setBounds(oscAddressPartsArea.reduced(oscAddressPartsArea.getWidth() / 8, oscAddressPartsArea.getHeight() /4));
        auto oscContentArea = area.removeFromTop(getHeight() / 4);
        oscContentLabel.setBounds(oscContentArea.reduced(oscContentArea.getWidth() / 4, oscContentArea.getHeight() / 4));


    }

    void setInitOSCAddress()
    {
        int numOSCControls = 0;
        for (auto& control : state.getParent()) {
            if (control.hasType(IDs::OSC_CONTROL)) numOSCControls++; 
        }
        state.setProperty(IDs::OSC_ADDRESS, "/vestalis/address" + juce::String(numOSCControls), nullptr);

    }

private: 
    juce::Value oscAddress;
    juce::Label oscAddressInput;
    juce::Label oscAddressLabel;
    juce::OSCReceiver& oscReceiver;
    juce::Label oscContentLabel;

};

class ControlList : public juce::Component,
                    public ValueTreeObjectList<Control>
{
public:
    ControlList(const juce::ValueTree& controlsTree, juce::UndoManager& um, juce::OSCReceiver& or) : ValueTreeObjectList<Control>(controlsTree), undoManager(um), oscReceiver(or)

    {
        rebuildObjects();
    };
    ~ControlList() override {
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
        g.drawText("ControlList", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }
    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
        auto area = getLocalBounds();
        auto controlHeight = getHeight() / juce::jmax(1, objects.size());
        for (auto* control : objects) {
            control->setBounds(area.removeFromTop(controlHeight));
        }

    }

    bool isSuitableType(const juce::ValueTree& valueTree) const
    {
        return valueTree.hasType(IDs::MANUAL_CONTROL) || valueTree.hasType(IDs::OSC_CONTROL);
    };

    Control* createNewObject(const juce::ValueTree& valueTree)
    {

        if (valueTree.hasType(IDs::MANUAL_CONTROL)) {
            auto* control = new ManualControl(valueTree, undoManager);
            addAndMakeVisible(control);
            return control;
        }
        else{
            auto* control = new OSCControl(valueTree, undoManager, oscReceiver);
            addAndMakeVisible(control);
            return control;
        }

    };
    
    void deleteObject(Control* control)
    {
        delete control;
    };
    void newObjectAdded(Control*)
    {
        resized();
    };
    void objectRemoved(Control*)
    {
        resized();
    };
    void objectOrderChanged() 
    {
        resized();
    };


private:
    juce::UndoManager& undoManager;
    juce::OSCReceiver& oscReceiver;


};
