#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Dial.h"

class TheScapeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TheScapeAudioProcessorEditor (TheScapeAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~TheScapeAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

private:
    TheScapeAudioProcessor& audioProcessor;
	juce::AudioProcessorValueTreeState& valueTreeState;

	// Plugin input and output controls

	Dial inputDial;
	Dial outputDial;

	juce::Label inputLabel;
	juce::Label outputLabel;

	std::unique_ptr<SliderAttachment> inputAttachment;
	std::unique_ptr<SliderAttachment> outputAttachment;

	// Delay controls

	Dial delayRateDial;
	Dial feedbackDial;
	Dial delayMixDial;

	juce::Label delayRateLabel;
	juce::Label feedbackLabel;
	juce::Label delayMixLabel;

	std::unique_ptr<SliderAttachment> delayRateAttachment;
	std::unique_ptr<SliderAttachment> feedbackAttachment;
	std::unique_ptr<SliderAttachment> delayMixAttachment;
	
	// Reverb controls

	Dial roomSizeDial;
	Dial widthDial;
	Dial dampingDial;
	Dial wetDial;

	juce::Label roomSizeLabel;
	juce::Label widthLabel;
	juce::Label dampingLabel;
	juce::Label wetLabel;

	std::unique_ptr<SliderAttachment> roomSizeAttachment;
	std::unique_ptr<SliderAttachment> widthAttachment;
	std::unique_ptr<SliderAttachment> dampingAttachment;
	std::unique_ptr<SliderAttachment> wetAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheScapeAudioProcessorEditor)
};
