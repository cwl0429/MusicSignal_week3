/*
  ==============================================================================

    Oscilloscope.h
    Created: 14 Oct 2021 1:39:11pm
    Author:  ChunWei

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FIFO.h"


class Oscilloscope : public juce::Component, public juce::Timer {
public:
    Oscilloscope(NewProjectAudioProcessor&);
    ~Oscilloscope() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    NewProjectAudioProcessor& processor;
    SingleChannelSampleFifo<juce::AudioBuffer<float>>& waveform;
    juce::AudioBuffer<float> pathBuffer;
    PathProducer<juce::Path> pathProducer;
    juce::Path waveformPath;

    void generateWaveform();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscilloscope);
};