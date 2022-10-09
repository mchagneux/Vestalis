/*
  ==============================================================================

    Visualizer.cpp
    Created: 16 Jan 2022 1:12:30pm
    Author:  mchag

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Visualizer.h"

//==============================================================================
Visualizer::Visualizer(const juce::ValueTree& shState): shaderState(shState)
{
  shaderState.addListener(this);
  if (auto * peer = getPeer())
      peer->setCurrentRenderingEngine (1);

  setOpaque (true);
  openGLContext.setRenderer (this);
  openGLContext.setComponentPaintingEnabled(false);
  openGLContext.attachTo (*this);
  openGLContext.setContinuousRepainting (true);
  // statusLabel.setText("Init text.", dontSendNotification);
  // addAndMakeVisible(statusLabel);
}

Visualizer::~Visualizer()
{
  openGLContext.detach();
}