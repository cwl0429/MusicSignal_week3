/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),sliderSet(p),oscilloscope(p), spectrum(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    
    synthChoose.addItem("Sine",1);
    synthChoose.addItem("Square", 2);
    synthChoose.addItem("Sawtooth", 3);
    synthChoose.addItem("Triangle", 4);
    
    waveComboBoxAttachment.reset(new juce::AudioProcessorValueTreeState::ComboBoxAttachment(audioProcessor.tree, "wave", synthChoose));

    for (auto& comp : subComponents)
        addAndMakeVisible(comp);

    
    addAndMakeVisible(synthChoose);
    setSize(800, 600);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto area = getLocalBounds();
    
    juce::FlexBox headLeftBlox;
    headLeftBlox.flexDirection = juce::FlexBox::Direction::column;
    headLeftBlox.items.add(juce::FlexItem(oscilloscope).withFlex(7.0f));
    headLeftBlox.items.add(juce::FlexItem(synthChoose).withFlex(1.0f));
    //oscilloscope.setBounds(oscilloscope.getBounds().reduced(10));
    
    juce::FlexBox headFlexBlox;
    headFlexBlox.flexDirection = juce::FlexBox::Direction::row;
    
    headFlexBlox.items.add(juce::FlexItem(headLeftBlox).withFlex(2.0f));
    headFlexBlox.items.add(juce::FlexItem(spectrum).withFlex(3.0f));
    

    juce::FlexBox bottomFlexBlox;
    bottomFlexBlox.flexDirection = juce::FlexBox::Direction::row;
    bottomFlexBlox.items.add(juce::FlexItem(sliderSet).withFlex(1.0f));

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::column;
    flexBox.items.add(juce::FlexItem(headFlexBlox).withFlex(7.0f));
    flexBox.items.add(juce::FlexItem(bottomFlexBlox).withFlex(2.0f));
    flexBox.performLayout(area.reduced(10));

}
