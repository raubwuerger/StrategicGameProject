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

bool MapHexItemRepository::Init()
{
	MapHexItems.clear();
	MapHexItemsById.clear();
	return true;
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

const MapHexItem* MapHexItemRepository::GetById(int mapHexItemId) const
{
	if (false == MapHexItemsById.contains(mapHexItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem with id=%1 not found!").arg(mapHexItemId));
		return nullptr;
	}
	return MapHexItemsById[mapHexItemId];
}

MapHexItem* MapHexItemRepository::GetByIdNonConst(int mapHexItemId) const
{
	if (false == MapHexItemsById.contains(mapHexItemId))
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem with id=%1 not found!").arg(mapHexItemId));
		return nullptr;
	}
	return MapHexItemsById[mapHexItemId];
}

MapHexItem* MapHexItemRepository::GetMapHexItemByRowCol(int row, int col)
{
	if (row < 0 || col < 0)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem out of bounds row=%1 and col=%2").arg(QString::number(row)).arg(QString::number(col)));
		return nullptr;
	}

	int rowCount = MapHexItems.count();
	if (row >= rowCount)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem with row=%1 and col=%2 not found! Max rows: %3").arg(QString::number(row)).arg(QString::number(col)).arg(QString::number(rowCount)));
		return nullptr;
	}

	QVector<MapHexItem*> concreteRow = MapHexItems.at(row);
	int colCount = concreteRow.count();
	if (col >= colCount)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("MapHexItem with row=%1 and col=%2 not found! Max cols: %3").arg(QString::number(row)).arg(QString::number(col)).arg(QString::number(colCount)));
		return nullptr;
	}

	return concreteRow.at(col);
}

void MapHexItemRepository::Release()
{
	MapHexItems.clear();
	MapHexItemsById.clear();
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
			MapHexItemsById.insert(currentRow.at(colIndex)->GetId(), currentRow.at(colIndex));
		}
	}
}
