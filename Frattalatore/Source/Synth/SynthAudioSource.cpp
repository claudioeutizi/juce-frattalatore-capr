/*
  ==============================================================================

    SynthAudioSource.cpp
    Created: 11 May 2022 4:01:09pm
    Author:  andre

  ==============================================================================
*/

#include "SynthAudioSource.h"

SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState& keyState) : keyboardState(keyState)
{
    for (auto i = 0; i < 4; ++i)                // [1]
        synth.addVoice(new SynthVoice());

    synth.addSound(new SynthSound());       // [2]
}

void SynthAudioSource::setUsingSineWaveSound()
{
    synth.clearSounds();
}

void SynthAudioSource::prepareToPlay(int, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate); // [3]
}

void SynthAudioSource::releaseResources()
{
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer incomingMidi;
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample,
        bufferToFill.numSamples, true);       // [4]

    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
        bufferToFill.startSample, bufferToFill.numSamples); // [5]
}
