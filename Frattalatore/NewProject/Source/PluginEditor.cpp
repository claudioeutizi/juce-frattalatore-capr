/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor(NewProjectAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), fractal()
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    rectangle = juce::Rectangle<int>(0, 0, fractal.getW(), fractal.getH());
    setSize(900, 900);
    fractalImage = juce::Image(juce::Image::PixelFormat::RGB, rectangle.getWidth(), rectangle.getHeight(), true);
    generateImage(fractalImage);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    /* g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1); */
    g.drawImage(fractalImage, 0, 0, rectangle.getWidth(), rectangle.getHeight(), 0, 0, fractal.getW(), fractal.getH(), false);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void NewProjectAudioProcessorEditor::generateImage(juce::Image& image) {
   fractal.drawFractal(image);
}