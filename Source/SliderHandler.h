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

class VerticalSliderWithLabel : public juce::Component
{
public:
    VerticalSliderWithLabel(NewProjectAudioProcessor& audioProcessor, juce::String titleName, juce::String unit);
    ~VerticalSliderWithLabel();

    void paint(juce::Graphics&)override;
    void resized() override;

private:
    NewProjectAudioProcessor& processor;
   
    
    juce::Label title;
    juce::Slider slider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;


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
    VerticalSliderWithLabel levelSlider;
    VerticalSliderWithLabel a_Slider;
    VerticalSliderWithLabel d_Slider;
    VerticalSliderWithLabel s_Slider;
    VerticalSliderWithLabel r_Slider;

    std::vector<VerticalSliderWithLabel*> sliders{ &levelSlider, &a_Slider, &d_Slider, &s_Slider, &r_Slider };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SliderHandler);
};