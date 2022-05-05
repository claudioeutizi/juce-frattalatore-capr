/*
  ==============================================================================

    OscData.cpp
    Created: 3 May 2022 12:17:35pm
    Author:  claud

  ==============================================================================
*/

#include "OscData.h"

void OscData::setOscWaveType(const int choice)
{
    switch (choice)
    {
    case 0: //sine wave
        initialise([](float x) { return std::sin(x); });
        break;
    case 1: //saw wave
        initialise([](float x) { return x / (juce::MathConstants<float>::pi); });
        break;
    case 2: //square wave
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;
    default: //error
        jassertfalse;
        break;
    }
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock)
{
    //sample-by-sample processing iot apply the FM processing
    for (int ch = 0; ch < audioBlock.getNumChannels(); ++ch) 
    {
        for (int s = 0; s < audioBlock.getNumSamples(); ++s) 
        {
            //obtaining the value of the wave of one instant
            fmMod = fmOsc.processSample(audioBlock.getSample(ch, s)) * fmDepth;
        } 
    }

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::updateFm(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    auto currentFreq = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod;
    setFrequency(currentFreq >= 0 ? currentFreq : currentFreq * -1.0f);
    
}
