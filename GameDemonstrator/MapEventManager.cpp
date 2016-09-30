#include "stdafx.h"
#include "MapEventManager.h"

CMapEventManager::CMapEventManager(QObject *parent)
	: QObject(parent),
	HexItemInfoDialog(nullptr)
{

}

CMapEventManager::~CMapEventManager()
{

}

#include "MapViewHexItem.h"
void CMapEventManager::InitMapItemsRegistry( int rows, int cols )
{
	QVector<MapViewHexItem*> row(cols);
	MapItems.fill(row,rows);
}

void CMapEventManager::RegisterMapItem( MapViewHexItem* mapItem )
{
	MapItems[mapItem->GetRow()][mapItem->GetCol()] = mapItem;
}

const MapViewHexItem* CMapEventManager::FindItemByIndex( int row, int col ) const
{
	return MapItems[row][col];
}

MapViewHexItem* CMapEventManager::FindItemByIndexNonConst( int row, int col )
{
	return MapItems[row][col];
}

#include "HexItemInfoDialog.h"
void CMapEventManager::UpdateMapItemInfo( int row, int col )
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
