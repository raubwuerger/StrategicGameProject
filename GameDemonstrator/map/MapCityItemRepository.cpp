#include "stdafx.h"
#include "MapCityItemRepository.h"
#include "MapCityItem.h"
#include "LogInterface.h"

MapCityItemRepository* MapCityItemRepository::Instance = nullptr;

MapCityItemRepository* MapCityItemRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new MapCityItemRepository;
	return Instance;
}

void MapCityItemRepository::Init()
{
	MapCityItems.clear();
}

QMap<int, MapCityItem*>::const_iterator MapCityItemRepository::GetFirstIterator() const
{
	return MapCityItems.cbegin();
}

QMap<int, MapCityItem*>::const_iterator MapCityItemRepository::GetLastIterator() const
{
	return MapCityItems.cend();
}

void MapCityItemRepository::SetMapCityItems(QMap<int, MapCityItem*> mapCityItems)
{
	MapCityItems = mapCityItems;
}

const MapCityItem* MapCityItemRepository::GetMapCityItemById(int MapCityItemId) const
{
	if (false == MapCityItems.contains(MapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(MapCityItemId));
		return nullptr;
	}
	return MapCityItems[MapCityItemId];
}

MapCityItem* MapCityItemRepository::GetMapCityItemByIdNonConst(int MapCityItemId) const
{
	if (false == MapCityItems.contains(MapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(MapCityItemId));
		return nullptr;
	}
	return MapCityItems[MapCityItemId];
}

void MapCityItemRepository::Release()
{
	MapCityItems.clear();
}

MapCityItemRepository::MapCityItemRepository()
{

}

MapCityItemRepository::~MapCityItemRepository()
{

}
