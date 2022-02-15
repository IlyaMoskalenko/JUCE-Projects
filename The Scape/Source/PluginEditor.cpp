#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheScapeAudioProcessorEditor::TheScapeAudioProcessorEditor (TheScapeAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{

	inputAttachment.reset(new SliderAttachment(valueTreeState, INPUT_ID, inputDial));
	outputAttachment.reset(new SliderAttachment(valueTreeState, OUTPUT_ID, outputDial));
	delayRateAttachment.reset(new SliderAttachment(valueTreeState, DELAYRATE_ID, delayRateDial));
	feedbackAttachment.reset(new SliderAttachment(valueTreeState, FEEDBACK_ID, feedbackDial));
	delayMixAttachment.reset(new SliderAttachment(valueTreeState, MIX_ID, delayMixDial));
	roomSizeAttachment.reset(new SliderAttachment(valueTreeState, ROOMSIZE_ID, roomSizeDial));
	widthAttachment.reset(new SliderAttachment(valueTreeState, WIDTH_ID, widthDial));
	dampingAttachment.reset(new SliderAttachment(valueTreeState, DAMPING_ID, dampingDial));
	wetAttachment.reset(new SliderAttachment(valueTreeState, DRYWET_ID, wetDial));

	inputLabel.setText(INPUT_NAME, juce::dontSendNotification);
	inputLabel.setJustificationType(juce::Justification::centredBottom);
	inputLabel.attachToComponent(&inputDial, false);
	addAndMakeVisible(inputLabel);
	addAndMakeVisible(inputDial);

	outputLabel.setText(OUTPUT_NAME, juce::dontSendNotification);
	outputLabel.setJustificationType(juce::Justification::centredBottom);
	outputLabel.attachToComponent(&outputDial, false);
	addAndMakeVisible(outputLabel);
	addAndMakeVisible(outputDial);

	delayRateLabel.setText(DELAYRATE_NAME, juce::dontSendNotification);
	delayRateLabel.setJustificationType(juce::Justification::centredBottom);
	delayRateLabel.attachToComponent(&delayRateDial, false);
	addAndMakeVisible(delayRateLabel);
	addAndMakeVisible(delayRateDial);

	feedbackLabel.setText(FEEDBACK_NAME, juce::dontSendNotification);
	feedbackLabel.setJustificationType(juce::Justification::centredBottom);
	feedbackLabel.attachToComponent(&feedbackDial, false);
	addAndMakeVisible(feedbackLabel);
	addAndMakeVisible(feedbackDial);

	delayMixLabel.setText(MIX_NAME, juce::dontSendNotification);
	delayMixLabel.setJustificationType(juce::Justification::centredBottom);
	delayMixLabel.attachToComponent(&delayMixDial, false);
	addAndMakeVisible(delayMixLabel);
	addAndMakeVisible(delayMixDial);

	roomSizeLabel.setText(ROOMSIZE_NAME, juce::dontSendNotification);
	roomSizeLabel.setJustificationType(juce::Justification::centredBottom);
	roomSizeLabel.attachToComponent(&roomSizeDial, false);
	addAndMakeVisible(roomSizeLabel);
	addAndMakeVisible(roomSizeDial);

	widthLabel.setText(WIDTH_NAME, juce::dontSendNotification);
	widthLabel.setJustificationType(juce::Justification::centredBottom);
	widthLabel.attachToComponent(&widthDial, false);
	addAndMakeVisible(widthLabel);
	addAndMakeVisible(widthDial);

	dampingLabel.setText(DAMPING_NAME, juce::dontSendNotification);
	dampingLabel.setJustificationType(juce::Justification::centredBottom);
	dampingLabel.attachToComponent(&dampingDial, false);
	addAndMakeVisible(dampingLabel);
	addAndMakeVisible(dampingDial);

	wetLabel.setText(DRYWET_NAME, juce::dontSendNotification);
	wetLabel.setJustificationType(juce::Justification::centredBottom);
	wetLabel.attachToComponent(&wetDial, false);
	addAndMakeVisible(wetLabel);
	addAndMakeVisible(wetDial);

	setSize(1000, 600);
}

TheScapeAudioProcessorEditor::~TheScapeAudioProcessorEditor()
{
}

//==============================================================================
void TheScapeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);
	juce::Rectangle<int> delayTitle(80, 180, 340, 20);
	g.drawText("Delay", delayTitle, juce::Justification::centredBottom);

	juce::Rectangle<int> reverbTitle(480, 180, 440, 20);
	g.drawText("Reverb", reverbTitle, juce::Justification::centredBottom);

	g.setColour(juce::Colour(82, 131, 163));
	juce::Rectangle<float> DelayArea(80, 210, 340, 180);
	g.drawRoundedRectangle(DelayArea, 10.0f, 2.0f);

	juce::Rectangle<float> ReverbArea(480, 210, 440, 180);
	g.drawRoundedRectangle(ReverbArea, 10.0f, 2.0f);


}

void TheScapeAudioProcessorEditor::resized()
{
	inputDial.setBounds(20, 20, 100, 100);
	outputDial.setBounds(1000 - 120, 20, 100, 100);

	delayRateDial.setBounds(100, 250, 100, 100);
	feedbackDial.setBounds(200, 250, 100, 100);
	delayMixDial.setBounds(300, 250, 100, 100);

	dampingDial.setBounds(1000-200, 250, 100, 100);
	widthDial.setBounds(1000 - 300, 250, 100, 100);
	roomSizeDial.setBounds(1000 - 400, 250, 100, 100);
	wetDial.setBounds(1000 - 500, 250, 100, 100);

}
