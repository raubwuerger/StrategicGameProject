#include "stdafx.h"
#include "MapView.h"
#include "MapGraphicsScene.h"
#include "MapHexItem.h"
#include "MapEventManager.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapRepository.h"
#include "LogInterface.h"
#include "MapUnitItem.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent),
	ROW_COL_NOT_INITIALIZED(-1),
	NO_ACTIVE_UNIT_ID(-1),
	ActiveRow(ROW_COL_NOT_INITIALIZED),
	ActiveCol(ROW_COL_NOT_INITIALIZED),
	ActiveUnitItemId(NO_ACTIVE_UNIT_ID)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	ConnectorMapHexItemInstance = new ConnectorMapHexItem;
	ConnectorMapUnitItemInstance = new ConnectorMapUnitItem;
	Scene = new MapGraphicsScene(this);
}

MapView::~MapView()
{
	delete ConnectorMapHexItemInstance;
	delete ConnectorMapUnitItemInstance;
	delete MapEventManagerInstance;
}

void MapView::Create()
{
	Scene->clear();
	InitMapEventManager();
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

ConnectorMapUnitItem* MapView::GetConnectorMapUnitItem() const
{
	return ConnectorMapUnitItemInstance;
}

bool MapView::AddMapHexItem(MapHexItem* mapHexItem)
{
	if (nullptr == mapHexItem )
	{
		return false;
	}
	mapHexItem->SetEventConnector(ConnectorMapHexItemInstance);
	Scene->addItem(mapHexItem);
	MapEventManagerInstance->RegisterMapHexItem(mapHexItem);
	return true;
}

bool MapView::AddedMapUnit(MapUnitItem *mapUnitItem)
{
	mapUnitItem->SetEventConnector(ConnectorMapUnitItemInstance);
	Scene->addItem(mapUnitItem);
	return false;
}

void MapView::InitMapEventManager()
{
	MapEventManagerInstance->InitGameMapRegistry();
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemEntered, this, &MapView::SlotHexMapItemActive);
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemEntered, MapEventManagerInstance, &MapEventManager::SlotUpdateMapItemInfo);

	connect(ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemEntered, this, &MapView::SlotUnitItemActive);
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

void MapView::SlotHexMapItemActive(int row, int col)
{
	ActiveRow = row;
	ActiveCol = col;
}

void MapView::SlotUnitItemActive(int unitItemId)
{
	ActiveUnitItemId = unitItemId;
}

void MapView::SlotUnitItemDeacivated()
{
	ActiveUnitItemId = NO_ACTIVE_UNIT_ID;
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
	if (false == QApplication::keyboardModifiers().testFlag(Qt::ControlModifier))
	{
		return;
	}
	QGraphicsView::wheelEvent(event);
	if( true == event->isAccepted() )
	{
		return;
	}

	DoZoom(event);
	event->accept();
}

void MapView::DoZoom(QWheelEvent *event)
{
	const qreal ZOOM_MAX = 3.0;
	const qreal ZOOM_MIN = 0.2;
	const qreal ZOOM_FACTOR = 1.6;
	QTransform currentTransformValue = this->transform();
	int y = event->angleDelta().y();
	if (event->angleDelta().y() > 0) //Vergrößern
	{
		if (currentTransformValue.m11() >= ZOOM_MAX)
		{
			return;
		}
		scale(ZOOM_FACTOR, ZOOM_FACTOR);
	}
	else
	{
		if (currentTransformValue.m11() <= ZOOM_MIN)
		{
			return;
		}
		scale(1.0 / ZOOM_FACTOR, 1.0 / ZOOM_FACTOR);
	}
}

