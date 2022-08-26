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
Visualizer::Visualizer()
{
  setOpaque (true);
  openGLContext.setRenderer (this);
  openGLContext.attachTo (*this);
  openGLContext.setContinuousRepainting (true);

}

Visualizer::~Visualizer()
{
}