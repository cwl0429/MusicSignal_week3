/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <fstream> 
#include <iostream>
#include <string>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;

    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
   
    void renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples) override;
    
    void setLevel(float newLevel);

    void setChannel(int newChannel);

    void setADSR(float attack, float decay, float sustain, float release);

    inline void logger(std::string msg);

    
private:
    float level;
    int channel;
    float frequency;
    int noteMidiNumber;
    float currentAngle;
    float angleIncrement;
    float tailOff;
    bool isPlaying = false;

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
};
