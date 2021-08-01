#include "stdafx.h"
#include "MapView.h"
#include "MapViewGraphicsScene.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"
#include "HexItemEventManager.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "../model/ModelMapRepository.h"

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
	InitMapEventManager();
	CreateMap();

	setScene(Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(), CalcMapHeightInPixel() );

	setDragMode(ScrollHandDrag);
}

void MapView::InitMapEventManager()
{
	MapEventManager->InitMapItemsRegistry( ModelMapRepository::GetInstance()->GetRows(), ModelMapRepository::GetInstance()->GetCols() );
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),MapEventManager,SLOT(UpdateMapItemInfo(int,int)));
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),Scene,SLOT(HexActive(int,int)));
	Scene->HexItemEventManager = HexItemEventManager;
}

#include "MapViewHexItem.h"
void MapView::CreateMap()
{
	HexagonData hexagonTemplate( HexagonData::DEFAULT_HEXE_SIZE );

	const QVector< QVector<ModelMapItem*> >*modelMap = ModelMapRepository::GetInstance()->GetMapItems();
	unsigned int rows = modelMap->length();
	unsigned int cols = modelMap->at(0).length();

	double startX = 0.0;
	double offsetX = hexagonTemplate.Side;

	double startY = 0.0;
	double offsetY = hexagonTemplate.Height;

	double offsetYEvenCol = hexagonTemplate.Height / 2.0;

	for( size_t row = 0; row < rows; row++ )
	{
		for( size_t col = 0; col < cols; col++ )
		{
			double cordX = startX + col * offsetX;
			double cordY = startY + row * offsetY;
			if( (col % 2) == 1 )
			{
				cordY += offsetYEvenCol;
			}
			MapViewHexItem *mapItem = new MapViewHexItem( hexagonTemplate, QPointF(cordX,cordY) );

			QPointF calculatedByFunction;
			CreateTopLeftPosition(col,row,calculatedByFunction);

			mapItem->SetRowAndCol(row,col);
			mapItem->SetHexItemEventManager( HexItemEventManager );
//TODO:	Load image from modelTerrainType
//			mapItem->SetTerrainImage( defaultTerrainType );
			Scene->addItem( mapItem );
			MapEventManager->RegisterMapItem( mapItem );
		}
	}
}

//TODO: Performance optimierung: Jede Zeile und Spalte hat immer genau zwei Werte. Diese kann man berechnen und dann entsprechend verwenden.
bool MapView::CreateTopLeftPosition(int col, int row, QPointF &topLeftPosition)
{
	HexagonData hexagonTemplate( HexagonData::DEFAULT_HEXE_SIZE );

	double startX = 0.0;
	double offsetX = hexagonTemplate.Side;

	double startY = 0.0;
	double offsetY = hexagonTemplate.Height;

	double offsetYEvenCol = hexagonTemplate.Height / 2.0;
	double cordX = startX + col * offsetX;
	double cordY = startY + row * offsetY;
	if( (col % 2) == 1 )
	{
		cordY += offsetYEvenCol;
	}

	topLeftPosition.setX(cordX);
	topLeftPosition.setY(cordY);
	return true;
}



void MapView::CreateMapFromModel()
{

}


double MapView::CalcMapWidthInPixel() const
{
	HexagonData hexagondata(HexagonData::DEFAULT_HEXE_SIZE);
	return hexagondata.Width + ( (ModelMapRepository::GetInstance()->GetCols() - 1 ) * hexagondata.Side );
}

double MapView::CalcMapHeightInPixel() const
{
	HexagonData hexagondata(HexagonData::DEFAULT_HEXE_SIZE);
	return (hexagondata.Height * ModelMapRepository::GetInstance()->GetRows()) + ( hexagondata.Height / 2.0 );
}
