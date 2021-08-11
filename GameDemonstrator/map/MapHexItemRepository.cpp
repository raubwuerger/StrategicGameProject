#include "stdafx.h"
#include "MapHexItemRepository.h"

MapHexItemRepository* MapHexItemRepository::Instance = nullptr;

MapHexItemRepository* MapHexItemRepository::GetInstance()
{
	if (nullptr != Instance)
	{
		return Instance;
	}

	Instance = new MapHexItemRepository;
	return Instance;
}

bool MapHexItemRepository::RegisterMapHexItem(MapHexItem* mapHexItem)
{
	return false;
}

QVector< QVector<MapHexItem*>>::const_iterator MapHexItemRepository::GetFirstIterator() const
{
	return MapHexItems.cbegin();
}

QVector< QVector<MapHexItem*>>::const_iterator MapHexItemRepository::GetLastIterator() const
{
	return MapHexItems.cend();
}

void MapHexItemRepository::SetMapHexItems(QVector< QVector<MapHexItem*> > mapHexItems)
{
	MapHexItems = mapHexItems;
}

MapHexItem* MapHexItemRepository::GetMapHexItemById(int mapHexItemId)
{
	return nullptr;
}

MapHexItemRepository::MapHexItemRepository()
{

}

MapHexItemRepository::~MapHexItemRepository()
{

}
