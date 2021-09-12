#include "stdafx.h"
#include "StringToNumberConverter.h"

bool StringToNumberConverter::Convert(const QString& text, int &converted)
{
	bool conversionOk = false;
	converted = text.toInt(&conversionOk);
	return conversionOk;
}

bool StringToNumberConverter::Convert(const QString& text, double &converted)
{
	bool conversionOk = false;
	converted = text.toDouble(&conversionOk);
	return conversionOk;
}

bool StringToNumberConverter::Convert(const QString& text, float &converted)
{
	bool conversionOk = false;
	converted = text.toFloat(&conversionOk);
	return conversionOk;
}
