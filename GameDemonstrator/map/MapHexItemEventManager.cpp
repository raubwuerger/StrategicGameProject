#include "stdafx.h"
#include "MapHexItemEventManager.h"
#include "game\GameMapItemRepository.h"
#include "map\MapHexItem.h"
#include "model\ModelTerrainType.h"
#include "game\GameUnitItemRepository.h"
#include "game\GameUnitItem.h"
#include "MapHexItemRepository.h"

MapHexItemEventManager::MapHexItemEventManager(QObject *parent)
	: QObject(parent),
	HexItemInfoDialog(nullptr),
	UnitTypeInfoDialog(nullptr),
	CityTypeInfoDialog(nullptr),
	DEFAULT_ENTRY("---")
{

}

MapHexItemEventManager::~MapHexItemEventManager()
{

}

MapHexItem* MapHexItemEventManager::FindMapHexItem(int gameMapItemId) const
{
	return MapHexItemRepository::GetInstance()->GetMapHexItemByIdNonConst(gameMapItemId);
}

#include "dialogs/HexItemInfoDialog.h"
#include "game/GameMapItem.h"
void MapHexItemEventManager::SlotUpdateMapItemInfo(int gameMapItemId)
{
	if (HexItemInfoDialog == nullptr)
	{
		return;
	}

	QString mapHexItemRow(DEFAULT_ENTRY);
	QString mapHexItemCol(DEFAULT_ENTRY);
	QString mapHexItemId(DEFAULT_ENTRY);
	QString mapHexItemTerrainName(DEFAULT_ENTRY);

	const GameMapItem* modelMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(gameMapItemId);
	if (nullptr != modelMapItem)
	{
		mapHexItemId = QString::number(modelMapItem->GetId());
		mapHexItemRow = QString::number(modelMapItem->GetRow());
		mapHexItemCol = QString::number(modelMapItem->GetCol());
		mapHexItemTerrainName = modelMapItem->GetTerrainType()->GetName();
	}

	HexItemInfoDialog->SetId(mapHexItemId);
	HexItemInfoDialog->SetRow(mapHexItemRow);
	HexItemInfoDialog->SetCol(mapHexItemCol);
	HexItemInfoDialog->SetTerrainName(mapHexItemTerrainName);
}

#include "dialogs/UnitTypeInfoDialog.h"
#include "model/ModelUnitType.h"
#include "model/ModelOwnerType.h"
void MapHexItemEventManager::SlotUpdateMapUnitItemInfo(int mapUnitItemId)
{
	if (nullptr == UnitTypeInfoDialog)
	{
		return;
	}

	QString mapUnitItem(QString::number(mapUnitItemId));
	QString mapUnitItemName(DEFAULT_ENTRY);
	QString mapUnitItemType(DEFAULT_ENTRY);
	QString mapHexItemId(DEFAULT_ENTRY);
	QString mapUnitItemOwnerName(DEFAULT_ENTRY);

	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(mapUnitItemId);
	if (nullptr != gameUnitItem)
	{
		mapUnitItemName = gameUnitItem->GetName();
		mapUnitItemType = gameUnitItem->GetModelUnitType()->GetName();
		mapHexItemId = QString::number(gameUnitItem->GetGameMapItemId());
		mapUnitItemOwnerName = gameUnitItem->GetModelOwnerType()->GetName();
	}

	UnitTypeInfoDialog->SetId(mapUnitItem);
	UnitTypeInfoDialog->SetName(mapUnitItemName);
	UnitTypeInfoDialog->SetType(mapUnitItemType);
	UnitTypeInfoDialog->SetMapItemId(mapHexItemId);
	UnitTypeInfoDialog->SetOwnerName(mapUnitItemOwnerName);
}

#include "dialogs/CityTypeInfoDialog.h"
#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
void MapHexItemEventManager::SlotUpdateMapCityItemInfo(int mapCityItemId)
{
	if (nullptr == CityTypeInfoDialog)
	{
		return;
	}

	QString cityItemId(QString::number(mapCityItemId));
	QString cityItemName(DEFAULT_ENTRY);
	QString cityItemTypeId(DEFAULT_ENTRY);
	QString mapHexItemId(DEFAULT_ENTRY);
	QString cityOwner(DEFAULT_ENTRY);

	const GameCityItem* item = GameCityItemRepository::GetInstance()->GetGameCityItemById(mapCityItemId);
	if (nullptr != item)
	{
		cityItemName = item->GetName();
		cityItemTypeId = QString::number(item->GetCityTypeId());
		mapHexItemId = QString::number(item->GetGameMapItemId());
		cityOwner = item->GetModelOwnerType()->GetName();
	}

	CityTypeInfoDialog->SetId(cityItemId);
	CityTypeInfoDialog->SetName(cityItemName);
	CityTypeInfoDialog->SetType(cityItemTypeId);
	CityTypeInfoDialog->SetMapItemId(mapHexItemId);
	CityTypeInfoDialog->SetOwnerName(cityOwner);
}
