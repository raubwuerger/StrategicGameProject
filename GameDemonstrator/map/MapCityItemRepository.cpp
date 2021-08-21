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
	MapCityItemsById.clear();
}

QVector< QVector<MapCityItem*>>::const_iterator MapCityItemRepository::GetFirstIterator() const
{
	return MapCityItems.cbegin();
}

QVector< QVector<MapCityItem*>>::const_iterator MapCityItemRepository::GetLastIterator() const
{
	return MapCityItems.cend();
}

void MapCityItemRepository::SetMapCityItems(QVector< QVector<MapCityItem*> > MapCityItems)
{
	MapCityItems = MapCityItems;
	CreateMapCityItemsById();
}

const MapCityItem* MapCityItemRepository::GetMapCityItemById(int MapCityItemId) const
{
	if (false == MapCityItemsById.contains(MapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(MapCityItemId));
		return nullptr;
	}
	return MapCityItemsById[MapCityItemId];
}

MapCityItem* MapCityItemRepository::GetMapCityItemByIdNonConst(int MapCityItemId) const
{
	if (false == MapCityItemsById.contains(MapCityItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapCityItem with id=%1 not found!").arg(MapCityItemId));
		return nullptr;
	}
	return MapCityItemsById[MapCityItemId];
}

MapCityItemRepository::MapCityItemRepository()
{

}

MapCityItemRepository::~MapCityItemRepository()
{

}

void MapCityItemRepository::CreateMapCityItemsById()
{
	int rows = MapCityItems.size();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		QVector<MapCityItem*> currentRow = MapCityItems.at(rowIndex);
		int cols = currentRow.size();
		for (int colIndex = 0; colIndex < cols; colIndex++)
		{
			MapCityItemsById.insert(currentRow.at(colIndex)->GetGameMapItemId(), currentRow.at(colIndex));
		}
	}
}
