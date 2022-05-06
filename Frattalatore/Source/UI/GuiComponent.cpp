/*
  ==============================================================================

    GuiComponent.cpp
    Created: 6 May 2022 1:25:41pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GuiComponent.h"


//===============IMPLEMENTATION OF SliderWithLabel===================================

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

SliderWithLabel::SliderWithLabel(juce::String labelName, juce::String paramId, juce::AudioProcessorValueTreeState& apvts, 
    const int width, const int height, juce::Slider::SliderStyle style)
{
    sliderWidth = width;
    sliderHeight = height;

    guiSlider.setSliderStyle(style);
    guiSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, textBoxWidth, textBoxHeight);
    addAndMakeVisible(guiSlider);

    guiLabel.setFont(fontHeight);
    guiLabel.setText(labelName, juce::dontSendNotification);
    guiLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(guiLabel);

    guiSliderAttachment = std::make_unique<SliderAttachment>(apvts, paramId, guiSlider);
}

void SliderWithLabel::resized()
{
    const auto dialToLabelRatio = 15;
    const auto labelHeight = 18;

    jassert(sliderWidth > 0);
    jassert(sliderHeight > 0);

    guiLabel.setBounds(0, 0, sliderWidth, labelHeight);
    guiSlider.setBounds(0, 0 + dialToLabelRatio, sliderWidth, sliderHeight);
}

//===============IMPLEMENTATION OF GuiComponent===================================
GuiComponent::GuiComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

GuiComponent::~GuiComponent()
{
}

void GuiComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    auto bounds = getLocalBounds();
    g.setColour(boundsColour);
    g.drawRoundedRectangle(bounds.toFloat().reduced(10.0f), 5.0f, 2.0f);

    g.setColour(juce::Colours::yellow);
    g.setFont(fontHeight);
    g.setFont(g.getCurrentFont().boldened());

    jassert(guiComponentName.isNotEmpty());
    g.drawText(guiComponentName, 20, 15, 100, 25, juce::Justification::left);
}

void GuiComponent::resized()
{
}
//===============IMPLEMENTATION OF SynthComboBox===================================

SynthComboBox::SynthComboBox(juce::String labelName, 
    juce::String paramId, juce::AudioProcessorValueTreeState& apvts, 
    juce::StringArray choices, const int defaultChoice)
{
    guiComboBox.addItemList(choices, 1);
    guiComboBox.setSelectedItemIndex(defaultChoice);
    addAndMakeVisible(guiComboBox);
    guiComboBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, paramId, guiComboBox);
}

void SynthComboBox::resized()
{
}
