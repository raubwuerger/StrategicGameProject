#include "stdafx.h"
#include "CityTypeEditor.h"
#include "model\ModelCityTypeRepository.h"
#include "model\ModelCityType.h"
#include "controller\EditorController.h"
#include "game\GameCityItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "controller\TerrainAccessTester.h"
#include "game\GameCityItemRepository.h"
#include "game\GameCityItem.h"
#include "game\GameUnitProductionController.h"

CityTypeEditor::CityTypeEditor(QObject *parent)
	: BaseEditor(parent),
	EditorControllerInstance(nullptr),
	ActiveModelCityType(nullptr),
	OwnerTypeId(1)
{

}

void CityTypeEditor::SlotDeactivated()
{
	return; //TODO: Do nothing at the moment
}

void CityTypeEditor::SlotActivated()
{
	if (nullptr == EditorControllerInstance)
	{
		return;
	}
	EditorControllerInstance->Activate(this);
}

void CityTypeEditor::SlotActiveCityTypeId(int CityTypeId)
{
	ActiveModelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(CityTypeId);
}

void CityTypeEditor::SlotActiveOwnerTypeId(int ownerTypeId)
{
	OwnerTypeId = ownerTypeId;
}

void CityTypeEditor::SlotAddCity(int mapItemId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	if (false == ActiveModelCityType->IsPlaceableOnTerrainType(GetModelTerrainType(mapItemId)))
	{
		return;
	}

	if ( true == GameCityItemRepository::GetInstance()->IsCityOnGameMapItemId(mapItemId))
	{
		return;
	}

	GameCityParameterObject obj;
	obj.GameMapItemId = mapItemId;
	obj.ModelCityTypeObject = ActiveModelCityType;
	obj.GameOwnerItemId = OwnerTypeId;

	GameCityItemFactory gameFactory;
	GameCityItem* created = gameFactory.Create(obj);
	if (nullptr == created)
	{
		return;
	}

	const GameUnitProduction* gameUnitProduction = GameUnitProductionController::GetInstance()->CreateDefaultGameUnitProduction(created->GetId());
	if (nullptr == gameUnitProduction)
	{
		Q_ASSERT(false);
		return;
	}

	created->SetGameUnitProduction(gameUnitProduction);

	MapCityItemFactory mapFactory;
	mapFactory.Create(MapViewInstance, created);
}

#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
#include "map/MapCityItemRepository.h"
#include "map/MapView.h"
void CityTypeEditor::SlotDeleteCity(int mapItemId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	GameCityItem* gameCityItem = GameCityItemRepository::GetInstance()->RemoveCityItemByGameMapItemId(mapItemId);
	if (nullptr == gameCityItem)
	{
		return;
	}

	MapCityItem*  mapCityItem = MapCityItemRepository::GetInstance()->RemoveById(gameCityItem->GetId());
	if (nullptr == mapCityItem)
	{
		return;
	}

	MapViewInstance->RemoveCity(mapCityItem);
	delete gameCityItem;
	delete mapCityItem;
}

#include "model/ModelTerrainType.h"
#include "game/GameMapItemRepository.h"
#include "game/GameMapItem.h"
int CityTypeEditor::GetModelTerrainType(int mapId)
{
	GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapId);
	if (nullptr == gameMapItem)
	{
		return NOT_INITIALIZED_INT;
	}
	return gameMapItem->GetModelTerrainTypeId();
}
