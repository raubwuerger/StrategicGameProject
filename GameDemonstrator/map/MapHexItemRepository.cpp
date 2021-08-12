#include "stdafx.h"
#include "MapHexItemRepository.h"
#include "MapHexItem.h"
#include "LogInterface.h"

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

void MapHexItemRepository::Init()
{
	MapHexItems.clear();
	MapHexItemsById.clear();
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
	CreateMapHexItemsById();
}

MapHexItem* MapHexItemRepository::GetMapHexItemById(int mapHexItemId)
{
	if (false == MapHexItemsById.contains(mapHexItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem with id=%1 not found!").arg(mapHexItemId));
		return nullptr;
	}
	return MapHexItemsById[mapHexItemId];
}

MapHexItemRepository::MapHexItemRepository()
{

}

MapHexItemRepository::~MapHexItemRepository()
{

}

void MapHexItemRepository::CreateMapHexItemsById()
{
	int rows = MapHexItems.size();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		QVector<MapHexItem*> currentRow = MapHexItems.at(rowIndex);
		int cols = currentRow.size();
		for (int colIndex = 0; colIndex < cols; colIndex++)
		{
			MapHexItemsById.insert(currentRow.at(colIndex)->GetGameMapItemId(), currentRow.at(colIndex));
		}
	}
}
