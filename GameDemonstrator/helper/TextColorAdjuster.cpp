#include "stdafx.h"
#include "TextColorAdjuster.h"

QColor TextColorAdjuster::GetAdjustedTextColor(const QColor& color)
{
	if (color == Qt::blue || color == Qt::green || color == Qt::darkGreen)
	{
		return Qt::white;
	}
	return Qt::black;
}
