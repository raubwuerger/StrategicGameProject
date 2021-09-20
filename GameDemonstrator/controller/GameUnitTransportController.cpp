#include "stdafx.h"
#include "GameUnitTransportController.h"
#include "game\GameUnit.h"
#include "game\GameUnitRuntimeData.h"
#include "map\MapHexItem.h"
#include "game\GameUnitRepository.h"
#include "model\ModelUnitType.h"

GameUnitTransportController::GameUnitTransportController(GameUnit* playerUnit)
	: GameUnitObject(playerUnit)
{

}

bool GameUnitTransportController::TransportUnit(const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	if (false == CanBeTransported(destination))
	{
		return false;
	}
	return true;
}

bool GameUnitTransportController::CanBeTransported(const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	GameUnit* transporterUnit = GetOwnUnitOnDestinationMapTile(destination->GetId());
	if (nullptr == transporterUnit)
	{
		return false;
	}
	
	const ModelUnitType* transporterModel = transporterUnit->GetModelUnitType();
	const ModelUnitType* transportedModel = GameUnitObject->GetModelUnitType();
	if (false == transporterModel->GetTransportCapacityByTerrainDomain(transportedModel->GetTerrainDomain()))
	{
		return false;
	}

	int freeTransportCapacity = GetFreeTransportCapacity(transporterUnit);
	if (0 >= freeTransportCapacity)
	{
		return false;
	}

	return true;
}

int GameUnitTransportController::GetFreeTransportCapacity(GameUnit* gameUnit) const
{
	if (gameUnit->GetRuntimeData()->TransportCapacity == NOT_INITIALIZED_INT)
	{
		return 0;
	}
	return gameUnit->GetRuntimeData()->TransportCapacity - gameUnit->GetRuntimeData()->TransportedGameUnitIds.size();
}

GameUnit* GameUnitTransportController::GetOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return nullptr;
	}

	if (gameUnitItem->GetModelOwnerTypeId() != GameUnitObject->GetModelOwnerTypeId())
	{
		return nullptr;
	}

	return const_cast<GameUnit*>(gameUnitItem);
}

