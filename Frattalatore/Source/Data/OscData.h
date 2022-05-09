/*
  ==============================================================================

    OscData.h
    Created: 3 May 2022 12:17:35pm
    Author:  claud

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{

public:
    virtual void OscData::setOscWaveType(const int choice);
    virtual void OscData::setGain(const float levelDb);
    virtual void OscData::setNoiseGain(const float noiseLevelDb);
    virtual void OscData::setOnOff(const bool onOff);
    virtual void OscData::updateFm(const float depth, const float freq);
    virtual void OscData::setWaveFrequency(const int midiNoteNumber);
    virtual void OscData::setPitch(const int pitch);
    virtual void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    virtual void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    virtual float processNextSample(float input);
    virtual void OscData::resetOsc();
    virtual void setParams(const int oscChoice, const float oscGain, const float noiseGain, const int oscPitch, const float fmFreq, const float fmDepth);

private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) {return sin(x); } }; 
    juce::dsp::Gain<float> gain;
    juce::Random noise;
    juce::dsp::Gain<float> noiseGain;
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    bool lastOnOff{ false };
    int lastPitch{ 0 };
    int lastMidiNote{ 0 };
};
