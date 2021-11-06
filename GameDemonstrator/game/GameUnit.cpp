#include "stdafx.h"
#include "GameUnit.h"
#include "model/ModelUnitType.h"
#include "GameUnitRuntimeData.h"
#include "GameUnitHelper.h"
#include "GameUnitTransportContainer.h"

GameUnit::GameUnit(int gameUnitId)
	: Id(gameUnitId),
		UnitType(nullptr),
		GameOwnerObject(nullptr),
		GameMapTileObject(nullptr),
		UnitTypeId(NOT_INITIALIZED_INT),
		GameOwnerId(NOT_INITIALIZED_INT),
		MapTileId(NOT_INITIALIZED_INT),
		RuntimeData(nullptr),
		IsEmbarkedOn(nullptr),
		StartEmbarking(NOT_INITIALIZED_BOOL),
		UnitTransportContainer(nullptr),
		IsTransportUnit(NOT_INITIALIZED_BOOL)
{
	RuntimeData = new GameUnitRuntimeData;
	UnitTransportContainer = new GameUnitTransportContainer;
}

GameUnit::~GameUnit()
{
	delete RuntimeData;
	delete UnitTransportContainer;
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
	if (true == GetIsEmbarked())
	{
		if (false == StartEmbarking )
		{
			RuntimeData->CurrentMovementPoints = 0;
			StartEmbarking = true;
		}
		return true;
	}

	StartEmbarking = false;

	if (false == CanMove())
	{
		return false;
	}
	RuntimeData->CurrentMovementPoints--;
	GameUnitHelper gameUnitHelper(const_cast<GameUnit*>(this));
	gameUnitHelper.MoveToPosition(MapTileId);
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

GameUnit* GameUnit::GetIsEmbarkedOn() const
{
	return IsEmbarkedOn;
}

bool GameUnit::GetIsEmbarked() const
{
	return IsEmbarkedOn != nullptr;
}

void GameUnit::SetEmbarked(GameUnit* embarkedOn)
{
	IsEmbarkedOn = embarkedOn;
}

void GameUnit::SetDismbarked()
{
	IsEmbarkedOn = nullptr;
}

bool GameUnit::GetIsTransporter() const
{
	if (nullptr == UnitTransportContainer)
	{
		return false;
	}
	return UnitTransportContainer->Capacity > 0;
}

int GameUnit::GetCountTransportedUnits() const
{
	return UnitTransportContainer->GetCount();
}

GameUnitTransportContainer* GameUnit::GetUnitTransportContainerNonConst()
{
	return UnitTransportContainer;
}

bool GameUnit::SetGameUnitTransportContainer(GameUnitTransportContainer* transportContainer)
{
	if (nullptr == transportContainer)
	{
		Q_ASSERT(transportContainer);
		return false;
	}

	delete UnitTransportContainer;
	UnitTransportContainer = transportContainer;
	return true;
}

const QString& GameUnit::GetDomain() const
{
	return UnitType->GetTerrainDomainName();
}

GameUnit* GameUnit::GetTransportedUnitAt(int index)
{
	return UnitTransportContainer->GetAt(index);
}

void GameUnit::DisembarkUnit( GameUnit* toDisembark)
{
	UnitTransportContainer->DisembarkUnit(toDisembark);
}

bool GameUnit::CanOccupieCity() const
{
	return UnitType->GetCanOccupieCity();
}

bool GameUnit::operator<(const GameUnit& rhs) const
{
	return Id < rhs.Id;
}

bool GameUnit::operator==(const GameUnit& rhs) const
{
	return Id == rhs.Id;
}
