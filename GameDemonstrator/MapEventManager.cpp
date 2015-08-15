#include "stdafx.h"
#include "MapEventManager.h"

MapEventManager::MapEventManager(QObject *parent)
	: QObject(parent),
	m_HexItemInfoDialog(nullptr)
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

#include "HexItemInfoDialog.h"
void MapEventManager::UpdateMapItemInfo( int row, int col )
{
	if( row < 0 || col < 0 )
	{
		return;
	}
	if( m_HexItemInfoDialog == nullptr )
	{
		return;
	}

	MapViewHexItem *item = MapItems[row][col];
	m_HexItemInfoDialog->ui.lineEditCol->setText( QString::number(item->GetCol()) );
	m_HexItemInfoDialog->ui.lineEditRow->setText( QString::number(item->GetRow()) );
}