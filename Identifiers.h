/*
  ==============================================================================

    Identifiers.h
    Created: 18 Jan 2022 3:47:50pm
    Author:  mchag

  ==============================================================================
*/
#include "JuceHeader.h"

#pragma once

namespace IDs

{
#define DECLARE_ID(name) const juce::Identifier name (#name);

    DECLARE_ID(APP)

    DECLARE_ID(CONTROLS)
    DECLARE_ID(MANUAL_CONTROL)
    DECLARE_ID(OSC_CONTROL)
    DECLARE_ID(CONTROL_NAME)
    DECLARE_ID(CONTROL_VALUE)
    DECLARE_ID(OSC_ADDRESS)
    DECLARE_ID(OSC_RECEIVER)
    DECLARE_ID(STATE)
    DECLARE_ID(OSC_PORT)

    DECLARE_ID(VISUAL_PARAMETERS)
    DECLARE_ID(VISUAL_PARAMETER)
    DECLARE_ID(VISUAL_PARAMETER_NAME)
    DECLARE_ID(BINDED_CONTROL)

    DECLARE_ID(SHADERS)
    DECLARE_ID(VERTEX_SHADER)
    DECLARE_ID(FRAGMENT_SHADER)
    DECLARE_ID(PLAIN_GEOMETRY)

#undef DECLARE_ID
}
