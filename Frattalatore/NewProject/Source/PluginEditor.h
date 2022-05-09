/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ProvaFractal/Fractal.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;
    

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void generateImage(juce::Image& image);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::Rectangle<int> rectangle;
    juce::Image fractalImage;
    juce::Label titleLabel;
    Fractal fractal;

    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
