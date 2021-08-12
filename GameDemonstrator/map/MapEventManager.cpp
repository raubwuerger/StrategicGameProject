#include "stdafx.h"
#include "MapEventManager.h"
#include "game\GameMapRepository.h"
#include "map\MapHexItem.h"
#include "model\ModelTerrainType.h"
#include "game\GameUnitItemRepository.h"
#include "game\GameUnitItem.h"

MapEventManager::MapEventManager(QObject *parent)
	: QObject(parent),
	HexItemInfoDialog(nullptr),
	DEFAULT_ENTRY("---")
{

}

MapEventManager::~MapEventManager()
{

}

void MapEventManager::InitGameMapRegistry()
{
	QVector<MapHexItem*> row(GameMapRepository::GetInstance()->GetCols());
	MapItems.fill(row, GameMapRepository::GetInstance()->GetRows());
}

void MapEventManager::RegisterMapHexItem( MapHexItem* mapItem )
{
	MapItems[mapItem->GetRow()][mapItem->GetCol()] = mapItem;
}

void MapEventManager::RegisterMapUnitItem( MapUnitItem* unitItem )
{
	//TODO: Sollte eine Map (ID) sein. Es wird sicherlich mehr als ein Item von jedem Type geben!!!
	if (true == UnitItems.contains(unitItem))
	{
		//TODO: Fehlermeldung ausgeben
		return;
	}
	UnitItems.push_back(unitItem);
}

const MapHexItem* MapEventManager::FindMapHexItemByIndex( int row, int col ) const
{
	return MapItems[row][col];
}

MapHexItem* MapEventManager::FindIMapHextemByIndexNonConst( int row, int col )
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

	QString mapHexItemRow(QString::number(row));
	QString mapHexItemCol(QString::number(col));
	QString mapHexItemId(DEFAULT_ENTRY);
	QString mapHexItemTerrainName(DEFAULT_ENTRY);

	const GameMapItem* modelMapItem = GameMapRepository::GetInstance()->GetGameMapItem(row,col);
	if (nullptr != modelMapItem)
	{
		mapHexItemId = QString::number(modelMapItem->GetId());
		mapHexItemTerrainName = modelMapItem->GetTerrainType()->GetName();
	}
	HexItemInfoDialog->SetId(mapHexItemId);
	HexItemInfoDialog->SetRow(mapHexItemRow);
	HexItemInfoDialog->SetCol(mapHexItemCol);
	HexItemInfoDialog->SetTerrainName(mapHexItemTerrainName);
}

#include "dialogs/UnitTypeInfoDialog.h"
#include "model/ModelUnitType.h"
void MapEventManager::SlotUpdateMapUnitItemInfo(int mapUnitItemId)
{
	if (nullptr == UnitTypeInfoDialog)
	{
		return;
	}

	QString mapUnitItem(QString::number(mapUnitItemId));
	QString mapUnitItemName(DEFAULT_ENTRY);
	QString mapUnitItemType(DEFAULT_ENTRY);

	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItemId);
	if (nullptr != gameUnitItem)
	{
		mapUnitItemName = gameUnitItem->GetModelUnitType()->GetName();
		mapUnitItemType = gameUnitItem->GetModelUnitType()->GetName();
	}

	UnitTypeInfoDialog->SetId(mapUnitItem);
	UnitTypeInfoDialog->SetName(mapUnitItemName);
	UnitTypeInfoDialog->SetType(mapUnitItemType);
}
