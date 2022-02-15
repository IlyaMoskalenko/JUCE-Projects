#include "Dial.h"

Dial :: Dial()
{
	setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
	setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);
	/*setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
						juce::MathConstants<float>::pi * 2.75f,
						true);*/
	//setRange(0.0f, 100.0f, 0.01);
	setDoubleClickReturnValue(true, 0.0f);
	setTextValueSuffix(" %");
	setNumDecimalPlacesToDisplay(2);
	onValueChange = [&]()
	{
		/*if (getValue() < 10)
			setNumDecimalPlacesToDisplay(2);
		else if (10 <= getValue() && getValue() < 100)
			setNumDecimalPlacesToDisplay(1);
		else
			setNumDecimalPlacesToDisplay(0);*/
	};

}

Dial::~Dial()
{
}