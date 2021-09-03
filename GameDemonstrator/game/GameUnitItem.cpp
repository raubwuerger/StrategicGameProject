#include "stdafx.h"
#include "GameUnitItem.h"
#include "model/ModelUnitType.h"
#include "GameUnitItemRuntimeData.h"

GameUnitItem::GameUnitItem(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		OwnerType(nullptr),
		MapItem(nullptr),
		UnitTypeId(-1),
		OwnerTypeId(-1),
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

const ModelOwnerType* GameUnitItem::GetModelOwnerType() const
{
	return OwnerType;
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
	return OwnerTypeId;
}

int GameUnitItem::GetGameMapItemId() const
{
	return MapItemId;
}

void GameUnitItem::UpdateTurn()
{
	RuntimeData->CurrenMovementPoints = RuntimeData->BaseMovementPoints;
	RuntimeData->CurrentStrength = RuntimeData->BaseStrength;
	//TODO: Reset movement points
	//TODO: Heal Unit
	//TODO: ...
}

bool GameUnitItem::CanMove() const
{
	Q_ASSERT(RuntimeData);
	if (0 < RuntimeData->CurrenMovementPoints)
	{
		return true;
	}
	return false;
}

bool GameUnitItem::Moved()
{
	if (false == CanMove())
	{
		return false;
	}
	RuntimeData->CurrenMovementPoints--;
	return true;
}

void GameUnitItem::Attacks()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GameUnitItem::Defends()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int GameUnitItem::GetStrength() const
{
	return RuntimeData->CurrentStrength;
}

bool GameUnitItem::InitRuntimeData()
{
	RuntimeData = new GameUnitItemRuntimeData();
	RuntimeData->BaseStrength = UnitType->GetStrength();
	RuntimeData->CurrentStrength = UnitType->GetStrength();
	RuntimeData->BaseMovementPoints = UnitType->GetMovementPoints();
	RuntimeData->CurrenMovementPoints = UnitType->GetMovementPoints();
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
