#include "stdafx.h"
#include "MapUnitItemFactory.h"
#include "MapUnitItem.h"
#include "LogInterface.h"
#include "game\GameUnitRepository.h"
#include "game\GameUnit.h"
#include "MapUnitItemRepository.h"
#include "MapHexItemRepository.h"
#include "MapHexItem.h"
#include "MapView.h"
#include "model\ModelUnitType.h"
#include "game\GameOwner.h"

MapUnitItemFactory::MapUnitItemFactory()
	: DefaultBorderWidth(2),
	DefaultBorderWidthSelected(4)

{
}

MapUnitItemFactory::~MapUnitItemFactory()
{
}

bool MapUnitItemFactory::Create( MapView* mapView )
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	MapUnitItemRepository::GetInstance()->Init();
	
	QMap<int, GameUnit*>::const_iterator gameUnit = GameUnitRepository::GetInstance()->GetFirstIterator();
	while (gameUnit != GameUnitRepository::GetInstance()->GetLastIterator())
	{
		GameUnit *gameItemUnit = gameUnit.value();
		int mapItemId = gameItemUnit->GetGameTileId();
		const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetById(mapItemId);
		if (nullptr == mapHexItem)
		{
			return false;
		}
		const QPointF topLeftPoint = mapHexItem->GetTopLeftPoint();
		MapUnitItem *newMapUnitItem = new MapUnitItem(AdjustTopLeftPosition(topLeftPoint));
		newMapUnitItem->BorderWidth = DefaultBorderWidth;
		newMapUnitItem->BorderWidthSelected = DefaultBorderWidthSelected;
		newMapUnitItem->SetGameUnitId(gameItemUnit->GetId());
		newMapUnitItem->SetMapHexItemId(mapHexItem->GetId());
		newMapUnitItem->SetUnitItemImage(GetImage(gameItemUnit));
		newMapUnitItem->Color = gameItemUnit->GetGameOwner()->GetColor();
		if (false == MapUnitItemRepository::GetInstance()->Register(newMapUnitItem))
		{
			return false;
		}
		mapView->AddedMapUnit(newMapUnitItem);
		gameUnit++;
	}
	return true;
}

bool MapUnitItemFactory::Create(MapView* mapView, const GameUnit* gameItemUnit)
{
	if (nullptr == mapView)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <mapView> must not be null!"));
		return false;
	}

	if (nullptr == gameItemUnit)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover parameter <gameUnitType> must not be null!"));
		return false;
	}

	int mapItemId = gameItemUnit->GetGameTileId();
	const MapHexItem* mapHexItem = MapHexItemRepository::GetInstance()->GetById(mapItemId);
	if (nullptr == mapHexItem)
	{
		return false;
	}
	const QPointF topLeftPoint = mapHexItem->GetTopLeftPoint();
	MapUnitItem *newMapUnitItem = new MapUnitItem(AdjustTopLeftPosition(topLeftPoint));
	newMapUnitItem->BorderWidth = DefaultBorderWidth;
	newMapUnitItem->BorderWidthSelected = DefaultBorderWidthSelected;
	newMapUnitItem->SetGameUnitId(gameItemUnit->GetId());
	newMapUnitItem->SetMapHexItemId(mapHexItem->GetId());
	newMapUnitItem->SetUnitItemImage(GetImage(gameItemUnit));
	newMapUnitItem->Color = gameItemUnit->GetGameOwner()->GetColor();
	if (false == MapUnitItemRepository::GetInstance()->Register(newMapUnitItem))
	{
		return false;
	}

	return mapView->AddedMapUnit(newMapUnitItem);
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

const QImage* MapUnitItemFactory::GetImage(const GameUnit* gameUnitItem)
{
	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	if (nullptr == modelUnitType)
	{
		Q_ASSERT(nullptr);
		return nullptr;
	}
	return modelUnitType->GetImage();
}
