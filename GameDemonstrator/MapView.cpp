#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	m_Scene = new MapViewGraphicsScene(this);
}

MapView::~MapView()
{
	delete m_HexItemEventManager;
	delete m_MapEventManager;
}

#include "MapViewHexItem.h"
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
			MapViewHexItem *mapItem = new MapViewHexItem( defaultHexagon, QPointF(cordX,cordY) );
			mapItem->SetRow(row);
			mapItem->SetCol(col);
			mapItem->SetHexItemEventManager( m_HexItemEventManager );
			mapItem->setBrush( QBrush(Qt::green) );
			m_Scene->addItem( mapItem );
			m_MapEventManager->RegisterMapItem( mapItem );
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

void MapView::Init()
{
	int cols = 40;
	int rows = 20;

	m_MapEventManager->InitMapItemsRegistry(rows,cols);

	connect(m_HexItemEventManager,SIGNAL(HexItemEntered(int,int)),m_MapEventManager,SLOT(UpdateMapItemInfo(int,int)));

	double defaultHexSize = 48.0;
	HexagonData hexagonTemplate( defaultHexSize );
	CreateTestMap( cols, rows, hexagonTemplate );

	setScene(m_Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(cols,hexagonTemplate), CalcMapHeightInPixel(rows,hexagonTemplate) );

	setDragMode(ScrollHandDrag);
}
