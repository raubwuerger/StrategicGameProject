#include "stdafx.h"
#include "GameUnitItem.h"
#include "model/ModelUnitType.h"
#include "GameUnitItemRuntimeData.h"

GameUnitItem::GameUnitItem(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		OwnerItem(nullptr),
		MapItem(nullptr),
		UnitTypeId(-1),
		OwnerItemId(-1),
		MapItemId(-1),
		RuntimeData(nullptr)
{
}

GameUnitItem::~GameUnitItem()
{
	delete RuntimeData;
	RuntimeData = nullptr;
}

const ModelUnitType* GameUnitItem::GetModelUnitType() const
{
	return UnitType;
}

const GameOwnerItem* GameUnitItem::GetGameOwnerItem() const
{
	return OwnerItem;
}

const GameMapItem* GameUnitItem::GetGameMapItem() const
{
	return MapItem;
}

const int GameUnitItem::GetId() const
{
	return Id;
}

const QString& GameUnitItem::GetName() const
{
	return Name;
}

void GameUnitItem::SetName(const QString& name)
{
	Name = name;
}

int GameUnitItem::GetModelUnitTypeId() const
{
	return UnitTypeId;
}

int GameUnitItem::GetModelOwnerTypeId() const
{
	return OwnerItemId;
}

int GameUnitItem::GetGameMapItemId() const
{
	return MapItemId;
}

void GameUnitItem::UpdateTurn() const
{
	RuntimeData->CurrentMovementPoints = RuntimeData->BaseMovementPoints;
	RuntimeData->CurrentStrength = RuntimeData->BaseStrength;
	//TODO: Reset movement points
	//TODO: Heal Unit
	//TODO: ...
}

bool GameUnitItem::CanMove() const
{
	Q_ASSERT(RuntimeData);
	if (0 < RuntimeData->CurrentMovementPoints)
	{
		return true;
	}
	return false;
}

bool GameUnitItem::Move() const
{
	if (false == CanMove())
	{
		return false;
	}
	RuntimeData->CurrentMovementPoints--;
	return true;
}

void GameUnitItem::Attacks() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GameUnitItem::Defends() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int GameUnitItem::GetCurrentStrength() const
{
	return RuntimeData->CurrentStrength;
}

int GameUnitItem::GetBaseStrength() const
{
	return RuntimeData->BaseStrength;
}

int GameUnitItem::GetCurrentMovementPoints() const
{
	return RuntimeData->CurrentMovementPoints;
}

int GameUnitItem::GetBaseMovementPoints() const
{
	return RuntimeData->BaseMovementPoints;
}

bool GameUnitItem::InitRuntimeData()
{
	RuntimeData = new GameUnitItemRuntimeData();
	RuntimeData->BaseStrength = UnitType->GetStrength();
	RuntimeData->CurrentStrength = UnitType->GetStrength();
	RuntimeData->BaseMovementPoints = UnitType->GetMovementPoints();
	RuntimeData->CurrentMovementPoints = UnitType->GetMovementPoints();
	return true;
}

bool GameUnitItem::CanOccupieCity() const
{
	return UnitType->GetCanOccupieCity();
}

bool GameUnitItem::operator<(const GameUnitItem& rhs) const
{
	return Id < rhs.Id;
}
