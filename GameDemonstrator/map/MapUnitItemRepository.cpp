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
		jha::GetLog()->Log_DEBUG(QObject::tr("MapUnitItem musst not be null!"));
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

MapUnitItemRepository::MapUnitItemRepository()
{

}

MapUnitItemRepository::~MapUnitItemRepository()
{

}
