/*
  ==============================================================================

    SynthVoice.cpp
    Created: 24 Jul 2021 12:43:29pm
    Author:  tuiji da

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<SynthSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    noteMidiNumber = midiNoteNumber;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    currentAngle = 0.f;
    angleIncrement = frequency / getSampleRate() * juce::MathConstants<float>::twoPi;
    tailOff = 0.0;
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    if (allowTailOff)
    {
        if (tailOff == 0.0)
            tailOff = 1.0;
    }
    else
    {
        clearCurrentNote();
        level = 0;
        currentAngle = 0.f;
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    // handle pitch wheel moved midi event
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    // handle midi control change
}

void SynthVoice::renderNextBlock (juce::AudioBuffer <float> &outputBuffer, int startSample, int numSamples)
{
    float value;
    float proportion;
    
 
    if (tailOff > 0.0)
    {
        
        for (int i = startSample; i < (startSample + numSamples); i++)//release key
        {
            switch (channel)
            {
            case 1: //sin wave
                value = std::sin(currentAngle);
                break;
            case 2: //square wave 
                value = ((std::sin(currentAngle) > 0) ? 1 : -1) ;
                break;
            case 3: //sawtooth wave 
                proportion = fmod(currentAngle + juce::MathConstants<float>::pi, juce::MathConstants<float>::twoPi) / juce::MathConstants<float>::twoPi;
                value = (proportion * 2 - 1);
                break;
            case 4: //triangle wave
                proportion = fmod(currentAngle + juce::MathConstants<float>::halfPi, juce::MathConstants<float>::twoPi) / juce::MathConstants<float>::twoPi;
                if (proportion < 0.5)
                    value = ((proportion * 2) * 2 - 1);
                else
                    value = 2 - ((proportion - 0.5) * 2) * 2 - 1;         
                break;
            default:
                value = std::sin(currentAngle);
                break;
            }
            value = value *level*tailOff;           
            outputBuffer.addSample(0, i, value);
            outputBuffer.addSample(1, i, value);
            
            //if (value != 0)logger(std::to_string(value));
            currentAngle += angleIncrement;
            tailOff *= 0.99;
            
            if (tailOff <= 0.05)
            {
                clearCurrentNote();
                angleIncrement = 0.0;
                level = 0.0;
                break;
            }
        }

    }
    else
    {
        for (int i = startSample; i < (startSample + numSamples); i++)//not release key
        {
            switch (channel)
            {
            case 0: //sin wave
                value = std::sin(currentAngle);
                break;
            case 1: //square wave 
                value = ((std::sin(currentAngle) > 0) ? 1 : -1);
                break;
            case 2: //sawtooth wave 
                proportion = fmod(currentAngle + juce::MathConstants<float>::pi, juce::MathConstants<float>::twoPi) / juce::MathConstants<float>::twoPi;
                value = (proportion * 2 - 1);
                break;
            case 3: //triangle wave
                proportion = fmod(currentAngle + juce::MathConstants<float>::halfPi, juce::MathConstants<float>::twoPi) / juce::MathConstants<float>::twoPi;
                if (proportion < 0.5)
                    value = ((proportion * 2) * 2 - 1);
                else
                    value = 2 - ((proportion - 0.5) * 2) * 2 - 1;
                
                break;
            default:
                value = std::sin(currentAngle);
                break;
            }
            value *= level;
            //if (value != 0)logger(std::to_string(value));
            outputBuffer.addSample(0, i, value);
            outputBuffer.addSample(1, i, value);
            
            currentAngle += angleIncrement;
        }
    }
}



void SynthVoice::setLevel(float newLevel)
{
    level = newLevel;
}

void SynthVoice::setChannel(int newChannel)
{
    channel = newChannel;
}

inline void SynthVoice::logger(std::string msg) {
    std::string filePath = "C:/Users/ChunWei/source/log.txt";
    std::ofstream ofs(filePath.c_str(), std::ios_base::out | std::ios_base::app);
    ofs << msg << '\n';
    ofs.close();
}