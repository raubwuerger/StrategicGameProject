#include "stdafx.h"
#include "MapView.h"
#include "MapGraphicsScene.h"
#include "MapHexItem.h"
#include "MapHexItemEventManager.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorMapUnitItem.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapTileRepository.h"
#include "LogInterface.h"
#include "MapUnitItem.h"
#include "controller/KeyEventController.h"
#include "MapCityItem.h"
#include "connectors/ConnectorMapCityItem.h"
#include "HexagonFactory.h"

ConnectorMapHexItem*	MapView::ConnectorMapHexItemInstance = new ConnectorMapHexItem;
ConnectorMapUnitItem*	MapView::ConnectorMapUnitItemInstance = new ConnectorMapUnitItem;
ConnectorMapCityItem*	MapView::ConnectorMapCityItemInstance = new ConnectorMapCityItem;


MapView::MapView(QWidget *parent)
	: QGraphicsView(parent)
{
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	Scene = new MapGraphicsScene(this);
	KeyEventControllerInstance = new KeyEventController;
	OriginalTransformValue = this->transform();
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
	jha::GetLog()->Log_MESSAGE(tr("Successful added MapUnitItem on hex id=%1").arg(QString::number(mapUnitItem->GetMapHexItemId())));
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

bool MapView::UpdateCity(MapCityItem *mapCityItem)
{
	if (nullptr == mapCityItem)
	{
		return false;
	}

	mapCityItem->update();
	return true;
}

const qreal ZOOM_MAX = 3.0;
const qreal ZOOM_MIN = 0.2;
const qreal ZOOM_FACTOR = 1.6;

void MapView::SlotZoomIn()
{
	QTransform currentTransformValue = this->transform();
	if (currentTransformValue.m11() >= ZOOM_MAX)
	{
		return;
	}
	scale(ZOOM_FACTOR, ZOOM_FACTOR);
}

void MapView::SlotZoomOut()
{
	QTransform currentTransformValue = this->transform();
	if (currentTransformValue.m11() <= ZOOM_MIN)
	{
		return;
	}
	scale(1.0 / ZOOM_FACTOR, 1.0 / ZOOM_FACTOR);
}

void MapView::SlotZoomOriginal()
{
	this->setTransform(OriginalTransformValue);
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
	//TODO: These values are fixed for the game!!!
	//TODO: Refactor!!!
	double SideLength = 48.0;
	double Width_ToBeReplaced = 2.0 * SideLength;

	return Width_ToBeReplaced + ((GameMapTileRepository::GetInstance()->GetCols() - 1) * (SideLength + GLOBAL_HEXAGON_OFFSET));
}

double MapView::CalcMapHeightInPixel() const
{
	//TODO: These values are fixed for the game!!!
	//TODO: Refactor!!!
	double SideLength = 48.0;
	double Height_ToBeReplaced = sqrt(3) * SideLength;

	return ((Height_ToBeReplaced + GLOBAL_HEXAGON_OFFSET) * GameMapTileRepository::GetInstance()->GetRows()) + (Height_ToBeReplaced / 2.0);
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

