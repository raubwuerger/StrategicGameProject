#include "stdafx.h"
#include "HexagonData.h"

static float const ROUND_VALUE = 0.5F;

/************************************************************************/
/* HexagonData                                                          */
/************************************************************************/
HexagonData::HexagonData( double sideLength )
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

void HexagonData::calcWidth()
{
	Width = 2.0 * SideLength;
}

void HexagonData::calcHeight()
{
	Height = sqrt(3) * SideLength;
}

void HexagonData::calcSide()
{
	Side = 3.0 / 2.0 * SideLength;
}

void HexagonData::calcBoundingRect()
{
	BoundingRect = QRectF(QPointF(-Width,-Height),QSizeF(Width, Height));
}

void HexagonData::calcHexPointsOrigin()
{
	HexPoints << QPointF( 0, Height * ROUND_VALUE) 
		<< QPointF( Width - Side, 0.0 ) 
		<< QPointF( Side,0.0 ) 
		<< QPointF( Width,Height * ROUND_VALUE ) 
		<< QPointF( Side,Height ) 
		<< QPointF( Width - Side,Height );
}

void HexagonData::MovePosition( const QPointF& topLeft )
{
	BoundingRect.moveTopLeft( topLeft );
	HexPoints.translate( topLeft );
}
