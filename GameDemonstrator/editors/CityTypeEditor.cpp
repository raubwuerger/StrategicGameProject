#include "stdafx.h"
#include "CityTypeEditor.h"
#include "model\ModelCityTypeRepository.h"
#include "model\ModelCityType.h"
#include "controller\EditorController.h"
#include "game\GameCityFactory.h"
#include "map\MapCityItemFactory.h"
#include "controller\TerrainAccessTester.h"
#include "game\GameCityRepository.h"
#include "game\GameCity.h"
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

	if ( true == GameCityRepository::GetInstance()->IsCityOnGameMapItemId(mapItemId))
	{
		return;
	}

	GameCityParameterObject obj;
	obj.GameMapItemId = mapItemId;
	obj.ModelCityTypeObject = ActiveModelCityType;
	obj.GameOwnerItemId = OwnerTypeId;

	GameCityFactory gameFactory;
	GameCity* created = gameFactory.Create(obj);
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

#include "game/GameCityRepository.h"
#include "game/GameCity.h"
#include "map/MapCityItemRepository.h"
#include "map/MapView.h"
void CityTypeEditor::SlotDeleteCity(int mapItemId)
{
	if (false == BaseEditor::GetActive())
	{
		return;
	}

	GameCity* gameCityItem = GameCityRepository::GetInstance()->RemoveCityItemByGameMapItemId(mapItemId);
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
#include "game/GameMapTileRepository.h"
#include "game/GameMapTile.h"
int CityTypeEditor::GetModelTerrainType(int mapId)
{
	GameMapTile* gameMapItem = GameMapTileRepository::GetInstance()->GetGameMapItemById(mapId);
	if (nullptr == gameMapItem)
	{
		return NOT_INITIALIZED_INT;
	}
	return gameMapItem->GetModelTerrainTypeId();
}
