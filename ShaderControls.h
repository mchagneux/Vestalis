#include <JuceHeader.h>
#include "Identifiers.h"


class ShaderControls : public Component, 
                    private CodeDocument::Listener
{
    public:
        ShaderControls(const ValueTree & shState): shaderState(shState) 
        {
            addAndMakeVisible (tabbedShaderEditorComp);
            tabbedShaderEditorComp.setTabBarDepth (25);
            tabbedShaderEditorComp.setColour (TabbedButtonBar::tabTextColourId, Colours::grey);
            tabbedShaderEditorComp.addTab ("Vertex", Colours::transparentBlack, &vertexShaderEditor, false);
            tabbedShaderEditorComp.addTab ("Fragment", Colours::transparentBlack, &fragmentShaderEditor, false);

            vertexShaderDoc.addListener(this);
            fragmentShaderDoc.addListener(this);
            compileButton.addAndMakeVisible(this);
            compileButton.setButtonText("Compile");
        }
        ~ShaderControls() override{};


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
            compileButton.setBounds(compileButtonBounds);
        }


    private:
        ValueTree shaderState; 
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
        ShaderControlsWindow(const ValueTree& shState, Colour backgroundColour, int buttonsNeeded): 
            DocumentWindow (juce::String("Shader controls"), backgroundColour, buttonsNeeded), 
            shaderControls(shState)
        {
            setContentOwned(&shaderControls, false);

        }
        ~ShaderControlsWindow() override{};

        void closeButtonPressed(){
            delete this;
        }

    private:
        ShaderControls shaderControls;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ShaderControlsWindow)


};
