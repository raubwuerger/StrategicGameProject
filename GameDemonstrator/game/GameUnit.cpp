#include "stdafx.h"
#include "GameUnit.h"
#include "model/ModelUnitType.h"
#include "GameUnitRuntimeData.h"

GameUnit::GameUnit(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		GameOwnerObject(nullptr),
		GameMapTileObject(nullptr),
		UnitTypeId(-1),
		GameOwnerId(-1),
		MapTileId(-1),
		RuntimeData(nullptr)
{
}

GameUnit::~GameUnit()
{
	delete RuntimeData;
	RuntimeData = nullptr;
}

const ModelUnitType* GameUnit::GetModelUnitType() const
{
	return UnitType;
}

const GameOwner* GameUnit::GetGameOwner() const
{
	return GameOwnerObject;
}

const GameMapTile* GameUnit::GetGameMapTile() const
{
	return GameMapTileObject;
}

const int GameUnit::GetId() const
{
	return Id;
}

const QString& GameUnit::GetName() const
{
	return Name;
}

void GameUnit::SetName(const QString& name) const
{
	Name = name;
}

int GameUnit::GetModelUnitTypeId() const
{
	return UnitTypeId;
}

int GameUnit::GetModelOwnerTypeId() const
{
	return GameOwnerId;
}

int GameUnit::GetGameTileId() const
{
	return MapTileId;
}

void GameUnit::UpdateTurn() const
{
	RuntimeData->CurrentMovementPoints = RuntimeData->BaseMovementPoints;
	RuntimeData->CurrentStrength = RuntimeData->BaseStrength;
	//TODO: Reset movement points
	//TODO: Heal Unit
	//TODO: ...
}

bool GameUnit::CanMove() const
{
	Q_ASSERT(RuntimeData);
	if (0 < RuntimeData->CurrentMovementPoints)
	{
		return true;
	}
	return false;
}

bool GameUnit::Move() const
{
	if (false == CanMove())
	{
		return false;
	}
	RuntimeData->CurrentMovementPoints--;
	return true;
}

void GameUnit::Attacks() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

void GameUnit::Defends() const
{
	throw std::logic_error("The method or operation is not implemented.");
}

int GameUnit::GetCurrentStrength() const
{
	return RuntimeData->CurrentStrength;
}

int GameUnit::GetBaseStrength() const
{
	return RuntimeData->BaseStrength;
}

int GameUnit::GetCurrentMovementPoints() const
{
	return RuntimeData->CurrentMovementPoints;
}

int GameUnit::GetBaseMovementPoints() const
{
	return RuntimeData->BaseMovementPoints;
}

bool GameUnit::InitRuntimeData()
{
	RuntimeData = new GameUnitRuntimeData();
	RuntimeData->BaseStrength = UnitType->GetStrength();
	RuntimeData->CurrentStrength = UnitType->GetStrength();
	RuntimeData->BaseMovementPoints = UnitType->GetMovementPoints();
	RuntimeData->CurrentMovementPoints = UnitType->GetMovementPoints();
	return true;
}

GameUnitRuntimeData* GameUnit::GetRuntimeData()
{
	return RuntimeData;
}

QString GameUnit::CreatStrengthString() const
{
	QString currentStrength;
	currentStrength += QString::number(GetCurrentStrength());
	currentStrength += " / ";
	currentStrength += QString::number(GetBaseStrength());
	return currentStrength;
}

QString GameUnit::CreateMovementPointsString() const
{
	QString movementPoints;
	movementPoints += QString::number(GetCurrentMovementPoints());
	movementPoints += " / ";
	movementPoints += QString::number(GetBaseMovementPoints());
	return movementPoints;
}

bool GameUnit::CanOccupieCity() const
{
	return UnitType->GetCanOccupieCity();
}

bool GameUnit::operator<(const GameUnit& rhs) const
{
	return Id < rhs.Id;
}