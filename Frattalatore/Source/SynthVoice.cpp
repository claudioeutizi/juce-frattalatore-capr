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
    for (int i = 0; i < 2; i++)
    {
        osc[i].setWaveFrequency(midiNoteNumber);
    }
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
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
    reset();

    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        //OSC
        osc[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        //FILTER
        filter[ch].prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
        //LFO
        lfo[ch].prepare(spec);
        lfo[ch].initialise([](float x) {return std::sin(x); });
    }
        //GAIN
        gain.prepare(spec);
        gain.setGainLinear(0.07f);

        isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared); //if prepareToPlay has not been called

    // return without doing anything
    if (!isVoiceActive()) return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); //iot avoid the initial clipping

    synthBuffer.clear();

    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = osc[ch].processNextSample(buffer[s])/* + osc[ch].processNextSample(buffer[s])*/;
        }
    }

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int ch = 0; ch < synthBuffer.getNumChannels(); ++ch)
    {
        auto* buffer = synthBuffer.getWritePointer(ch, 0);

        for (int s = 0; s < synthBuffer.getNumSamples(); ++s)
        {
            buffer[s] = filter[ch].processNextSample(ch, synthBuffer.getSample(ch, s));
        }
    }
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) clearCurrentNote();
    }
}

void SynthVoice::reset()
{
    gain.reset();
    adsr.reset();
}

void SynthVoice::updateFilterParams(const int filterType, const float filterCutOff, const float resonance, const float lfoFreq, const float lfoDepth)
{
    auto cutOff = filterCutOff;
    for (int ch = 0; ch < numChannelsToProcess; ch++)
    {
        lfo[ch].setFrequency (lfoFreq);
        cutOff = (lfoDepth * lfoOutput[ch]) + cutOff;
        cutOff = std::clamp<float> (cutOff, 20.0f, 20000.0f);
        filter[ch].updateParameters(filterType, cutOff, resonance);
    }
}

