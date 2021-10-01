#include "stdafx.h"
#include "HexagonItem.h"

HexagonItem::HexagonItem(const QPolygonF& hexagon)
	: Hexagon(hexagon),
	SideLength(NOT_INITIALIZED_DOUBLE),
	CenterPoint(NOT_INITIALIZED_DOUBLE,NOT_INITIALIZED_DOUBLE),
	BoundingRectHeight(NOT_INITIALIZED_DOUBLE),
	BoundingRectWidth(NOT_INITIALIZED_DOUBLE),
	BoundingRect()
{

}

double HexagonItem::GetSideLength() const
{
	return SideLength;
}

double HexagonItem::GetBoundingRectHeight() const
{
	return BoundingRectHeight;
}

double HexagonItem::GetBoundingRectWidth() const
{
	return BoundingRectWidth;
}

QPolygonF HexagonItem::GetHexagon() const
{
	return Hexagon;
}

QRectF HexagonItem::GetBoundingRect() const
{
	return BoundingRect;
}
