#include "stdafx.h"
#include "MapEventManager.h"

MapEventManager::MapEventManager(QObject *parent)
	: QObject(parent),
	HexItemInfoDialog(nullptr)
{

}

MapEventManager::~MapEventManager()
{

}

#include "MapViewHexItem.h"
void MapEventManager::InitMapItemsRegistry( int rows, int cols )
{
	QVector<MapViewHexItem*> row(cols);
	MapItems.fill(row,rows);
}

void MapEventManager::RegisterMapItem( MapViewHexItem* mapItem )
{
	MapItems[mapItem->GetRow()][mapItem->GetCol()] = mapItem;
}

const MapViewHexItem* MapEventManager::FindItemByIndex( int row, int col ) const
{
	return MapItems[row][col];
}

MapViewHexItem* MapEventManager::FindItemByIndexNonConst( int row, int col )
{
	return MapItems[row][col];
}

#include "HexItemInfoDialog.h"
void MapEventManager::UpdateMapItemInfo( int row, int col )
{
	if( row < 0 || col < 0 )
	{
		return;
	}
	if( HexItemInfoDialog == nullptr )
	{
		return;
	}

	MapViewHexItem *item = MapItems[row][col];
	HexItemInfoDialog->ui.lineEditCol->setText( QString::number(item->GetCol()) );
	HexItemInfoDialog->ui.lineEditRow->setText( QString::number(item->GetRow()) );
}
