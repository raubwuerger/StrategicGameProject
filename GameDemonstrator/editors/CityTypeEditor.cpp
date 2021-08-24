#include "stdafx.h"
#include "CityTypeEditor.h"
#include "model\ModelCityTypeRepository.h"
#include "model\ModelCityType.h"
#include "controller\EditorController.h"
#include "game\GameCityItemFactory.h"
#include "map\MapCityItemFactory.h"

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

	GameCityParameterObject obj;
	obj.GameMapItemId = mapItemId;
	obj.ModelCityTypeObject = ActiveModelCityType;
	obj.ModelOwnerTypeId = OwnerTypeId;
	GameCityItemFactory gameFactory;
	GameCityItem* created = gameFactory.Create(obj);
	if (nullptr == created)
	{
		return;
	}

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
}
