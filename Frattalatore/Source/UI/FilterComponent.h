/*
  ==============================================================================

    FilterComponent.h
    Created: 4 May 2022 5:27:45pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, 
        juce::String filterFreqId, juce::String filterResId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypeSelector{"Filter Type"};
    juce::Slider filterCutOffSlider;
    juce::Slider filterResonanceSlider;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<Attachment> filterCutOffAttachment;
    std::unique_ptr<Attachment> filterResonanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeSelectorAttachment;

    juce::Label filterTypeSelectorLabel{ "Filter Type", "Filter Type" };
    juce::Label filterCutOffLabel{ "CutOff Freq", "CutOff Freq" };
    juce::Label filterResonanceLabel{ "Resonance", "Resonance" };

    virtual void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<Attachment>& attachment);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
