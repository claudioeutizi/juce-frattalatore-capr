/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth/SynthVoice.h"
#include "Synth/SynthSound.h"
#include ""

//==============================================================================
/**
*/
class FrattalatoreAudioProcessor  : public juce::AudioProcessor,
    public juce::OSCReceiver,
    public juce::OSCReceiver::Listener<juce::OSCReceiver::RealtimeCallback>
{
public:
    //==============================================================================
    FrattalatoreAudioProcessor();
    ~FrattalatoreAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    void oscMessageReceived(const juce::OSCMessage& message) override;
    void oscBundleReceived(const juce::OSCBundle& bundle) override;
    void showConnectionErrorMessage(const juce::String&) {}
    juce::AudioProcessorValueTreeState apvts;
    juce::MidiKeyboardState& getKeyboardState() { return keyboardState; };

private:

    static constexpr int numChannelsToProcess{ 2 };
    static constexpr int maxNumPointsOSC{ 5 };
    static constexpr int numVoices{ 5 };

    juce::Synthesiser synth;
    juce::MidiKeyboardState keyboardState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    void setParams();
    void setVoiceParams();
    void setFilterParams();
    std::array<float, numChannelsToProcess> lfoOutput{ 0.0f,0.0f };

    //OSC comunication
    juce::String OSCAddress{"127.0.0.1"};
    int OSCPort{ 7000 };
    //Default parameters that will be modified by the OSC messages
    static constexpr float defaultFMFreq{ 0.0f };
    static constexpr float defaultFMDepth{ 0.0f };
    static constexpr float defaultOscGain{ -60.0f };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrattalatoreAudioProcessor)
};
