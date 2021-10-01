#include "stdafx.h"
#include "HexagonFactory.h"
#include "HexagonItem.h"

static const int HEXAGON_POINT_COUNT = 6;
const double HexagonFactory::HEXAGON_DISTANCE_CENTER_CORNER = 48.0;
static const QPointF HEXAGON_CENTER_POINT(48.0, 41.569219381653042); //TODO: Why this???

HexagonItem* HexagonFactory::CreateFlatTopped()
{
	HexagonItem* hexagonItem = new HexagonItem(CreateFlatToppedHexagon(HEXAGON_DISTANCE_CENTER_CORNER));
	hexagonItem->SideLength = HEXAGON_DISTANCE_CENTER_CORNER;
	hexagonItem->BoundingRectHeight = sqrt(3) * HEXAGON_DISTANCE_CENTER_CORNER;
	hexagonItem->BoundingRectWidth = 2.0 * HEXAGON_DISTANCE_CENTER_CORNER;
	hexagonItem->BoundingRect = QRectF(QPointF(-hexagonItem->GetBoundingRectWidth(), -hexagonItem->GetBoundingRectHeight()), QSizeF(hexagonItem->GetBoundingRectWidth(), hexagonItem->GetBoundingRectHeight()));
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
		hexPointsFlatTopped << CreateFlatToppedHexagonCorner(HEXAGON_DISTANCE_CENTER_CORNER, index);
	}
	return hexPointsFlatTopped;
}

QPointF HexagonFactory::CreateFlatToppedHexagonCorner(double distanceCenterCorner, unsigned int index) const
{
	double angle_deg = 60 * index;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = HEXAGON_CENTER_POINT.x() + distanceCenterCorner * cos(angle_rad);
	qreal y = HEXAGON_CENTER_POINT.y() + distanceCenterCorner * sin(angle_rad);
	return QPointF(x, y);
}

QPolygonF HexagonFactory::CreatePointyToppedHexagon(double sizeLength) const
{
	QPolygonF	hexPointsFlatTopped;
	for (int index = 0; index < HEXAGON_POINT_COUNT; index++)
	{
		hexPointsFlatTopped << CreateFlatToppedHexagonCorner(HEXAGON_DISTANCE_CENTER_CORNER, index);
	}
	return hexPointsFlatTopped;
}

QPointF HexagonFactory::CreatePointyToppedHexagonCorner(double distanceCenterCorner, unsigned int index) const
{
	double angle_deg = 60 * index - 30;
	double angle_rad = double(M_PI) / 180 * angle_deg;
	qreal x = HEXAGON_CENTER_POINT.x() + distanceCenterCorner * cos(angle_rad);
	qreal y = HEXAGON_CENTER_POINT.y() + distanceCenterCorner * sin(angle_rad);
	return QPointF(x, y);
}
