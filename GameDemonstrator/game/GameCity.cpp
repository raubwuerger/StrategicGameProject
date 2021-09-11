#include "stdafx.h"
#include "GameCity.h"
#include "GameCityRuntimeData.h"
#include "Model\ModelCityType.h"
#include "GameUnitProduction.h"

GameCity::GameCity(int id)
	:	Id(id),
		GameOwnerObject(nullptr),
		GameMapTileObject(nullptr),
		GameOwnerId(-1),
		GameMapTileId(-1),
		SpezializedUnitTypeId(-1),
		RuntimeData(nullptr),
		UnitProduction(nullptr)
{
}

GameCity::~GameCity()
{
	delete UnitProduction;
}

const int GameCity::GetId() const
{
	return Id;
}

const QString& GameCity::GetName() const
{
	return Name;
}

void GameCity::SetName(const QString& name)
{
	Name = name;
}

const GameOwner* GameCity::GetGameOwner() const
{
	return GameOwnerObject;
}

void GameCity::SetGameOwner(const GameOwner* gameOwner)
{
	GameOwnerObject = gameOwner;
}

void GameCity::SetGameOwnerId(int gameOwnerId)
{
	GameOwnerId = gameOwnerId;
}

const GameMapTile* GameCity::GetGameMapTile() const
{
	return GameMapTileObject;
}

int GameCity::GetGameOwnerId() const
{
	return GameOwnerId;
}

int GameCity::GetGameMapTileId() const
{
	return GameMapTileId;
}

const ModelCityType* GameCity::GetCityModelType() const
{
	return CityType;
}

int GameCity::GetModelCityTypeId() const
{
	return CityTypeId;
}

void GameCity::UpdateTurn() const
{
	ResetDefenceValue();
	UpdateUnitProduction();
	//TODO: Increase build unit step
	//TODO: ...
}

int GameCity::GetSpezializedUnitTypeId() const
{
	return SpezializedUnitTypeId;
}

bool GameCity::Move() const
{
	return false; // Nothing to do
}

void GameCity::Attacks() const
{
	return; // Nothing to do
}

void GameCity::Defends() const
{
	return; // 
}

int GameCity::GetBaseStrength() const
{
	return RuntimeData->BaseStrength;
}

int GameCity::GetCurrentStrength() const
{
	return RuntimeData->CurrentStrength;
}

int GameCity::GetBaseEfficiency() const
{
	return RuntimeData->BaseEfficiency;
}

int GameCity::GetCurrentEfficiency() const
{
	return RuntimeData->CurrentEfficiency;
}

bool GameCity::InitRuntimeData()
{
	RuntimeData = new GameCityRuntimeData();
	RuntimeData->BaseEfficiency = CityType->GetEfficiency();
	RuntimeData->CurrentEfficiency = CityType->GetEfficiency();
	RuntimeData->BaseStrength = CityType->GetDefenceValue();
	RuntimeData->CurrentStrength = CityType->GetDefenceValue();
	return true;
}

GameCityRuntimeData* GameCity::GetRuntimeData()
{
	return RuntimeData;
}

void GameCity::ResetDefenceValue() const
{
	RuntimeData->CurrentStrength = RuntimeData->BaseStrength;
}

void GameCity::UpdateUnitProduction() const
{
	int productionProgress = CityType->GetBaseProductionPoints();
	if (UnitProduction->GetGameUnitId() == this->SpezializedUnitTypeId)
	{
		productionProgress += CityType->GetBaseProductionPoints();
	}
	UnitProduction->UpdateProductionProgress(productionProgress);
}

const GameUnitProduction* GameCity::GetUnitProduction() const
{
	return UnitProduction;
}

void GameCity::SetGameUnitProduction(const GameUnitProduction* unitProduction)
{
	Q_ASSERT(unitProduction);
	UnitProduction = unitProduction;
}

bool GameCity::operator<(const GameCity& rhs) const
{
	return Id < rhs.Id;
}
