#include "stdafx.h"
#include "MapView.h"
#include "MapGraphicsScene.h"
#include "MapHexItem.h"
#include "MapEventManager.h"
#include "HexItemEventManager.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "model/ModelMapRepository.h"
#include "LogInterface.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent),
	ROW_COL_NOT_INITIALIZED(-1),
	ActiveRow(ROW_COL_NOT_INITIALIZED),
	ActiveCol(ROW_COL_NOT_INITIALIZED)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	Scene = new MapGraphicsScene(this);
}

MapView::~MapView()
{
	delete HexItemEventManager;
	delete MapEventManager;
}

void MapView::Create()
{
	InitMapEventManager();
	if( false == CreateMapFromModel() )
	{
		return;
	}
	this->setRenderHint(QPainter::Antialiasing);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setScene(Scene);
	setSceneRect(0, 0, CalcMapWidthInPixel(), CalcMapHeightInPixel() );

	setDragMode(ScrollHandDrag);
}

void MapView::InitMapEventManager()
{
	MapEventManager->InitMapItemsRegistry( ModelMapRepository::GetInstance()->GetRows(), ModelMapRepository::GetInstance()->GetCols() );
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),MapEventManager,SLOT(UpdateMapItemInfo(int,int)));
	connect(HexItemEventManager,SIGNAL(HexItemEntered(int,int)),this,SLOT(HexActive(int,int)));
	Scene->HexItemEventManager = HexItemEventManager;
}

bool MapView::CreateMapFromModel()
{
	HexagonData hexagonTemplate( HexagonData::DEFAULT_HEXE_SIZE );

	const QVector< QVector<ModelMapItem*> >* modelMap = ModelMapRepository::GetInstance()->GetMapItems();
	if( nullptr == modelMap )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("ModelMapRepository contains no items!") );
		return false;
	}

	int rows = modelMap->size();
	for( int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<ModelMapItem*> row = modelMap->at(currentRow);
		int cols = row.size();
		for( int currentCol = 0; currentCol < cols; currentCol++ )
		{
			ModelMapItem* modelMapItem = row.at(currentCol);
			QPointF topLeftPosition;
			CreateTopLeftPosition(currentRow,currentCol,topLeftPosition);
			MapHexItem *mapItem = new MapHexItem( hexagonTemplate, topLeftPosition );
			mapItem->SetRowAndCol(currentRow,currentCol);
			mapItem->SetHexItemEventManager( HexItemEventManager );
			mapItem->SetModelMapItemId( modelMapItem->GetId() );
			const ModelTerrainType* modelTerrainType = modelMapItem->GetTerrainType();
			mapItem->SetTerrainImage( modelTerrainType->GetImage() );
			Scene->addItem( mapItem );
			MapEventManager->RegisterMapItem( mapItem );

		}
	}
	return true;
}

//TODO: Performance optimierung: Jede Zeile und Spalte hat immer genau zwei Werte. Diese kann man berechnen und dann entsprechend verwenden.
bool MapView::CreateTopLeftPosition(int row, int col, QPointF &topLeftPosition)
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


void MapView::mouseReleaseEvent(QMouseEvent * event)
{
	QGraphicsView::mouseReleaseEvent(event);
}

void MapView::mousePressEvent(QMouseEvent *event)
{
	QGraphicsView::mousePressEvent(event);
	EmitHexItemPressed();
}

void MapView::mouseMoveEvent(QMouseEvent *event)
{
	QGraphicsView::mouseMoveEvent(event);
	if (event->buttons() == Qt::LeftButton)
	{
		EmitHexItemPressed();
	}
}

void MapView::HexActive(int row, int col)
{
	ActiveRow = row;
	ActiveCol = col;
}

void MapView::EmitHexItemPressed()
{
	if( nullptr == HexItemEventManager )
	{
		return;
	}
	
	if( ROW_COL_NOT_INITIALIZED == ActiveRow )
	{
		return;
	}

	if( ROW_COL_NOT_INITIALIZED == ActiveCol )
	{
		return;
	}

	emit HexItemEventManager->HexItemPressed( ActiveRow, ActiveCol );
}

void MapView::wheelEvent(QWheelEvent *event)
{
	QGraphicsView::wheelEvent(event);
	if( true == event->isAccepted() )
	{
		return;
	}
	const qreal factor = 1.1;
	if( event->angleDelta().y() > 0 )
	{
		scale(factor,factor);
	}
	else
	{
		scale(1 / factor, 1 / factor );
	}
	event->accept();
}
