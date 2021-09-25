#include "stdafx.h"
#include "ExperimentalClass.h"
#include <Qt>

QPointF CreateFlatHexCorner(QPointF center, double size, unsigned int index)
{
	double angle_deg = 60 * index;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = center.x() +size * cos(angle_rad);
	qreal y = center.y() +size * sin(angle_rad);
	return QPointF(x, y);
}

QPointF CreatePointyHexCorner(QPointF center, double size, unsigned int index)
{
	double angle_deg = 60 * index - 30;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = center.x() + size * cos(angle_rad);
	qreal y = center.y() + size * sin(angle_rad);
	return QPointF(x, y);
}

float CalculateHexSideLength(const QPolygonF& hexPoints, int startingPoint)
{
	int destinationPoint = startingPoint + 1;
	if (destinationPoint >= hexPoints.size())
	{
		destinationPoint = 0;
	}
	QLineF length(hexPoints.at(startingPoint), hexPoints.at(destinationPoint));
	return length.length();
}

void ExperimentalClass::DoExperimental() const
{
	QPointF center(0,0);
	double distanceCenterCorner = 48.0;
	QPolygonF	HexPointsFlatTopped;
	for (int index = 0; index < 6; index++)
	{
		HexPointsFlatTopped << CreateFlatHexCorner(center,distanceCenterCorner,index);
	}

	QPolygonF	HexPointsPointyTopped;
	for (int index = 0; index < 6; index++)
	{
		HexPointsPointyTopped << CreatePointyHexCorner(center, distanceCenterCorner, index);
	}

	QVector<double> HexPointsFlatToppedSideLength;
	for (int index = 0; index < 6; index++)
	{
		HexPointsFlatToppedSideLength << CalculateHexSideLength(HexPointsFlatTopped, index);
	}

	QVector<double> HexPointsPointyToppedSideLength;
	for (int index = 0; index < 6; index++)
	{
		HexPointsPointyToppedSideLength << CalculateHexSideLength(HexPointsPointyTopped, index);
	}

	/*
	QVector<double> HexPointsHexagonDataSideLength;
	MapHexItemHexagonData mapHexItemHexagonData(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);
	for (int index = 0; index < 6; index++)
	{
		HexPointsHexagonDataSideLength << CalculateHexSideLength(mapHexItemHexagonData.GetHexPoints(), index);
	}
	*/
	int waitForBreakPoint = 0;
}
