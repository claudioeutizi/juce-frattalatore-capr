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
#include "../Data/OscData.h"
#include "../Data/AdsrData.h"
#include "../Data/FilterData.h"

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
    virtual void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;


    virtual void reset();

    void updateFilterParams(const int filterType, const float filterCutOff, const float resonance, const float lfoFreq, const float lfoDepth);
    std::array<std::array<OscData, 2>,5>& getOscillators() { return this->oscillators; };
    std::array<OscData, 2>& getOscillator(const int idxOscillator) { return oscillators[idxOscillator]; };
    AdsrData& getAdsr() { return this->adsr; };
    //void updateFilterParams(const int filterType, const float filterCutOff, const float filterResonance, const float lfoFreq, const float lfoDepth);
private:
    static constexpr int numChannelsToProcess{ 2 };
    std::array<std::array<OscData, numChannelsToProcess>,5> oscillators;
    std::array<float, 5> xCoordinates;
    std::array<float, 5> yCoordinates;
    std::array<juce::dsp::Oscillator<float>, numChannelsToProcess> lfo;
    std::array<FilterData, numChannelsToProcess> filter;
    juce::AudioBuffer<float> synthBuffer;
    AdsrData adsr;
    std::array<float, numChannelsToProcess> lfoOutput{ 0.0f,0.0f };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false }; //check that what we use has been previously instantiated
};