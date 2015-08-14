#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	m_Scene = new MapViewGraphicsScene(this);

	double defaultHexSize = 48.0;
	HexagonData hexagonTemplate( defaultHexSize );
	int cols = 40;
	int rows = 20;
	CreateTestMap( cols, rows, hexagonTemplate );

	setScene(m_Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(cols,hexagonTemplate), CalcMapHeightInPixel(rows,hexagonTemplate) );

	//Use ScrollHand Drag Mode to enable Panning
	setDragMode(ScrollHandDrag);
}

MapView::~MapView()
{

}

void MapView::CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon )
{
	double startX = 0.0;
	double startY = 0.0;
	double offsetX = defaultHexagon.side;
	double offsetY = defaultHexagon.height;
	double offsetYEvenCol = defaultHexagon.height / 2.0;

	for( size_t row = 0; row < mapHeight; row++ )
	{
		for( size_t col = 0; col < mapWidth; col++ )
		{
			double cordX = startX + col * offsetX;
			double cordY = startY + row * offsetY;
			if( (col % 2) == 1 )
			{
				cordY += offsetYEvenCol;
			}
			m_Scene->addItem( new MapViewHexItem( defaultHexagon, QPointF(cordX,cordY) ) );
		}
	}
}

double MapView::CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const
{
	return hexagon.width + ( (hexagonCountCols - 1) * hexagon.side );
}

double MapView::CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const
{
	return (hexagon.height * hexagonCountRows) + ( hexagon.height / 2.0 );
}
