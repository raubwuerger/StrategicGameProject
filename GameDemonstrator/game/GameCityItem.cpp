#include "stdafx.h"
#include "GameCityItem.h"
#include "GameCityItemRuntimeData.h"
#include "Model\ModelCityType.h"
#include "GameUnitProduction.h"

GameCityItem::GameCityItem(int id)
	:	Id(id),
		OwnerItem(nullptr),
		MapItem(nullptr),
		OwnerItemId(-1),
		MapItemId(-1),
		SpezializedUnitTypeId(-1),
		RuntimeData(nullptr),
		UnitProduction(nullptr)
{
	UnitProduction = new GameUnitProduction(Id);
}

GameCityItem::~GameCityItem()
{
	delete UnitProduction;
}

const int GameCityItem::GetId() const
{
	return Id;
}

const QString& GameCityItem::GetName() const
{
	return Name;
}

void GameCityItem::SetName(const QString& name)
{
	Name = name;
}

const GameOwnerItem* GameCityItem::GetGameOwnerItem() const
{
	return OwnerItem;
}

void GameCityItem::SetGameOwnerItem(const GameOwnerItem* gameOwnerItem)
{
	OwnerItem = gameOwnerItem;
}

void GameCityItem::SetGameOwnerItemId(int gameOwnerItemId)
{
	OwnerItemId = gameOwnerItemId;
}

const GameMapItem* GameCityItem::GetGameMapItem() const
{
	return MapItem;
}

int GameCityItem::GetGameOwnerItemId() const
{
	return OwnerItemId;
}

int GameCityItem::GetGameMapItemId() const
{
	return MapItemId;
}

const ModelCityType* GameCityItem::GetCityModelType() const
{
	return CityType;
}

int GameCityItem::GetModelCityTypeId() const
{
	return CityTypeId;
}

void GameCityItem::UpdateTurn() const
{
	ResetDefenceValue();
	UpdateUnitProduction();
	//TODO: Increase build unit step
	//TODO: ...
}

int GameCityItem::GetSpezializedUnitTypeId() const
{
	return SpezializedUnitTypeId;
}

bool GameCityItem::Move() const
{
	return false; // Nothing to do
}

void GameCityItem::Attacks() const
{
	return; // Nothing to do
}

void GameCityItem::Defends() const
{
	return; // 
}

int GameCityItem::GetBaseStrength() const
{
	return RuntimeData->BaseStrength;
}

int GameCityItem::GetCurrentStrength() const
{
	return RuntimeData->CurrentStrength;
}

int GameCityItem::GetBaseEfficiency() const
{
	return RuntimeData->BaseEfficiency;
}

int GameCityItem::GetCurrentEfficiency() const
{
	return RuntimeData->CurrentEfficiency;
}

bool GameCityItem::InitRuntimeData()
{
	RuntimeData = new GameCityItemRuntimeData();
	RuntimeData->BaseEfficiency = CityType->GetEfficiency();
	RuntimeData->CurrentEfficiency = CityType->GetEfficiency();
	RuntimeData->BaseStrength = CityType->GetDefenceValue();
	RuntimeData->CurrentStrength = CityType->GetDefenceValue();
	return true;
}

GameCityItemRuntimeData* GameCityItem::GetRuntimeData()
{
	return RuntimeData;
}

void GameCityItem::ResetDefenceValue() const
{
	RuntimeData->CurrentStrength = RuntimeData->BaseStrength;
}

void GameCityItem::UpdateUnitProduction(const GameUnitProduction& unitProduction)
{
	UnitProduction->SetGameUnitId(unitProduction.GetGameUnitId());
}

void GameCityItem::UpdateUnitProduction() const
{
	int productionProgress = CityType->GetBaseProductionPoints();
	if (UnitProduction->GetGameUnitId() == this->SpezializedUnitTypeId)
	{
		productionProgress += CityType->GetBaseProductionPoints();
	}
	UnitProduction->UpdateProductionProgress(productionProgress);
}

const GameUnitProduction* GameCityItem::GetUnitProduction() const
{
	return UnitProduction;
}

void GameCityItem::SetGameUnitProduction(const GameUnitProduction& unitProduction)
{
	UnitProduction->SetGameUnitId(unitProduction.GetGameUnitId());
	UnitProduction->SetProductionProgress(unitProduction.GetProductionProgress());
}

bool GameCityItem::operator<(const GameCityItem& rhs) const
{
	return Id < rhs.Id;
}
