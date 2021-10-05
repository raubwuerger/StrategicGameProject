#include "stdafx.h"
#include "StringToBoolConverter_TEST.h"
#include "StringToBoolConverter.h"

void StringToBoolConverter_TEST::Test()
{
	int VALID_0 = 0;
	int VALID_1 = 1;
	int INVALID_2 = 2;
	int INVALID_neg1 = -1;

	QString VALID_TRUE = "trUe";
	QString VALID_OK = "OK";
	QString VALID_FALSE = "FaLSe";
	QString VALID_NOK = "nok";

	QString INVALID_NULL;
	QString INVALID_EMPTY = "";
	QString INVALID_TOLONG = "Falses";
	QString INVALID_TOSHORT = "n";

	bool booleanValue;

	StringToBoolConverter Converter;
	if (false == Converter.Convert(QString::number(VALID_0), &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (false == Converter.Convert(QString::number(VALID_1), &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(QString::number(INVALID_2), &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(QString::number(INVALID_neg1), &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(QString::number(INT_MAX), &booleanValue))
	{
		Q_ASSERT(false);
	}
	
	if (true == Converter.Convert(QString::number(INT_MIN), &booleanValue))
	{
		Q_ASSERT(false);
	}
	
	if (false == Converter.Convert(VALID_TRUE, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (false == Converter.Convert(VALID_OK, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (false == Converter.Convert(VALID_FALSE, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (false == Converter.Convert(VALID_NOK, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(INVALID_NULL, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(INVALID_EMPTY, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(INVALID_TOLONG, &booleanValue))
	{
		Q_ASSERT(false);
	}

	if (true == Converter.Convert(INVALID_TOSHORT, &booleanValue))
	{
		Q_ASSERT(false);
	}
}
