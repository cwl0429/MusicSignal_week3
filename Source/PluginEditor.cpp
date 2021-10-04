/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    levelSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    levelSlider.setValue(0.5);
    levelSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
        true,
        levelSlider.getTextBoxWidth(),
        levelSlider.getTextBoxHeight());
    levelSliderAttachment.reset(new juce::AudioProcessorValueTreeState::SliderAttachment(audioProcessor.tree, "level", levelSlider));

    
   
    synthChoose.addItem("Sine",1);
    synthChoose.addItem("Square", 2);
    synthChoose.addItem("Sawtooth", 3);
    synthChoose.addItem("Triangle", 4);
    waveComboBoxAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wave", synthChoose));


    addAndMakeVisible(levelSlider);
    addAndMakeVisible(synthChoose);
    setSize(400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.setColour(juce::Colours::white);
    int x = 50;
    int y = 100;
    int width = 50;
    int height = levelSlider.getHeight();

    g.drawFittedText("Level", x, y, width, height, juce::Justification::centred, 1);
    g.drawFittedText("Synthesizer", x, 150, width, height, juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    int sliderWidth = area.getWidth() / 2;
    int sliderHeight = area.getHeight() / 4;
    int x = 100;
    int y = 100;

    levelSlider.setBounds(x, y, sliderWidth, sliderHeight);
    synthChoose.setBounds(x, y + 50, sliderWidth, sliderHeight);
}
