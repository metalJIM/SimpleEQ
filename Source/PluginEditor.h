/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//Custom class so we don't need to call the Slider definition every single time. Just use this constructor
struct CustomRotarySlider : juce::Slider
{
    CustomRotarySlider() : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox)
    {

    }
};

//==============================================================================
/**
*/
class SimpleEQAudioProcessorEditor  : public juce::AudioProcessorEditor,
//Create a listener to listen to all of the Parameter changes in Processor
juce::AudioProcessorParameter::Listener, 
juce::Timer
{
public:
    SimpleEQAudioProcessorEditor (SimpleEQAudioProcessor&);
    ~SimpleEQAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void parameterValueChanged(int parameterIndex, float newValue) override;

    void parameterGestureChanged(int parametIndex, bool gestureIsStarting) override {};
    //For the Atomic timer
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SimpleEQAudioProcessor& audioProcessor;

    juce::Atomic<bool> parametersChanged { false };

    //an object of CustomRotarySlider for each of the sliders
    CustomRotarySlider peakFreqSlider, peakGainSlider,
                       peakQualitySlider, lowCutFreqSlider,
                       highCutFreqSlider, lowCutSlopeSlider,
                       highCutSlopeSlider;

    //Alias for the APVTS connector class
    using APVTS = juce::AudioProcessorValueTreeState;
    using Attachment = APVTS::SliderAttachment;

    //an object of Attachment for each of the slider which need to be initialised in the Constructor
    Attachment peakFreqSliderAttachment, peakGainSliderAttachment,
               peakQualitySliderAttachment, lowCutFreqSliderAttachment, 
               highCutFreqSliderAttachment, lowCutSlopeSliderAttachment, 
               highCutSlopeSliderAttachment;


    //function on a vector that will iterate through all the components above so things can be done to them 
    std::vector<juce::Component*> getComps();

    MonoChain monoChain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessorEditor)
};
