#include "stdafx.h"
#include "ExperimentalClass.h"
#include <Qt>

QPointF flat_hex_corner(QPointF center, int size, unsigned int index)
{
	float angle_deg = 60 * index;
	float angle_rad = float(M_PI) / 180 * angle_deg;
	qreal x = center.x() +size * cos(angle_rad);
	qreal y = center.y() +size * sin(angle_rad);
	return QPointF(x, y);
}

QPointF pointy_hex_corner(QPointF center, int size, unsigned int index)
{
	float angle_deg = 60 * index - 30;
	float angle_rad = float(M_PI) / 180 * angle_deg;
	qreal x = center.x() + size * cos(angle_rad);
	qreal y = center.y() + size * sin(angle_rad);
	return QPointF(x, y);
}

void ExperimentalClass::DoExperimental()
{
	QPointF center(0,0);
	int distanceCenterCorner = 1;
	QPolygonF	HexPointsFlatTopped;
	for (int index = 0; index < 6; index++)
	{
		HexPointsFlatTopped << flat_hex_corner(center,distanceCenterCorner,index);
	}

	QPolygonF	HexPointsPointyTopped;
	for (int index = 0; index < 6; index++)
	{
		HexPointsPointyTopped << pointy_hex_corner(center, distanceCenterCorner, index);
	}

	int waitForBreakPoint = 0;
}
