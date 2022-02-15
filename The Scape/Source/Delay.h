#pragma once

#include <JuceHeader.h>
#include "define.h"

class Delay
{
public:
	Delay();
	~Delay();

	void prepare(juce::dsp::ProcessSpec spec);
	void setParameters(int newDelayRate, float newFeedback, float newMix);
	void process(juce::AudioBuffer<float>& buffer);

private:

	void fillDelayBuffer(int channel, int bufferLength, int delayBufferLength, const float* ChannelData);
	void getFromDelayBuffer(int channel, juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& delayBuffer);
	void feedbackDelay(int channel, int bufferLength, int delayBufferLength, float* ChannelData);

	int sampleRate{ 44100 };
	int samplesPerBlock;
	int numChannels;
	int writePosition{ 0 };
	int delayRate{ 0 };

	float feedbackGain{ 0.8f };
	float mixValue{ 0 };

	juce::AudioBuffer<float> processedBuffer;
	juce::AudioBuffer<float> delayBuffer;


};


