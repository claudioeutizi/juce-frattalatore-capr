/*
  ==============================================================================
    OscComponent.cpp
    Created: 5 May 2022 4:55:21pm
    Author:  Claudio Eutizi, Andres Bertazzi, Pierluigi Tartabini, Riccardo Martinelli
  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"
#define PORT 7000
//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts,
    juce::String waveSelectorId,
    juce::String gainId,
    juce::String pitchId,
    juce::String fmFreqId,
    juce::String fmDepthId,
    juce::String fmOSCAddPatt):
        gain("Gain", gainId, apvts, dialWidth, dialHeight),
        pitch("Pitch", pitchId, apvts, dialWidth, dialHeight),
        fmFreq("FM Freq", fmFreqId, apvts, dialWidth, dialHeight),
        fmDepth("FM Depth", fmDepthId, apvts, dialWidth, dialHeight)
{
    // specify here on which UDP port number to receive incoming OSC messages

// tell the component to listen for OSC messages matching this address:
    this->fmOSCAddressPattern = fmOSCAddPatt;
    if (fmOSCAddressPattern != "")
    {
        if (!connect(PORT))                       // [3]
            showConnectionErrorMessage("Error: could not connect to UDP port 7000.");
        addListener(this, "/juce/" + fmOSCAddressPattern);
    }
    juce::StringArray oscChoices { "Sine", "Saw", "Square" };
    oscTypeSelector.addItemList(oscChoices, 1);
    oscTypeSelector.setSelectedItemIndex(0);
    addAndMakeVisible(oscTypeSelector);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscTypeSelector);
    addAndMakeVisible(gain);
    addAndMakeVisible(pitch);
    addAndMakeVisible(fmFreq);
    addAndMakeVisible(fmDepth);
}

OscComponent::~OscComponent()
{
}

void OscComponent::oscMessageReceived(const juce::OSCMessage& message)
{
    if (message.getAddressPattern().toString() == ("/juce/" + fmOSCAddressPattern))
        if (message.size() == 3
            && message[0].isInt32()
            && message[1].isFloat32()
            && message[2].isFloat32())
        {
            this->fmFreq.getGuiSlider().setValue(convertingIterationsInFMFreqRange(message[0].getInt32()));
            this->fmDepth.getGuiSlider().setValue(computingModulusCoordinatesForFMDepth(message[1].getFloat32(), message[2].getFloat32()));
        }
}

float OscComponent::convertingIterationsInFMFreqRange(const int iterations)
{
    int oldRange = 128;
    float newRange = 100.0f;
    float newValue = (((iterations - 1) * newRange) / oldRange) + 0.0f;
    return newRange - newValue;
}

float OscComponent::computingModulusCoordinatesForFMDepth(float x, float y)
{
    return sqrt((x * x) + (y * y));
}


void OscComponent::showConnectionErrorMessage(const juce::String& messageText)
{
    juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
        "Connection error",
        messageText,
        "OK");
}


void OscComponent::resized()
{
    const auto yStart = 15;
    const auto width = 70;
    const auto height = 88;

    oscTypeSelector.setBounds(18, 40, 140, 25);
    gain.setBounds(oscTypeSelector.getX(), oscTypeSelector.getBottom()+10, width, height);
    pitch.setBounds(oscTypeSelector.getX()+70, oscTypeSelector.getBottom()+10, width, height);
    fmFreq.setBounds(oscTypeSelector.getX(), gain.getBottom(), width, height);
    fmDepth.setBounds(oscTypeSelector.getX()+70, pitch.getBottom(), width, height);
}
