#include "stdafx.h"
#include "MapView.h"
#include "MapGraphicsScene.h"
#include "MapHexItem.h"
#include "MapEventManager.h"
#include "connectors/ConnectorMapHexItem.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapRepository.h"
#include "LogInterface.h"
#include "MapUnitItem.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent),
	ROW_COL_NOT_INITIALIZED(-1),
	ActiveRow(ROW_COL_NOT_INITIALIZED),
	ActiveCol(ROW_COL_NOT_INITIALIZED)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	ConnectorMapHexItemInstance = new ConnectorMapHexItem();
	Scene = new MapGraphicsScene(this);
}

MapView::~MapView()
{
	delete ConnectorMapHexItemInstance;
	delete MapEventManagerInstance;
}

void MapView::Create()
{
	InitMapEventManager();
	if (false == CreateGameFromModel())
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

ConnectorMapHexItem* MapView::GetConnectorMapHexItem() const
{
	return ConnectorMapHexItemInstance;
}

bool MapView::AddedMapUnit(int row, int col, MapUnitItem *mapUnitItem)
{
	Scene->addItem(mapUnitItem);
	return false;
}

void MapView::InitMapEventManager()
{
	MapEventManagerInstance->InitMapItemsRegistry(GameMapRepository::GetInstance()->GetRows(), GameMapRepository::GetInstance()->GetCols());
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemEntered, this, &MapView::SlotHexActive);
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemEntered, MapEventManagerInstance, &MapEventManager::SlotUpdateMapItemInfo);
}

bool MapView::CreateGameFromModel()
{
	if (false == CreateMapFromModel())
	{
		return false;
	}
	if (false == CreateUnitsFromModel())
	{
		return false;
	}
	return true;
}

bool MapView::CreateMapFromModel()
{
	HexagonData hexagonTemplate( HexagonData::DEFAULT_HEXE_SIZE );

	const QVector< QVector<GameMapItem*> >* modelMap = GameMapRepository::GetInstance()->GetMapItems();
	if( nullptr == modelMap )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("ModelMapRepository contains no items!") );
		return false;
	}

	int rows = modelMap->size();
	for( int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapItem*> row = modelMap->at(currentRow);
		int cols = row.size();
		for( int currentCol = 0; currentCol < cols; currentCol++ )
		{
			GameMapItem* modelMapItem = row.at(currentCol);
			QPointF topLeftPosition;
			CreateTopLeftPosition(currentRow,currentCol,topLeftPosition);
			MapHexItem *mapItem = new MapHexItem( hexagonTemplate, topLeftPosition );
			mapItem->SetRowAndCol(currentRow,currentCol);
			mapItem->SetHexItemEventManager( ConnectorMapHexItemInstance );
			mapItem->SetModelMapItemId( modelMapItem->GetId() );
			mapItem->SetTerrainImage( GetImage(modelMapItem) );
			Scene->addItem( mapItem );
			MapEventManagerInstance->RegisterMapItem( mapItem );

		}
	}

	return true;
}

#include "game/GameUnitItemRepository.h"
bool MapView::CreateUnitsFromModel()
{

	QMap<int, GameUnitItem*>::const_iterator gameUnitIterator = GameUnitItemRepository::GetInstance()->GetFirstIterator();
	while (gameUnitIterator != GameUnitItemRepository::GetInstance()->GetLastIterator())
	{
		GameUnitItem* currentGameUnit = gameUnitIterator.value();
		int gameMapItemId = currentGameUnit->GetGameMapItemId();
		GameMapItem* gameMapItem = GameMapRepository::GetInstance()->GetGameMapItemById(gameMapItemId);
		if (nullptr == gameMapItem)
		{
			gameUnitIterator++;
			continue;

		}
		MapUnitItem* newMapUnitItem = new MapUnitItem(gameMapItem->Get);
		gameUnitIterator++;
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

const QImage* MapView::GetImage(const GameMapItem* modelMapItem)
{
	const ModelTerrainType* modelTerrainType = modelMapItem->GetTerrainType();
	if (nullptr == modelTerrainType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelTerrainType->GetImage();
}

double MapView::CalcMapWidthInPixel() const
{
	HexagonData hexagondata(HexagonData::DEFAULT_HEXE_SIZE);
	return hexagondata.Width + ( (GameMapRepository::GetInstance()->GetCols() - 1 ) * hexagondata.Side );
}

double MapView::CalcMapHeightInPixel() const
{
	HexagonData hexagondata(HexagonData::DEFAULT_HEXE_SIZE);
	return (hexagondata.Height * GameMapRepository::GetInstance()->GetRows()) + ( hexagondata.Height / 2.0 );
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

void MapView::SlotHexActive(int row, int col)
{
	ActiveRow = row;
	ActiveCol = col;
}

void MapView::EmitHexItemPressed()
{
	if( nullptr == ConnectorMapHexItemInstance )
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

	emit ConnectorMapHexItemInstance->SignalHexItemPressed(ActiveRow, ActiveCol);
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
