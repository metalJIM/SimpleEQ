/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SimpleEQAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SimpleEQAudioProcessor();
    ~SimpleEQAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    //Expects us to provide a list of all parameters when it's created. THe last argument is a function
    //that provides that
    
    //Static as it doens't provide any member variables
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    //Connects GUI elements to processing Variables etc
    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

private:
    //====Set up alias for nested namespaces====
    
    //Peak Filter
    using Filter = juce::dsp::IIR::Filter<float>;
    //Cutoff Filter - Processes audio in a chain, and we want up to 4 12 dB/Oct filters on our Cutoff Filters
    using CutFilter = juce::dsp::ProcessorChain<Filter, Filter, Filter, Filter>;
    //Represents the Audio Chain of the whole filter plugin - Low Cut , Peak, then High Cut
    using MonoChain = juce::dsp::ProcessorChain<CutFilter, Filter, CutFilter>;
    //Declare two mono chains for stereo processing
    MonoChain leftChain, rightChain;
    

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleEQAudioProcessor)
};
