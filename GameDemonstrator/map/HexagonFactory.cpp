#include "stdafx.h"
#include "HexagonFactory.h"
#include "HexagonItem.h"

static const int HEXAGON_POINT_COUNT = 6;
const double HexagonFactory::HEXAGON_DISTANCE_CENTER_CORNER = 48.0;
static const QPointF HEXAGON_CENTER_POINT(48.0, 41.569219381653042); //TODO: Why this???
static const double BOUNDING_RECT_WIDTH_MULTIPLIER = 2.0;
static const double CIRCLE_HALF_IN_DEGREE = 180.0;
static const double CIRCLE_SIXTHS_IN_DEGREE = 60.0;
static const double CIRCLE_TWELFTH_IN_DEGREE = 30.0;

HexagonItem* HexagonFactory::CreateFlatTopped()
{
	HexagonItem* hexagonItem = new HexagonItem(CreateFlatToppedHexagon(HEXAGON_DISTANCE_CENTER_CORNER));
	hexagonItem->SideLength = HEXAGON_DISTANCE_CENTER_CORNER;
	hexagonItem->BoundingRectHeight = SQUARE_ROOT_THREE * HEXAGON_DISTANCE_CENTER_CORNER;
	hexagonItem->BoundingRectWidth = BOUNDING_RECT_WIDTH_MULTIPLIER * HEXAGON_DISTANCE_CENTER_CORNER;
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
	double angle_deg = CIRCLE_SIXTHS_IN_DEGREE * index;
	double angle_rad = double(M_PI) / CIRCLE_HALF_IN_DEGREE * angle_deg;
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
	double angle_deg = CIRCLE_SIXTHS_IN_DEGREE * index - CIRCLE_TWELFTH_IN_DEGREE;
	double angle_rad = double(M_PI) / CIRCLE_HALF_IN_DEGREE * angle_deg;
	qreal x = HEXAGON_CENTER_POINT.x() + distanceCenterCorner * cos(angle_rad);
	qreal y = HEXAGON_CENTER_POINT.y() + distanceCenterCorner * sin(angle_rad);
	return QPointF(x, y);
}
