#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"
#include "GameInitialisationData.h"
#include "HexItemEventManager.h"
#include "TerrainTypeRepository.h"
#include "TerrainType.h"

CMapView::CMapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	Scene = new MapViewGraphicsScene(this);
}

CMapView::~CMapView()
{
	delete HexItemEventManager;
	delete MapEventManager;
}

#include "model/GameDataConfig.h"
void CMapView::Create()
{
	unsigned int cols = GameDataConfig::GetInstance()->TheGameMapConfig.Cols;
	unsigned int rows = GameDataConfig::GetInstance()->TheGameMapConfig.Rows;
	MapEventManager->InitMapItemsRegistry( cols, rows );
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),MapEventManager,SLOT(UpdateMapItemInfo(int,int)));
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),Scene,SLOT(HexActive(int,int)));
	Scene->HexItemEventManager = HexItemEventManager;

	double defaultHexSize = 48.0;
	HexagonData hexagonTemplate( defaultHexSize );
	CreateTestMap( cols, rows, hexagonTemplate, CTerrainTypeRepository::GetInstance()->GetDefaultTerrainType()->GetImage() );

	setScene(Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(cols,hexagonTemplate), CalcMapHeightInPixel(rows,hexagonTemplate) );

	setDragMode(ScrollHandDrag);
}

//TODO: Muss hier CTerrainTypeRepository übergeben werden, oder tut es defaultTerrainType auch???
#include "TerrainType.h"
void CMapView::Init( const CGameInitialisationData &data, const CTerrainType* defaultTerrainType )
{
	MapEventManager->InitMapItemsRegistry(data.Rows,data.Cols);

	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),MapEventManager,SLOT(UpdateMapItemInfo(int,int)));
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),Scene,SLOT(HexActive(int,int)));
	Scene->HexItemEventManager = HexItemEventManager;

	double defaultHexSize = 48.0;
	HexagonData hexagonTemplate( defaultHexSize );
	CreateTestMap( data.Cols, data.Rows, hexagonTemplate, defaultTerrainType->GetImage() );

	setScene(Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(data.Cols,hexagonTemplate), CalcMapHeightInPixel(data.Rows,hexagonTemplate) );

	setDragMode(ScrollHandDrag);
}

#include "MapViewHexItem.h"
void CMapView::CreateTestMap( int mapWidth, int mapHeight, const HexagonData& defaultHexagon, const QImage* defaultTerrainType  )
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

double CMapView::CalcMapWidthInPixel( int hexagonCountCols, const HexagonData& hexagon ) const
{
	return hexagon.Width + ( (hexagonCountCols - 1) * hexagon.Side );
}

double CMapView::CalcMapHeightInPixel( int hexagonCountRows, const HexagonData& hexagon ) const
{
	return (hexagon.Height * hexagonCountRows) + ( hexagon.Height / 2.0 );
}
