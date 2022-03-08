#include "MainComponent.h"

//==============================================================================

MainComponent::MainComponent() : app(juce::ValueTree(IDs::APP)),
                                 bottomPane(undoManager)                                     
{

    
    auto OSCState = juce::ValueTree(IDs::OSC_RECEIVER);  
    OSCState.setProperty(IDs::STATE, "Disconnected", nullptr);
    OSCState.setProperty(IDs::OSC_PORT, 9901, nullptr);

    app.appendChild(OSCState, nullptr);
    app.appendChild(juce::ValueTree(IDs::CONTROLS), nullptr);

    auto visualParametersState = juce::ValueTree(IDs::VISUAL_PARAMETERS);
    auto visualParameter = juce::ValueTree(IDs::VISUAL_PARAMETER);
    visualParameter.setProperty(IDs::VISUAL_PARAMETER_NAME, "iTime", nullptr);
    visualParametersState.appendChild(visualParameter, nullptr);
    app.appendChild(visualParametersState, nullptr);

    controlsPane = std::make_unique<ControlsPane>(  app.getChildWithName(IDs::CONTROLS), 
                                                    undoManager, 
                                                    oscReceiver );

    topPane = std::make_unique<TopPane>(    app.getChildWithName(IDs::OSC_RECEIVER), 
                                            undoManager, 
                                            oscReceiver );

    visualParametersPane = std::make_unique<VisualParametersPane>(  app.getChildWithName(IDs::VISUAL_PARAMETERS), 
                                                                    undoManager );
    addAndMakeVisible(*visualParametersPane);
    addAndMakeVisible(*topPane);
    addAndMakeVisible(bottomPane);
    addAndMakeVisible(visualizer);
    addAndMakeVisible(*controlsPane);
    setSize(600, 400);

}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    auto area = getLocalBounds();
    
    topPane->setBounds(area.removeFromTop(0.1 * getHeight()));
    bottomPane.setBounds(area.removeFromBottom(0.05 * getHeight()));
    auto controlArea = area.removeFromLeft(0.2 * getWidth());
    controlsPane->setBounds(controlArea);
    visualizer.setBounds(area.removeFromLeft(0.6 * getWidth()));
    visualParametersPane->setBounds(area);
}