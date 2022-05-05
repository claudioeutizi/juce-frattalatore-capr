/*
  ==============================================================================

    FliterData.h
    Created: 4 May 2022 4:43:30pm
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    void FilterData::prepareToPlay (double sampleRate, int samplePerBlock, int numChannels);
    void FilterData::process(juce::AudioBuffer<float>& buffer);
    void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, const float modulator = 1.0f);
    void FilterData::reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};