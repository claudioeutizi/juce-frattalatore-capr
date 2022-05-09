/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Fractal.h"

//==============================================================================
JuceTestAudioProcessorEditor::JuceTestAudioProcessorEditor (JuceTestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), fractal()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    spaceBounds = juce::Rectangle<int>(0, 0, 900, 900);
    setSize (600, 500);
    
    //addAndMakeVisible(titleLabel);
    //addAndMakeVisible(fractal);


}

JuceTestAudioProcessorEditor::~JuceTestAudioProcessorEditor()
{
}

//==============================================================================
void JuceTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /* g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1); */
    g.drawText("juce plugin", getLocalBounds(), juce::Justification::centred, true);
    g.setFont(juce::Font("Times New Roman", 20.0f, juce::Font::italic));
    
   
}

void JuceTestAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    spaceImage = juce::Image(juce::Image::PixelFormat::RGB, spaceBounds.getWidth(), spaceBounds.getHeight(), true);
    generateImage();

}

void  JuceTestAudioProcessorEditor::generateImage() {
    juce::Graphics g{ spaceImage };
    fractal.drawFractal(spaceImage);
    
}
