#include "stdafx.h"
#include "GameCityItem.h"
#include "GameCityItemRuntimeData.h"
#include "Model\ModelCityType.h"

GameCityItem::GameCityItem(int id)
	: Id(id),
		OwnerItem(nullptr),
		MapItem(nullptr),
		OwnerItemId(-1),
		MapItemId(-1),
		SpezializedUnitTypeId(-1),
		RuntimeData(nullptr)
{
}

GameCityItem::~GameCityItem()
{
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

void GameCityItem::UpdateTurn()
{
	//TODO: Increase build unit step
	//TODO: ...
}

int GameCityItem::GetSpezializedUnitTypeId() const
{
	return SpezializedUnitTypeId;
}

bool GameCityItem::Move()
{
	return false; // Nothing to do
}

void GameCityItem::Attacks()
{
	return; // Nothing to do
}

void GameCityItem::Defends()
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

bool GameCityItem::operator<(const GameCityItem& rhs) const
{
	return Id < rhs.Id;
}
