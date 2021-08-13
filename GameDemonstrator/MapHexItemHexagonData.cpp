#include "stdafx.h"
#include "MapHexItemHexagonData.h"

const float MapHexItemHexagonData::ROUND_VALUE = 0.5F;
const double MapHexItemHexagonData::DEFAULT_HEXE_SIZE = 48.0;
const double MapHexItemHexagonData::WIDTH_SIDE_MULTIPLICATOR = 2.0;
const double MapHexItemHexagonData::ZERO = 0.0;

/************************************************************************/
/* HexagonData                                                          */
/************************************************************************/
MapHexItemHexagonData::MapHexItemHexagonData( double sideLength )
	: SideLength(sideLength),
	Width(0.0),
	Height(0.0),
	Side(0.0)
{
	calcWidth();
	calcHeight();
	calcSide();
	calcBoundingRect();
	calcHexPointsOrigin();
}

void MapHexItemHexagonData::calcWidth()
{
	Width = WIDTH_SIDE_MULTIPLICATOR * SideLength;
}

void MapHexItemHexagonData::calcHeight()
{
	Height = sqrt(3) * SideLength;
}

void MapHexItemHexagonData::calcSide()
{
	Side = 3.0 / WIDTH_SIDE_MULTIPLICATOR * SideLength;
}

void MapHexItemHexagonData::calcBoundingRect()
{
	BoundingRect = QRectF(QPointF(-Width,-Height),QSizeF(Width, Height));
}

void MapHexItemHexagonData::calcHexPointsOrigin()
{
	HexPoints << QPointF( ZERO, Height * ROUND_VALUE) 
		<< QPointF( Width - Side, ZERO ) 
		<< QPointF( Side, ZERO ) 
		<< QPointF( Width,Height * ROUND_VALUE ) 
		<< QPointF( Side,Height ) 
		<< QPointF( Width - Side,Height );
}

void MapHexItemHexagonData::MovePosition( const QPointF& topLeft )
{
	BoundingRect.moveTopLeft( topLeft );
	HexPoints.translate( topLeft );
}
