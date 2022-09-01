#include <JuceHeader.h>
#include "Identifiers.h"


class ShaderControls : public Component, 
                        private CodeDocument::Listener                        
{
    public:
        ShaderControls(const ValueTree & shState, UndoManager& uM): shaderState(shState), undoManager(uM)
        {
            addAndMakeVisible (tabbedShaderEditorComp);
            tabbedShaderEditorComp.setTabBarDepth (25);
            tabbedShaderEditorComp.setColour (TabbedButtonBar::tabTextColourId, Colours::grey);
            tabbedShaderEditorComp.addTab ("Vertex", Colours::transparentBlack, &vertexShaderEditor, false);
            tabbedShaderEditorComp.addTab ("Fragment", Colours::transparentBlack, &fragmentShaderEditor, false);


            vertexShaderDoc.replaceAllContent(shaderState.getProperty(IDs::VERTEX_SHADER));
            fragmentShaderDoc.replaceAllContent(shaderState.getProperty(IDs::FRAGMENT_SHADER));
            vertexShaderDoc.addListener(this);
            fragmentShaderDoc.addListener(this);
            
            compileButton.setButtonText("Compile");
            compileButton.onClick = [this]
            {
                shaderState.setProperty(IDs::VERTEX_SHADER, 
                                        vertexShaderDoc.getAllContent(),
                                        &undoManager);

                shaderState.setProperty(IDs::FRAGMENT_SHADER, 
                                        fragmentShaderDoc.getAllContent(),
                                        &undoManager);
            };
            addAndMakeVisible(compileButton);
        }
        ~ShaderControls() override 
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
        }


        void codeDocumentTextInserted (const String& /*newText*/, int /*insertIndex*/) override
        {

        }

        void codeDocumentTextDeleted (int /*startIndex*/, int /*endIndex*/) override
        {

        }

        void resized() override{
            auto bounds = getLocalBounds(); 
            auto compileButtonBounds = bounds.removeFromBottom(int(getHeight() / 8));
            tabbedShaderEditorComp.setBounds(bounds);
            compileButton.setBounds(compileButtonBounds.reduced(int(compileButtonBounds.getWidth() / 4), 
                                                                int(compileButtonBounds.getHeight() / 8)));
        }


    private:
        ValueTree shaderState; 
        UndoManager& undoManager;
        CodeDocument vertexShaderDoc, fragmentShaderDoc;
        CodeEditorComponent vertexShaderEditor {vertexShaderDoc, nullptr}, 
                            fragmentShaderEditor {fragmentShaderDoc, nullptr};

        TabbedComponent tabbedShaderEditorComp {TabbedButtonBar::TabsAtTop};
        TextButton compileButton;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShaderControls)
};

class ShaderControlsWindow : public DocumentWindow 
{

    public: 
        ShaderControlsWindow(const ValueTree& shState, UndoManager& um, Colour backgroundColour, int buttonsNeeded): 
            DocumentWindow (juce::String("Shader controls"), backgroundColour, buttonsNeeded), shaderControls(shState, um)
        {
            setContentOwned(&shaderControls, false);

        }
        ~ShaderControlsWindow() override{};

        void closeButtonPressed() override{

            delete this;
        }

    private:
        ShaderControls shaderControls;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShaderControlsWindow)


};
