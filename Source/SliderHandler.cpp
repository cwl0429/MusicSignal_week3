/*
  ==============================================================================

    SliderHandler.cpp
    Created: 13 Oct 2021 2:53:39pm
    Author:  ChunWei

  ==============================================================================
*/

#include "SliderHandler.h"
//#include <JuceHeader.h>

VerticalSliderWithLabel::VerticalSliderWithLabel(NewProjectAudioProcessor& audioProcessor, juce::String titleName,juce::String unit) :
    processor(audioProcessor)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow,
        true,
        slider.getTextBoxWidth() - 30,
        slider.getTextBoxHeight());
    
    //slider.setRange(upperBound,lowerBound);
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.tree, juce::String{ titleName }.toLowerCase(), slider);
    title.setText(titleName, juce::dontSendNotification);
    title.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(title);
    addAndMakeVisible(slider);
}

VerticalSliderWithLabel::~VerticalSliderWithLabel()
{

}

void VerticalSliderWithLabel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(192,192,192));
}

void VerticalSliderWithLabel::resized()
{
    auto area = getLocalBounds();
    title.setBounds(area.removeFromTop(15));
    slider.setBounds(area.reduced(4));
}


//==============================================================================


SliderHandler::SliderHandler(NewProjectAudioProcessor& p) :
    processor(p),
    levelSlider(p,"Level",""),
    a_Slider(p,"Attack",""),
    d_Slider(p,"Decay", ""),
    s_Slider(p,"Sustain", ""),
    r_Slider(p,"Release", "")
{
    for (auto& slider : sliders)
    {
        addAndMakeVisible(slider);
    }
}
SliderHandler::~SliderHandler()
{

}

void SliderHandler::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(100, 100, 100));

}

void SliderHandler::resized()
{
    juce::FlexBox flexBox;
    for (auto& slider : sliders)
    {
        juce::FlexItem item{ *slider };
        flexBox.items.add(item.withFlex(1.0));
    }
    flexBox.performLayout(getLocalBounds());

    for (auto& slider : sliders)
    {
        slider->setBounds(slider->getBounds().reduced(5));
    }
}