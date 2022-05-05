/*
  ==============================================================================

    SynthVoice.h
    Created: 30 Apr 2022 11:11:03am
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    // Ereditato tramite SynthesiserVoice
    virtual bool canPlaySound(juce::SynthesiserSound*) override;


    virtual void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;


    virtual void stopNote(float velocity, bool allowTailOff) override;


    virtual void pitchWheelMoved(int newPitchWheelValue) override;

    virtual void controllerMoved(int controllerNumber, int newControllerValue) override;

    virtual void prepareToplay(double sampleRate, int samplesPerBlock, int outputChannels);

    virtual void updateAdsr(const float attack, const float decay,
        const float sustain, const float release);

    virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    virtual void updateFilter(const int filterType, const float cutOff, const float resonance);

    virtual void updateModAdsr(const float attack, const float decay,
        const float sustain, const float release);

    OscData& getOscillator() { return this->osc; }
private:
    juce::AudioBuffer<float> synthBuffer;
    OscData osc;
    AdsrData adsr;
    FilterData filter;
    AdsrData modAdsr;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false }; //check that what we use has been previously instantiated

};