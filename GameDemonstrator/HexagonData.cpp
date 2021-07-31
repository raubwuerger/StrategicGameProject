#include "stdafx.h"
#include "HexagonData.h"

const float HexagonData::ROUND_VALUE = 0.5F;
const double HexagonData::DEFAULT_HEXE_SIZE = 48.0;
const double HexagonData::WIDTH_SIDE_MULTIPLICATOR = 2.0;
const double HexagonData::ZERO = 0.0;

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
	Width = WIDTH_SIDE_MULTIPLICATOR * SideLength;
}

void HexagonData::calcHeight()
{
	Height = sqrt(3) * SideLength;
}

void HexagonData::calcSide()
{
	Side = 3.0 / WIDTH_SIDE_MULTIPLICATOR * SideLength;
}

void HexagonData::calcBoundingRect()
{
	BoundingRect = QRectF(QPointF(-Width,-Height),QSizeF(Width, Height));
}

void HexagonData::calcHexPointsOrigin()
{
	HexPoints << QPointF( ZERO, Height * ROUND_VALUE) 
		<< QPointF( Width - Side, ZERO ) 
		<< QPointF( Side, ZERO ) 
		<< QPointF( Width,Height * ROUND_VALUE ) 
		<< QPointF( Side,Height ) 
		<< QPointF( Width - Side,Height );
}

void HexagonData::MovePosition( const QPointF& topLeft )
{
	BoundingRect.moveTopLeft( topLeft );
	HexPoints.translate( topLeft );
}
