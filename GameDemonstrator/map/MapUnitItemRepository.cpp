#include "stdafx.h"
#include "MapUnitItemRepository.h"
#include "MapUnitItem.h"
#include "LogInterface.h"

MapUnitItemRepository* MapUnitItemRepository::Instance = nullptr;

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
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem with id %1 is not exists!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}
	return MapUnitItems.take(gameUnitItemId);
}

MapUnitItemRepository::MapUnitItemRepository()
{

}

MapUnitItemRepository::~MapUnitItemRepository()
{

}
