#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"
#include "HexItemEventManager.h"
#include "TerrainTypeRepository.h"
#include "TerrainType.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	Scene = new MapViewGraphicsScene(this);
}

MapView::~MapView()
{
	delete HexItemEventManager;
	delete MapEventManager;
}

#include "model/ModelDataOverallSettings.h"
void MapView::Create()
{
	unsigned int cols = ModelDataOverallSettings::GetInstance()->GetGameMapConfig()->Cols;
	unsigned int rows = ModelDataOverallSettings::GetInstance()->GetGameMapConfig()->Rows;
	MapEventManager->InitMapItemsRegistry( rows, cols );
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),MapEventManager,SLOT(UpdateMapItemInfo(int,int)));
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),Scene,SLOT(HexActive(int,int)));
	Scene->HexItemEventManager = HexItemEventManager;

	double defaultHexSize = 48.0;
	HexagonData hexagonTemplate( defaultHexSize );
	CreateTestMap( cols, rows, hexagonTemplate, TerrainTypeRepository::GetInstance()->GetDefaultTerrainType()->GetImage() );

	setScene(Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(cols,hexagonTemplate), CalcMapHeightInPixel(rows,hexagonTemplate) );

	setDragMode(ScrollHandDrag);
}

#include "MapViewHexItem.h"
void MapView::CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon, const QImage* defaultTerrainType  )
{
	double startX = 0.0;
	double startY = 0.0;
	double offsetX = defaultHexagon.Side;
	double offsetY = defaultHexagon.Height;
	double offsetYEvenCol = defaultHexagon.Height / 2.0;

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
			mapItem->SetRowAndCol(row,col);
			mapItem->SetHexItemEventManager( HexItemEventManager );
			mapItem->SetTerrainImage( defaultTerrainType );
			Scene->addItem( mapItem );
			MapEventManager->RegisterMapItem( mapItem );
		}
	}
}

double MapView::CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const
{
	return hexagon.Width + ( (hexagonCountCols - 1) * hexagon.Side );
}

double MapView::CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const
{
	return (hexagon.Height * hexagonCountRows) + ( hexagon.Height / 2.0 );
}
