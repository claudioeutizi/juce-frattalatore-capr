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

    std::array<OscData,2>& getOscillator() { return osc; }
    AdsrData& getAdsr() { return adsr; }
private:
    static constexpr int numChannelsToProcess{ 2 };
    juce::AudioBuffer<float> synthBuffer;
    std::array<OscData, numChannelsToProcess> osc;
    AdsrData adsr;
    std::array<FilterData, numChannelsToProcess> filter;
    AdsrData modAdsr;
    std::array<float, numChannelsToProcess> lfoOutput{ 0.0f,0.0f };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false }; //check that what we use has been previously instantiated

};