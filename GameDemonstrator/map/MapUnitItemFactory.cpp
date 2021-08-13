#include "stdafx.h"
#include "MapUnitItemFactory.h"
#include "MapUnitItem.h"
#include "LogInterface.h"
#include "game\GameUnitItemRepository.h"
#include "game\GameUnitItem.h"
#include "MapUnitItemRepository.h"
#include "MapHexItemRepository.h"
#include "MapHexItem.h"
#include "MapView.h"
#include "model\ModelUnitType.h"

MapUnitItemFactory::MapUnitItemFactory()
{
}

MapUnitItemFactory::~MapUnitItemFactory()
{
}

bool MapUnitItemFactory::CreateUnit( MapView* mapView )
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	MapUnitItemRepository::GetInstance()->Init();
	
	QMap<int, GameUnitItem*>::const_iterator gameUnit = GameUnitItemRepository::GetInstance()->GetFirstIterator();
	while (gameUnit != GameUnitItemRepository::GetInstance()->GetLastIterator())
	{
		GameUnitItem *gameItemUnit = gameUnit.value();
		int mapItemId = gameItemUnit->GetGameMapItemId();
		MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetMapHexItemById(mapItemId);
		if (nullptr == mapHexItem)
		{
			return false;
		}
		const QPointF topLeftPoint = mapHexItem->GetTopLeftPoint();
		MapUnitItem *newMapUnitItem = new MapUnitItem(AdjustTopLeftPosition(topLeftPoint));
		newMapUnitItem->SetGameUnitId(gameItemUnit->GetId());
		newMapUnitItem->SetMapHexItemId(mapHexItem->GetGameMapItemId());
		newMapUnitItem->SetUnitItemImage(GetImage(gameItemUnit));
		if (false == MapUnitItemRepository::GetInstance()->Register(newMapUnitItem))
		{
			return false;
		}
		mapView->AddedMapUnit(newMapUnitItem);
		gameUnit++;
	}
	return true;
}

bool MapUnitItemFactory::CreateUnit(MapView* mapView, const GameUnitItem* gameUnitType)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	if (nullptr == gameUnitType)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <gameUnitType> must not be null!"));
		return false;
	}


/*	MapUnitItem *newMapUnitItem = new MapUnitItem(AdjustTopLeftPosition(topLeftPoint));
	newMapUnitItem->SetGameUnitId(gameItemUnit->GetId());
	newMapUnitItem->SetMapHexItemId(mapHexItem->GetGameMapItemId());
	newMapUnitItem->SetUnitItemImage(GetImage(gameItemUnit));
	if (false == MapUnitItemRepository::GetInstance()->Register(newMapUnitItem))
	{
		return false;
	}
	mapView->AddedMapUnit(newMapUnitItem);
	*/
	return true;
}

bool MapUnitItemFactory::DeleteUnit(MapView* mapView, int unitItemId)
{
	return false;
}

const QPointF MapUnitItemFactory::AdjustTopLeftPosition(const QPointF& topLeftPosition)
{
	QPointF adjustedPosition(topLeftPosition);
	return adjustedPosition -= QPointF(-16.0, -20.0); //TODO: http://wanderfalke/redmine/issues/4
}

const QImage* MapUnitItemFactory::GetImage(const GameUnitItem* gameUnitItem)
{
	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	if (nullptr == modelUnitType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelUnitType->GetImage();
}
