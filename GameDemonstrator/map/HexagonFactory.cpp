#include "stdafx.h"
#include "HexagonFactory.h"
#include "HexagonItem.h"

static const int HEXAGON_POINT_COUNT = 6;
const double HexagonFactory::HEXAGON_DISTANCE_CENTER_CORNER = 48.0;
static const QPointF HEXAGON_CENTER_POINT(0.0,0.0);

HexagonItem* HexagonFactory::CreateFlatTopped()
{
	HexagonItem* hexagonItem = new HexagonItem(CreateFlatToppedHexagon(HEXAGON_DISTANCE_CENTER_CORNER));
	return hexagonItem;
}

HexagonItem* HexagonFactory::CreatePointyTopped()
{
	HexagonItem* hexagonItem = new HexagonItem(CreatePointyToppedHexagon(HEXAGON_DISTANCE_CENTER_CORNER));
	return hexagonItem;
}

QPolygonF HexagonFactory::CreateFlatToppedHexagon(double sizeLength) const
{
	QPolygonF	hexPointsFlatTopped;
	for (int index = 0; index < HEXAGON_POINT_COUNT; index++)
	{
		QPointF shifted(48.0, 41.569219381653042); //TODO: Why this???
		hexPointsFlatTopped << CreateFlatToppedHexagonCorner(shifted, HEXAGON_DISTANCE_CENTER_CORNER, index);
	}
	return hexPointsFlatTopped;
}

QPointF HexagonFactory::CreateFlatToppedHexagonCorner(const QPointF& center, double distanceCenterCorner, unsigned int index) const
{
	double angle_deg = 60 * index;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = center.x() + distanceCenterCorner * cos(angle_rad);
	qreal y = center.y() + distanceCenterCorner * sin(angle_rad);
	return QPointF(x, y);
}

QPolygonF HexagonFactory::CreatePointyToppedHexagon(double sizeLength) const
{
	QPolygonF	hexPointsFlatTopped;
	for (int index = 0; index < HEXAGON_POINT_COUNT; index++)
	{
		hexPointsFlatTopped << CreateFlatToppedHexagonCorner(HEXAGON_CENTER_POINT, HEXAGON_DISTANCE_CENTER_CORNER, index);
	}
	return hexPointsFlatTopped;
}

QPointF HexagonFactory::CreatePointyToppedHexagonCorner(const QPointF& center, double distanceCenterCorner, unsigned int index) const
{
	double angle_deg = 60 * index - 30;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = center.x() + distanceCenterCorner * cos(angle_rad);
	qreal y = center.y() + distanceCenterCorner * sin(angle_rad);
	return QPointF(x, y);
}
