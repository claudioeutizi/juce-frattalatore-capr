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
    audioProcessor (p), keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
    osc1(audioProcessor.apvts, "OSC1TYPE", "OSC1GAIN", "OSC1PITCH", "OSC1FMFREQ", "OSC1FMDEPTH"),
    osc2(audioProcessor.apvts, "OSC2TYPE", "OSC2GAIN", "OSC2PITCH", "OSC2FMFREQ", "OSC2FMDEPTH"),
    osc3(audioProcessor.apvts, "OSC3TYPE", "OSC3GAIN", "OSC3PITCH", "OSC3FMFREQ", "OSC3FMDEPTH"),
    osc4(audioProcessor.apvts, "OSC4TYPE", "OSC4GAIN", "OSC4PITCH", "OSC4FMFREQ", "OSC4FMDEPTH"),
    osc5(audioProcessor.apvts, "OSC5TYPE", "OSC5GAIN", "OSC5PITCH", "OSC5FMFREQ", "OSC5FMDEPTH"),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE"),
    adsr(audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    lfo(audioProcessor.apvts, "LFOFREQ", "LFODEPTH")

{
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::LOGO_Capr_png, BinaryData::LOGO_Capr_pngSize); 
    backgroundImage = backgroundImage.rescaled(150, 150); 
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    addAndMakeVisible(keyboardComponent);

    LookAndFeel::setDefaultLookAndFeel(&customLookAndFeel);
    //Oscillator parameters
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc3);
    addAndMakeVisible(osc4);
    addAndMakeVisible(osc5);

    //Filter
    addAndMakeVisible(filter);

    //LFO
    addAndMakeVisible(lfo);

    //adsr sliders
    addAndMakeVisible(adsr);

    osc1.setComponentName("Oscillator1");
    osc2.setComponentName("Oscillator2");
    osc3.setComponentName("Oscillator3");
    osc4.setComponentName("Oscillator4");
    osc5.setComponentName("Oscillator5");
    filter.setComponentName("Filter");
    lfo.setComponentName("Filter LFO");
    adsr.setComponentName("ADSR");

    auto oscColour = juce::Colour::fromRGB(247, 190, 67);
    auto filterColour = juce::Colour::fromRGB(246, 87, 64);

    osc1.setBoundsColour(oscColour);
    osc2.setBoundsColour(oscColour);
    osc3.setBoundsColour(oscColour);
    osc4.setBoundsColour(oscColour);
    osc5.setBoundsColour(oscColour);
    filter.setBoundsColour(filterColour);
    lfo.setBoundsColour(filterColour);

    setSize(900, 600);
}

FrattalatoreAudioProcessorEditor::~FrattalatoreAudioProcessorEditor()
{
}

//==============================================================================
void FrattalatoreAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour
   // g.fillAll(juce::Colours::black);
    g.drawImageAt(backgroundImage,getWidth()/2.0-75, getHeight()/2.0);
}

void FrattalatoreAudioProcessorEditor::resized()
{
    //positioning all the graphical components in the right place

    const auto oscWidth = 180;
    const auto oscHeight = 280;
    osc1.setBounds(0, 0, oscWidth, oscHeight);
    osc2.setBounds(osc1.getRight(), 0, oscWidth, oscHeight);
    osc3.setBounds(osc2.getRight(), 0, oscWidth, oscHeight);
    osc4.setBounds(osc3.getRight(), 0, oscWidth, oscHeight);
    osc5.setBounds(osc4.getRight(), 0, oscWidth, oscHeight);

    filter.setBounds(0, osc5.getBottom(), getWidth()/4.0, 200);
    lfo.setBounds(filter.getRight(), osc5.getBottom(), getWidth()/4.0, 200);
    adsr.setBounds(lfo.getRight(), osc4.getBottom(), getWidth()/2.0, 200);

    keyboardComponent.setBounds(0,filter.getBottom(), getWidth(), 120);
}

