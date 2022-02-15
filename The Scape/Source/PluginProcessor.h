#pragma once

#include <JuceHeader.h>
#include "define.h"
#include "Delay.h"
//==============================================================================
class TheScapeAudioProcessor  : public juce::AudioProcessor
{
public:
    TheScapeAudioProcessor();
    ~TheScapeAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	Delay delay;

private:

	std::atomic<float>* inputGainParameter = nullptr;
	std::atomic<float>* outputGainParameter = nullptr;
	std::atomic<float>* delayRateParameter = nullptr;
	std::atomic<float>* feedbackParameter = nullptr;
	std::atomic<float>* delayMixParameter = nullptr;
	std::atomic<float>* roomSizeParameter = nullptr;
	std::atomic<float>* widthParameter = nullptr;
	std::atomic<float>* dampingParameter = nullptr;
	std::atomic<float>* wetParameter = nullptr;

	juce::AudioProcessorValueTreeState apvts;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheScapeAudioProcessor)
};
