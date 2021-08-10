#include "stdafx.h"
#include "MapEventManager.h"
#include "game\GameMapRepository.h"
#include "model\ModelTerrainType.h"

MapEventManager::MapEventManager(QObject *parent)
	: QObject(parent),
	HexItemInfoDialog(nullptr)
{

}

MapEventManager::~MapEventManager()
{

}

#include "map\MapHexItem.h"
void MapEventManager::InitMapItemsRegistry( int rows, int cols )
{
	QVector<MapHexItem*> row(cols);
	MapItems.fill(row,rows);
}

void MapEventManager::RegisterMapItem( MapHexItem* mapItem )
{
	MapItems[mapItem->GetRow()][mapItem->GetCol()] = mapItem;
}

void MapEventManager::RegisterUnitItem( MapUnitItem* unitItem )
{
	//TODO: Sollte eine Map (ID) sein. Es wird sicherlich mehr als ein Item von jedem Type geben!!!
	if (true == UnitItems.contains(unitItem))
	{
		//TODO: Fehlermeldung ausgeben
		return;
	}
	UnitItems.push_back(unitItem);
}

const MapHexItem* MapEventManager::FindItemByIndex( int row, int col ) const
{
	return MapItems[row][col];
}

MapHexItem* MapEventManager::FindItemByIndexNonConst( int row, int col )
{
	return MapItems[row][col];
}

#include "dialogs/HexItemInfoDialog.h"
void MapEventManager::SlotUpdateMapItemInfo( int row, int col )
{
	if( row < 0 || col < 0 )
	{
		return;
	}
	
	if( HexItemInfoDialog == nullptr )
	{
		return;
	}

	const GameMapItem* modelMapItem = GameMapRepository::GetInstance()->GetModelMapItem(row,col);
	HexItemInfoDialog->SetMapHexItemId( QString::number(modelMapItem->GetId()) );
	HexItemInfoDialog->SetMapHexItemRow(QString::number(row));
	HexItemInfoDialog->SetMapHexItemCol(QString::number(col));
	HexItemInfoDialog->SetMapHexItemTerrainId( modelMapItem->GetTerrainType()->GetName() );
}
