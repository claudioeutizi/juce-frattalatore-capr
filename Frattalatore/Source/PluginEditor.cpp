/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrattalatoreAudioProcessorEditor::FrattalatoreAudioProcessorEditor (FrattalatoreAudioProcessor& p):
    AudioProcessorEditor (&p),
    audioProcessor (p),
    osc(audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH"),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE"),
    adsr(audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    lfo(audioProcessor.apvts, "LFO1FREQ", "LFO1DEPTH")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (620, 500);

    //Oscillator parameters
    addAndMakeVisible(osc);

    //Filter
    addAndMakeVisible(filter);

    //LFO
    addAndMakeVisible(lfo);

    //adsr sliders
    addAndMakeVisible(adsr);


    osc.setName("Oscillator");
    filter.setName("Filter");
    lfo.setName("Filter LFO");
    adsr.setName("ADSR");

    auto oscColour = juce::Colour::fromRGB(247, 190, 67);
    auto filterColour = juce::Colour::fromRGB(246, 87, 64);

    osc.setBoundsColour(oscColour);

    filter.setBoundsColour(filterColour);
    lfo.setBoundsColour(filterColour);

    setSize(1080, 525);
}

FrattalatoreAudioProcessorEditor::~FrattalatoreAudioProcessorEditor()
{
}

//==============================================================================
void FrattalatoreAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour
    g.fillAll(juce::Colours::black);
}

void FrattalatoreAudioProcessorEditor::resized()
{
    //positioning all the graphical components in the right place

    const auto oscWidth = 420;
    const auto oscHeight = 180;
    osc.setBounds(0, 0, oscWidth, oscHeight);
    filter.setBounds(osc.getRight(), 0, 180, 200);
    lfo.setBounds(filter.getRight(), filter.getBottom(), 180, 160);
    adsr.setBounds(filter.getRight(), 0, 230, 360);
}

