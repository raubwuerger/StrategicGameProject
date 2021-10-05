#include "stdafx.h"
#include "StringToBoolConverter.h"

static const QString BOOLEAN_TRUE = "true";
static const QString BOOLEAN_FALSE = "false";
static const QString BOOLEAN_OK = "ok";
static const QString BOOLEAN_NOK = "nok";

bool StringToBoolConverter::Convert(const QString& text, bool* value) const
{
	return DoConvert(text,value);
}

bool StringToBoolConverter::DoConvert(const QString& text, bool* value) const
{
	if (false == IsInteger(text))
	{
		return ConvertBooleanFromString(text, value);
	}
	
	return ConvertBooleanFromInteger(text, value);
}

bool StringToBoolConverter::IsInteger(const QString& text) const
{
	bool conversionOk;
	int isInteger = text.toInt(&conversionOk);
	if (false == conversionOk)
	{
		return false;
	}
	return true;
}

bool StringToBoolConverter::ConvertBooleanFromInteger(const QString& text, bool* value) const
{
	bool conversionOk;
	int intValue = text.toInt(&conversionOk);
	if (false == conversionOk)
	{
		return false;
	}
	if (intValue == 0)
	{
		*value = false;
		return true;
	}
	if (intValue == 1)
	{
		*value = true;
		return true;
	}
	return false;
}

bool StringToBoolConverter::ConvertBooleanFromString(const QString& text, bool* value) const
{
	QString textLowerCase = text.toLower();
	if (textLowerCase == BOOLEAN_TRUE)
	{
		*value = true;
		return true;
	}

	if (textLowerCase == BOOLEAN_OK)
	{
		*value = true;
		return true;
	}

	if (textLowerCase == BOOLEAN_FALSE)
	{
		*value = false;
		return true;
	}

	if (textLowerCase == BOOLEAN_NOK)
	{
		*value = false;
		return true;
	}

	return false;
}
