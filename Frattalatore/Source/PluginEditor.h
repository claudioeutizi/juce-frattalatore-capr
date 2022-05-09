/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/CustomLookAndFeel.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"
#include "UI/AdsrComponent.h"
#include "UI/LfoComponent.h"


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
    OscComponent osc1, osc2, osc3, osc4, osc5;
    FilterComponent filter;
    AdsrComponent adsr;
    LfoComponent lfo;
    CustomLookAndFeel customLookAndFeel;
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    juce::Image backgroundImage;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrattalatoreAudioProcessorEditor)
};
