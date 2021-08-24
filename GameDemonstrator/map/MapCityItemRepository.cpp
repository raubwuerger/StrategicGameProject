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

bool MapCityItemRepository::Register(MapCityItem* mapCityItem)
{
	if (true == MapCityItems.contains(mapCityItem->GetId()))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 already exists!").arg(QString::number(mapCityItem->GetId())));
		return false;
	}
	MapCityItems.insert(mapCityItem->GetId(), mapCityItem);
	return true;
}

void MapCityItemRepository::SetMapCityItems(QMap<int, MapCityItem*> mapCityItems)
{
	MapCityItems = mapCityItems;
}

const MapCityItem* MapCityItemRepository::GetMapCityItemById(int mapCityItemId) const
{
	if (false == MapCityItems.contains(mapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(QString::number(mapCityItemId)));
		return nullptr;
	}
	return MapCityItems[mapCityItemId];
}

MapCityItem* MapCityItemRepository::GetMapCityItemByIdNonConst(int mapCityItemId) const
{
	if (false == MapCityItems.contains(mapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(QString::number(mapCityItemId)));
		return nullptr;
	}
	return MapCityItems[mapCityItemId];
}

MapCityItem* MapCityItemRepository::RemoveById(int mapCityItemId)
{
	if (false == MapCityItems.contains(mapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(QString::number(mapCityItemId)));
		return nullptr;
	}

	return MapCityItems.take(mapCityItemId);
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
