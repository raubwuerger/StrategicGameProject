#include "stdafx.h"
#include "MapView.h"
#include "MapGraphicsScene.h"
#include "MapHexItem.h"
#include "MapHexItemEventManager.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapItemRepository.h"
#include "LogInterface.h"
#include "MapUnitItem.h"
#include "controller/KeyEventController.h"
#include "MapCityItem.h"
#include "connectors/ConnectorMapCityItem.h"

MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	ConnectorMapHexItemInstance = new ConnectorMapHexItem;
	ConnectorMapUnitItemInstance = new ConnectorMapUnitItem;
	ConnectorMapCityItemInstance = new ConnectorMapCityItem;
	Scene = new MapGraphicsScene(this);
	KeyEventControllerInstance = new KeyEventController;
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

bool MapView::AddMapHexItem(MapHexItem* mapHexItem)
{
	if (nullptr == mapHexItem )
	{
		return false;
	}
	mapHexItem->SetEventConnector(ConnectorMapHexItemInstance);
	Scene->addItem(mapHexItem);
	return true;
}

bool MapView::AddedMapUnit(MapUnitItem *mapUnitItem)
{
	if (nullptr == mapUnitItem)
	{
		return false;
	}
	mapUnitItem->SetEventConnector(ConnectorMapUnitItemInstance);
	mapUnitItem->SetKeyEventController(KeyEventControllerInstance);
	Scene->addItem(mapUnitItem);
	return true;
}


bool MapView::RemoveMapUnit(MapUnitItem *mapUnitItem)
{
	if (nullptr == mapUnitItem)
	{
		return false;
	}
	Scene->removeItem(mapUnitItem);
	return true;
}

bool MapView::AddCity(MapCityItem *mapCityItem)
{
	if (nullptr == mapCityItem)
	{
		return false;
	}
	mapCityItem->SetEventConnector(ConnectorMapCityItemInstance);
	Scene->addItem(mapCityItem);
	return true;
}

bool MapView::RemoveCity(MapCityItem *mapCityItem)
{
	if (nullptr == mapCityItem)
	{
		return false;
	}

	Scene->removeItem(mapCityItem);
	return true;
}

void MapView::InitMapEventManager()
{
	connect(ConnectorMapHexItemInstance, &ConnectorMapHexItem::SignalHexItemEntered, MapEventManagerInstance, &MapHexItemEventManager::SlotUpdateMapItemInfo);

	connect(ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemEntered, MapEventManagerInstance, &MapHexItemEventManager::SlotUpdateMapUnitItemInfo);

	connect(ConnectorMapCityItemInstance, &ConnectorMapCityItem::SignalCityItemEntered, MapEventManagerInstance, &MapHexItemEventManager::SlotUpdateMapCityItemInfo); //TODO: Muss der MapView wissen welches Item aktiv ist?
	connect(ConnectorMapCityItemInstance, &ConnectorMapCityItem::SignalHexItemEntered, MapEventManagerInstance, &MapHexItemEventManager::SlotUpdateMapItemInfo); //TODO: Muss der MapView wissen welches Item aktiv ist?
}

double MapView::CalcMapWidthInPixel() const
{
	MapHexItemHexagonData hexagondata(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);
	return hexagondata.Width + ( (GameMapItemRepository::GetInstance()->GetCols() - 1 ) * hexagondata.Side );
}

double MapView::CalcMapHeightInPixel() const
{
	MapHexItemHexagonData hexagondata(MapHexItemHexagonData::DEFAULT_HEXE_SIZE);
	return (hexagondata.Height * GameMapItemRepository::GetInstance()->GetRows()) + ( hexagondata.Height / 2.0 );
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

