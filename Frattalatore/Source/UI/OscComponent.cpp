/*
  ==============================================================================
    OscComponent.cpp
    Created: 5 May 2022 4:55:21pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli
  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,
    juce::String waveSelectorId,
    juce::String gainId,
    juce::String pitchId,
    juce::String fmFreqId,
    juce::String fmDepthId) :
    gain("Gain", gainId, apvts, dialWidth, dialHeight),
    pitch("Pitch", pitchId, apvts, dialWidth, dialHeight),
    fmFreq("FM Freq", fmFreqId, apvts, dialWidth, dialHeight),
    fmDepth("FM Depth", fmDepthId, apvts, dialWidth, dialHeight)
{
    juce::StringArray oscChoices { "Sine", "Saw", "Square" };
    oscTypeSelector.addItemList(oscChoices, 1);
    oscTypeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(oscTypeSelector);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscTypeSelector);
    addAndMakeVisible(gain);
    addAndMakeVisible(pitch);
    addAndMakeVisible(fmFreq);
    addAndMakeVisible(fmDepth);
}

OscComponent::~OscComponent()
{
}


void OscComponent::resized()
{
    const auto yStart = 15;
    const auto width = 70;
    const auto height = 88;

    oscTypeSelector.setBounds(18, 40, 100, 25);
    gain.setBounds(120, yStart, width, height);
    pitch.setBounds(190, yStart, width, height);
    fmFreq.setBounds(260, yStart, width, height);
    fmDepth.setBounds(330, yStart, width, height);
}
