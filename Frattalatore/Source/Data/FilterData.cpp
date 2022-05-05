/*
  ==============================================================================

    FliterData.cpp
    Created: 4 May 2022 4:43:30pm
    Author:  claud

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplePerBlock, int numChannels)
{
    filter.reset();
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplePerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    filter.prepare(spec);
    isPrepared = true;

}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block{ buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float> {block});
}

void FilterData::updateParameters(const int filterType, const float frequency, const float resonance, /* optional */const float modulator)
{
    switch (filterType)
    {
    case 0:
        filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
        break;
    case 1:
        filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
        break;
    case 2:
        filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
        break;
    }
    float modFreq = frequency * modulator;
    //setting the bounds, with the modulation it may happen that the freq goes beyond them
    modFreq = std::fmin(std::fmax(modFreq, 20.0f), 20000.0f);
    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}
