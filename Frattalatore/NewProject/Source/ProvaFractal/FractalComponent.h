/*
  ==============================================================================

    FractalComponent.h
    Created: 9 May 2022 11:53:16am
    Author:  claud

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Fractal.h"

//==============================================================================
/*
*/
class FractalComponent  : public juce::Component
{
public:
    FractalComponent();
    ~FractalComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Fractal fractal;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FractalComponent)
};
