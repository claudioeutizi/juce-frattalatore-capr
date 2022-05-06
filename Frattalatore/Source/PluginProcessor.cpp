/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

//==============================================================================
FrattalatoreAudioProcessor::FrattalatoreAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    //polyphonic synthesiser
    synth.addSound(new SynthSound());
    for (int v = 0; v < numVoices; v++) 
    {
        synth.addVoice(new SynthVoice());
    }
}

FrattalatoreAudioProcessor::/*destructor*/~FrattalatoreAudioProcessor()
{
}

//==============================================================================
const juce::String FrattalatoreAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FrattalatoreAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FrattalatoreAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FrattalatoreAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FrattalatoreAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FrattalatoreAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FrattalatoreAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FrattalatoreAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FrattalatoreAudioProcessor::getProgramName (int index)
{
    return {};
}

void FrattalatoreAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FrattalatoreAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        //the next line returns a SynthesiserVoice object that does not have
        // our prepareToPlay definition => cast
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToplay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
}

void FrattalatoreAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FrattalatoreAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FrattalatoreAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    setParams();

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    //for (int ch = 0; ch < numChannelsToProcess; ++ch)
    //{
    //    auto* output = buffer.getWritePointer(ch);
    //    for (int s = 0; s < buffer.getNumSamples(); ++s)
    //    {
    //        lfoOutput[ch] = lfo[ch].processSample(buffer.getSample(ch, s));
    //        output[s] = filter[ch].processNextSample(ch, buffer.getSample(ch, s));
    //    }
    //}
}

//==============================================================================
bool FrattalatoreAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FrattalatoreAudioProcessor::createEditor()
{
    return new FrattalatoreAudioProcessorEditor (*this);
}

//==============================================================================
void FrattalatoreAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FrattalatoreAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FrattalatoreAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FrattalatoreAudioProcessor::createParams()
{

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //OSC select and options
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray
        { "Sine", "Saw", "Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> 
    { -40.0f, 0.2f, 0.1f }, 0.1f, "dB"));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -48, 48, 0));

    //FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "OSC 1 FM Frequency", juce::NormalisableRange<float>
    {0.0f, 1000.0f, 0.01f, 0.3f}, 5.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "OSC 1 FM Depth", juce::NormalisableRange<float>
    {0.0f, 1000.0f, 0.01f, 0.3f}, 500.0f)); //more control on the lower range, like logarithmically

    //Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", 
        juce::StringArray{ "LPF", "BPF", "HPF" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter CutOff", juce::NormalisableRange<float>
    {20.0f, 20000.0f, 0.1f, 0.6f}, 200.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float>
    {1.0f, 10.0f, 0.1f}, 1.0f));

    //LFO
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO1FREQ", "LFO1 Frequency", juce::NormalisableRange<float> 
    { 0.0f, 20.0f, 0.1f }, 5.0f, "Hz"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO1DEPTH", "LFO1 Depth", juce::NormalisableRange<float> 
    { 0.0f, 500.0f, 0.1f}, 1000.0f, ""));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>
    {0.1f, 1.0f, 0.1f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>
    {0.1f, 3.0f, 0.1f, }, 0.4f));
    return { params.begin(), params.end() };
}

void FrattalatoreAudioProcessor::setParams()
{
    setVoiceParams();
    setFilterParams();
}

void FrattalatoreAudioProcessor::setVoiceParams()
{
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        //check the correct casting for each voice
        if (auto voice = dynamic_cast<SynthVoice*> (synth.getVoice(i)))
        {

            // OSC 
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& oscGain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& oscPitch = *apvts.getRawParameterValue("OSC1PITCH");

            //FM
            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");

            //ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& osc = voice->getOscillator();
            //auto& adsr = voice->getAdsr();
            for (int j = 0; j < getTotalNumOutputChannels(); i++)
            {
                osc[j].setParams(oscWaveChoice, oscGain, oscPitch, fmFreq, fmDepth);
            }
            auto& adsr = voice->getAdsr();
            adsr.updateADSR(attack.load(), decay.load(), sustain.load(), release.load()); //the pointer is for a AtomicFloat -> convert it into float iot save 
        }
    }
}

void FrattalatoreAudioProcessor::setFilterParams()
{
    auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
    auto& filterCutOff = *apvts.getRawParameterValue("FILTERCUTOFF");
    auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");

    auto& lfoFreq = *apvts.getRawParameterValue("LFO1FREQ");
    auto& lfoDepth = *apvts.getRawParameterValue("LFO1DEPTH");
    
    for (int ch = 0; ch < numChannelsToProcess; ++ch)
    {
        for (int i = 0; i < synth.getNumVoices(); ++i) 
        {
            if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
            {
                lfo[ch].setFrequency(lfoFreq);
                //filterCutOff = (lfoDepth * lfoOutput[ch]) + filterCutOff;
                auto cutOff = std::clamp<float>(filterCutOff, 20.0f, 20000.0f);
                voice->updateFilterParams(filterType, filterCutOff, filterResonance, lfoFreq, lfoDepth);
            }
        }
    }
}
