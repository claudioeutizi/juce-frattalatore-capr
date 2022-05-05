/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class FrattalatoreAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FrattalatoreAudioProcessorEditor (FrattalatoreAudioProcessor&);
    ~FrattalatoreAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    FrattalatoreAudioProcessor& audioProcessor;
    AdsrComponent adsr;
    OscComponent osc;
    FilterComponent filter;
    AdsrComponent modAdsr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrattalatoreAudioProcessorEditor)
};
