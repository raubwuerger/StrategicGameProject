#include "stdafx.h"
#include "GameCity.h"
#include "GameCityRuntimeData.h"
#include "Model\ModelCityType.h"
#include "GameUnitProduction.h"

GameCity::GameCity(int id)
	:	Id(id),
		GameOwnerObject(nullptr),
		GameMapTileObject(nullptr),
		GameOwnerId(NOT_INITIALIZED_INT),
		GameMapTileId(NOT_INITIALIZED_INT),
		SpezializedUnitTypeId(NOT_INITIALIZED_INT),
		RuntimeData(nullptr),
		UnitProduction(nullptr),
		HasOceanAccess(NOT_INITIALIZED_BOOL),
		EFFICIENCY_INCREASE(0.2)
{
	RuntimeData = new GameCityRuntimeData;
	UnitProduction = new GameUnitProduction(Id);
}

GameCity::~GameCity()
{
	delete UnitProduction;
	delete RuntimeData;
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

bool GameCity::HasSpezializedUnitType() const
{
	return SpezializedUnitTypeId != NOT_INITIALIZED_INT;
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

	if (UnitProduction->GetModelTypeId() == MODEL_UNIT_ID_EFFICIENCY)	//TODO: Think about other concept for efficiency production
	{
		UnitProduction->SetProductionProgress(100);
		return;
	}

	int productionProgress = CityType->GetBaseProductionPoints();
	if (UnitProduction->GetModelTypeId() == this->SpezializedUnitTypeId)
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

bool GameCity::GetHasOceanAccess() const
{
	return HasOceanAccess;
}

void GameCity::SetHasOceanAccess(bool hasAccess)
{
	HasOceanAccess = hasAccess;
}

void GameCity::IncreaseEfficiency() const
{
	RuntimeData->CurrentEfficiency += EFFICIENCY_INCREASE;
}

bool GameCity::operator<(const GameCity& rhs) const
{
	return Id < rhs.Id;
}
