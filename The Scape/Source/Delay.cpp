#include "Delay.h"

Delay::Delay()
{
	
}

Delay::~Delay()
{
	processedBuffer.clear();
	delayBuffer.clear();
}

void Delay::prepare(juce::dsp::ProcessSpec spec) {
	sampleRate = spec.sampleRate;
	samplesPerBlock = spec.maximumBlockSize;
	numChannels = spec.numChannels;

	const int delayBufferSize = 2 * sampleRate;
	delayBuffer.setSize(numChannels, delayBufferSize);
	processedBuffer.setSize(numChannels, samplesPerBlock);
	processedBuffer.clear();
	delayBuffer.clear();
	
}

void Delay::setParameters(int newDelayRate, float newFeedback, float newMix) {
	if (delayRate != newDelayRate) {
		delayRate = newDelayRate;
	}
	if (feedbackGain != newFeedback) {
		feedbackGain = newFeedback;
	}
	if (mixValue != newMix) {
		mixValue  = newMix;
	}
}

void Delay::process(juce::AudioBuffer<float>& buffer) {

	const int bufferLength = buffer.getNumSamples();
	const int delayBufferLength = delayBuffer.getNumSamples();
	processedBuffer = buffer;

	for (int channel = 0; channel < numChannels; ++channel)
	{
		const float* bufferData = processedBuffer.getReadPointer(channel);
		const float* delayBufferData = delayBuffer.getReadPointer(channel);

		float* dryData = buffer.getWritePointer(channel);
		float* ChannelData = processedBuffer.getWritePointer(channel);
		

		fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData);
		getFromDelayBuffer(channel, processedBuffer, delayBuffer);
		feedbackDelay(channel, bufferLength, delayBufferLength, ChannelData);

		for (int i = 0; i < buffer.getNumSamples(); i++)
		{
			dryData[i] = ChannelData[i] * mixValue + (1 - mixValue) * dryData[i];
		}
	}
	writePosition += bufferLength;
	writePosition %= delayBufferLength;
}

void Delay::fillDelayBuffer(int channel, int bufferLength, int delayBufferLength, const float* ChannelData) {
	if (delayBufferLength >= bufferLength + writePosition)
	{
		delayBuffer.copyFromWithRamp(channel, writePosition, ChannelData, bufferLength, 0.8, 0.8);
	}
	else {
		const int bufferRemaining = delayBufferLength - writePosition;
		delayBuffer.copyFromWithRamp(channel, writePosition, ChannelData, bufferRemaining, 0.8, 0.8);
		delayBuffer.copyFromWithRamp(channel, 0, ChannelData+bufferRemaining, bufferLength - bufferRemaining, 0.8, 0.8);
	}
}

void Delay::getFromDelayBuffer(int channel, juce::AudioBuffer<float>& buffer, juce::AudioBuffer<float>& delayBuffer) {

	auto bufferLength = buffer.getNumSamples();
	auto delayBufferLength = delayBuffer.getNumSamples();

	int readPosition = static_cast<int> (delayBufferLength + writePosition - (sampleRate * delayRate / 1000)) % delayBufferLength;

	if (delayBufferLength >= bufferLength + readPosition) {
		buffer.copyFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), bufferLength, 0.8, 0.8);
		
	}
	else {
		
		const int bufferRemaining = delayBufferLength - readPosition;
		buffer.copyFromWithRamp(channel, 0, delayBuffer.getReadPointer(channel, readPosition), bufferRemaining, 0.8, 0.8);
		buffer.copyFromWithRamp(channel, bufferRemaining, delayBuffer.getReadPointer(channel, 0), bufferLength - bufferRemaining, 0.8, 0.8);
	}
}

void Delay::feedbackDelay(int channel, int bufferLength, int delayBufferLength, float* ChannelData) {

	if (delayBufferLength >= bufferLength + writePosition) {
		delayBuffer.addFromWithRamp(channel, writePosition, ChannelData, bufferLength, feedbackGain, feedbackGain);
	}
	else {
		const int bufferRemaining = delayBufferLength - writePosition;
		//delayBuffer.addFromWithRamp(channel, bufferRemaining, ChannelData, bufferRemaining, feedbackGain, feedbackGain);
		//delayBuffer.addFromWithRamp(channel, 0, ChannelData+ bufferRemaining, bufferLength - bufferRemaining, feedbackGain, feedbackGain);
		delayBuffer.addFromWithRamp(channel, writePosition, ChannelData, bufferRemaining, feedbackGain, feedbackGain);
		delayBuffer.addFromWithRamp(channel, 0, ChannelData + bufferRemaining, bufferLength - bufferRemaining, feedbackGain, feedbackGain);
	}
}

