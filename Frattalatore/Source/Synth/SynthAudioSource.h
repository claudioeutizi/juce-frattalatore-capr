/*
  ==============================================================================

    SynthAudioSource.h
    Created: 11 May 2022 4:01:09pm
    Author:  andre

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthVoice.h"

class SynthAudioSource : public juce::AudioSource
{
public:
    SynthAudioSource(juce::MidiKeyboardState& keyState);
    void setUsingSineWaveSound();
    void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override;
    void releaseResources() override; 
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    
private:
    juce::MidiKeyboardState& keyboardState;
    juce::Synthesiser synth;
};