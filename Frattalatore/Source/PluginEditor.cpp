/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FrattalatoreAudioProcessorEditor::FrattalatoreAudioProcessorEditor (FrattalatoreAudioProcessor& p)
    : AudioProcessorEditor (&p),
    audioProcessor (p),
    osc(audioProcessor.apvts,"OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH"),
    adsr("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRES"),
    modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (620, 500);

    //adsr sliders
    addAndMakeVisible(adsr);

    //Oscillator parameters
    addAndMakeVisible(osc);

    //Filter
    addAndMakeVisible(filter);

    //Mod filter
    addAndMakeVisible(modAdsr);

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

    //dimension variables
    const auto paddingX = 5;
    const auto paddingY = 35;
    const auto paddingYFilter = 270;
    const auto width = 300;
    const auto height = 200;

    //placing the components

    osc.setBounds(paddingX, paddingY, width, height);
    adsr.setBounds(osc.getRight(),paddingY, width, height);
    filter.setBounds(paddingX, paddingYFilter, width, height);
    modAdsr.setBounds(filter.getRight(), paddingYFilter, width, height);
}

