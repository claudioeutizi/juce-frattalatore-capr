/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Fractal.h"

//==============================================================================
/**
*/
class JuceTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceTestAudioProcessorEditor (JuceTestAudioProcessor&);
    ~JuceTestAudioProcessorEditor() override;
    

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void generateImage();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Rectangle<int> spaceBounds;
    juce::Image spaceImage;
    juce::Label titleLabel;
    Fractal fractal;

    JuceTestAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceTestAudioProcessorEditor)
};
