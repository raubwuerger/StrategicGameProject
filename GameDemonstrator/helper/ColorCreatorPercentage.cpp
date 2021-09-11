#include "stdafx.h"
#include "ColorCreatorPercentage.h"

ColorCreatorPercentage::ColorCreatorPercentage()
	: BorderRed(NOT_INITIALIZED_INT)
{
	LightRed = QColor(255, 51, 51);
	LightYellow = QColor(255, 255, 224);
	LightGreen = QColor(144, 238, 144);
	BorderGreen = 0.8;
	BorderRed = 0.2;
}

QColor ColorCreatorPercentage::Create(double value)
{
	ColorCreatorPercentage colorCreteatorPercentage;
	if (value >= colorCreteatorPercentage.BorderGreen)
	{
		return colorCreteatorPercentage.LightGreen;
	}

	if (value <= colorCreteatorPercentage.BorderRed)
	{
		return colorCreteatorPercentage.LightRed;
	}

	return colorCreteatorPercentage.LightYellow;
}
