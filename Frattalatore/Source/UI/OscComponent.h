/*
  ==============================================================================

    OscComponent.h
    Created: 3 May 2022 12:41:18pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GuiComponent.h"
//==============================================================================
/*
*/
class OscComponent  : public GuiComponent
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, 
    juce::String waveSelectorId,
    juce::String gainId,
    juce::String pitchId,
    juce::String fmFreqId,
    juce::String fmDepthId);
    ~OscComponent() override;
    void resized() override;

private:
    juce::ComboBox oscTypeSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    SliderWithLabel gain;
    SliderWithLabel pitch;
    SliderWithLabel fmFreq;
    SliderWithLabel fmDepth;

    static constexpr int dialWidth = 70;
    static constexpr int dialHeight = 70;

protected:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
