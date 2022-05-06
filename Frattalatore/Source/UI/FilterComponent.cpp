/*
  ==============================================================================

    FilterComponent.cpp
    Created: 1 Apr 2021 1:30:00pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, 
    juce::String filterTypeSelectorId, juce::String filterCutOffId, 
    juce::String filterResId):
        cutOff("CutOff", filterCutOffId, apvts, dialWidth, dialHeight),
        resonance("Resonance", filterResId, apvts, dialWidth, dialHeight)        
{
    juce::StringArray filterTypeChoices{ "LPF", "BPF", "HPF" };
    typeSelector.addItemList(filterTypeChoices, 1);
    typeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(typeSelector);
    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, typeSelector);

    addAndMakeVisible(cutOff);
    addAndMakeVisible(resonance);

}

FilterComponent::~FilterComponent()
{
}


void FilterComponent::resized()
{
    const auto startX = 18;
    const auto startY = 80;
    const auto width = 70;
    const auto height = 88;

    typeSelector.setBounds(18, 40, 145, 25);
    cutOff.setBounds(startX, startY, width, height);
    resonance.setBounds(cutOff.getRight(), startY, width, height);
}