/*
  ==============================================================================

    SliderHandler.h
    Created: 13 Oct 2021 2:53:39pm
    Author:  ChunWei

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include "PluginProcessor.h"
#include "AweLookAndFeel.h"

class RotarySliderWithLabel : public juce::Component
{
public:
    RotarySliderWithLabel(NewProjectAudioProcessor& audioProcessor, juce::String titleName, juce::String unit);
    ~RotarySliderWithLabel();

    void paint(juce::Graphics&)override;
    void resized() override;

private:
    NewProjectAudioProcessor& processor;
   
    
    juce::Label title;
    juce::Slider slider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    AweLookAndFeel lnf;

};
class SliderHandler : public juce::Component
{
public:
    SliderHandler(NewProjectAudioProcessor& );
    ~SliderHandler() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    NewProjectAudioProcessor& processor;
    RotarySliderWithLabel levelSlider;
    RotarySliderWithLabel a_Slider;
    RotarySliderWithLabel d_Slider;
    RotarySliderWithLabel s_Slider;
    RotarySliderWithLabel r_Slider;

    std::vector<RotarySliderWithLabel*> sliders{ &levelSlider, &a_Slider, &d_Slider, &s_Slider, &r_Slider };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderHandler);
};