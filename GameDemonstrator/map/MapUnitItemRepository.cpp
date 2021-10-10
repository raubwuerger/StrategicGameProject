#include "stdafx.h"
#include "MapUnitItemRepository.h"
#include "MapUnitItem.h"
#include "LogInterface.h"
#include "MapView.h"

MapUnitItemRepository*	MapUnitItemRepository::Instance = nullptr;
MapView*				MapUnitItemRepository::MapViewInstance = nullptr;

MapUnitItemRepository* MapUnitItemRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new MapUnitItemRepository;
	return Instance;
}

bool MapUnitItemRepository::Init()
{
	MapUnitItems.clear();
	return true;
}

bool MapUnitItemRepository::Register(MapUnitItem* mapUnitItem)
{
	if (nullptr == mapUnitItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem must not be null!"));
		return false;
	}

	int gameUnitId = mapUnitItem->GetGameUnitId();

	if (true == MapUnitItems.contains(gameUnitId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 already exists!").arg(QString::number(gameUnitId)));
		return false;
	}
	MapUnitItems.insert(gameUnitId, mapUnitItem);
	return true;
}

MapUnitItem* MapUnitItemRepository::Remove(int gameUnitItemId)
{
	if (false == MapUnitItems.contains(gameUnitItemId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 does not exist!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}

	MapUnitItem* deleted = MapUnitItems.take(gameUnitItemId);

	Q_ASSERT(MapViewInstance);
	MapViewInstance->RemoveMapUnit(deleted);
	return deleted;
}

MapUnitItem* MapUnitItemRepository::RemoveFromMap(int gameUnitItemId)
{
	if (false == MapUnitItems.contains(gameUnitItemId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 does not exist!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}

	MapUnitItem* removed = MapUnitItems[gameUnitItemId];

	Q_ASSERT(MapViewInstance);
	MapViewInstance->RemoveMapUnit(removed);
	return removed;
}

MapUnitItem* MapUnitItemRepository::Hide(int gameUnitItemId)
{
	if (false == MapUnitItems.contains(gameUnitItemId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 does not exist!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}

	MapUnitItem* mapUnit = MapUnitItems[gameUnitItemId];

	Q_ASSERT(MapViewInstance);
	mapUnit->hide();
	return mapUnit;
}

MapUnitItem* MapUnitItemRepository::Show(int gameUnitItemId)
{
	if (false == MapUnitItems.contains(gameUnitItemId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 does not exist!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}

	MapUnitItem* mapUnit = MapUnitItems[gameUnitItemId];

	Q_ASSERT(MapViewInstance);
	mapUnit->show();
	return mapUnit;
}

bool MapUnitItemRepository::AddToMap(int gameUnitId)
{
	if (false == MapUnitItems.contains(gameUnitId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 does not exist!").arg(QString::number(gameUnitId)));
		return nullptr;
	}

	MapUnitItem* show = MapUnitItems[gameUnitId];

	Q_ASSERT(MapViewInstance);
	return MapViewInstance->AddedMapUnit(show);
}

void MapUnitItemRepository::Release()
{
	MapUnitItems.clear();
}

MapUnitItem* MapUnitItemRepository::GetById(int id)
{
	if (false == MapUnitItems.contains(id))
	{
		return nullptr;
	}
	return MapUnitItems[id];
}

MapUnitItemRepository::MapUnitItemRepository()
{

}

MapUnitItemRepository::~MapUnitItemRepository()
{

}
