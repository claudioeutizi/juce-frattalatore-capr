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
    virtual void setOscWaveType(const int choice);
    virtual void setWaveFrequency(const int midiNoteNumber);
    virtual void prepareToPlay(juce::dsp::ProcessSpec& spec);
    virtual void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock);
    virtual void updateFm(const float depth, const float freq);
private:
    juce::dsp::Oscillator<float> fmOsc{ [](float x) {return sin(x); } }; //frequency modulator
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMidiNote{ 0 };
};
