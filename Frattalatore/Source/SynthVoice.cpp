/*
  ==============================================================================

    SynthVoice.cpp
    Created: 30 Apr 2022 11:11:39am
    Author:  claud

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    //SynthSound is correctly casting to SynthesiserSound?
    return dynamic_cast<juce::SynthesiserSound*> (sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
    modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    modAdsr.noteOff();
    if (!allowTailOff || !adsr.isActive()) 
        clearCurrentNote();
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToplay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    //OSC
    osc.prepareToPlay(spec);
    //ADSR
    adsr.setSampleRate(sampleRate);
    //FILTER
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    //MOD FILTER
    modAdsr.setSampleRate(sampleRate);
    //GAIN
    gain.prepare(spec);


    gain.setGainLinear(0.3f);

    isPrepared = true;
}
void SynthVoice::updateAdsr(const float attack, const float decay,
    const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared); //if prepareToPlay has not been called

    // return without doing anything
    if (!isVoiceActive()) return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); //iot avoid the initial clipping
    modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples); //despite it does not work on the output envelope, I need this function to activate it
    synthBuffer.clear();

    //Audio block
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    //Oscillator
    osc.getNextAudioBlock(audioBlock);

    //adsr applied
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    //filtering
    filter.process(synthBuffer);

    //gain
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    //the AudioBlock is an alias of the outputBuffer -> what i do with AudioBlock i do the same in the output buffer    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) clearCurrentNote();
    }
}

void SynthVoice::updateFilter(const int filterType, const float cutOff, const float resonance)
{
    float modulator = modAdsr.getNextSample();
    filter.updateParameters(filterType, cutOff, resonance, modulator);
}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
    modAdsr.updateADSR(attack, decay, sustain, release);
}

