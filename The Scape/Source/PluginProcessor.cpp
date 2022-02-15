#include "PluginProcessor.h"
#include "PluginEditor.h"

TheScapeAudioProcessor::TheScapeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
	),
	apvts(*this, nullptr, juce::Identifier("parameters"), {
												std::make_unique<juce::AudioParameterFloat>(INPUT_ID,
																							INPUT_NAME,
																							juce::NormalisableRange<float>(-24.0f, 24.0f),
																							0.0f),
												std::make_unique<juce::AudioParameterFloat>(OUTPUT_ID,
																							OUTPUT_NAME,
																							juce::NormalisableRange<float>(-24.0f, 24.0f),
																							0.0f),
												std::make_unique<juce::AudioParameterFloat>(ROOMSIZE_ID,
																							ROOMSIZE_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.5f),
												std::make_unique<juce::AudioParameterFloat>(DRYWET_ID,
																							DRYWET_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.5f),
												std::make_unique<juce::AudioParameterFloat>(DAMPING_ID,
																							DAMPING_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.0f),
												std::make_unique<juce::AudioParameterFloat>(WIDTH_ID,
																							WIDTH_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.5f),
												std::make_unique<juce::AudioParameterFloat>(DELAYRATE_ID,
																							DELAYRATE_NAME,
																							juce::NormalisableRange<float>(0.0f, 2000.0f),
																							350.0f),
												std::make_unique<juce::AudioParameterFloat>(FEEDBACK_ID,
																							FEEDBACK_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.3f),
												std::make_unique<juce::AudioParameterFloat>(MIX_ID,
																							MIX_NAME,
																							juce::NormalisableRange<float>(0.0f, 1.0f),
																							0.5f)
												})
#endif
{ 
	inputGainParameter = apvts.getRawParameterValue(INPUT_ID);
	outputGainParameter = apvts.getRawParameterValue(OUTPUT_ID);
	delayRateParameter = apvts.getRawParameterValue(DELAYRATE_ID);
	feedbackParameter = apvts.getRawParameterValue(FEEDBACK_ID);
	delayMixParameter = apvts.getRawParameterValue(MIX_ID);
	roomSizeParameter = apvts.getRawParameterValue(ROOMSIZE_ID);
	widthParameter = apvts.getRawParameterValue(WIDTH_ID);
	dampingParameter = apvts.getRawParameterValue(DAMPING_ID);
	wetParameter = apvts.getRawParameterValue(DRYWET_ID);
}

TheScapeAudioProcessor::~TheScapeAudioProcessor()
{
}

const juce::String TheScapeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheScapeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheScapeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheScapeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheScapeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheScapeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheScapeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheScapeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TheScapeAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheScapeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void TheScapeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = getTotalNumInputChannels();

	delay.setParameters((int)*delayRateParameter, *feedbackParameter, *delayMixParameter);
	delay.prepare(spec);
}

void TheScapeAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheScapeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheScapeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();

	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	buffer.applyGain((*inputGainParameter + 24.0f)/ 24.0f);

	delay.setParameters((int)*delayRateParameter, *feedbackParameter, *delayMixParameter);

	/*for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{
		auto* channelData = buffer.getWritePointer(channel);

		for (int sample = 0; sample < buffer.getNumSamples(); sample++)
		{
			channelData[sample] = ;
		}
	}*/
	delay.process(buffer);

	buffer.applyGain((*outputGainParameter + 24.0f) / 24.0f);
}

bool TheScapeAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* TheScapeAudioProcessor::createEditor()
{
    return new TheScapeAudioProcessorEditor (*this, apvts);
}

void TheScapeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	auto state = apvts.copyState();
	std::unique_ptr<juce::XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void TheScapeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(apvts.state.getType()))
			apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheScapeAudioProcessor();
}
