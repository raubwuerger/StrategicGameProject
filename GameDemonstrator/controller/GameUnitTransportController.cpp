#include "stdafx.h"
#include "GameUnitTransportController.h"
#include "game\GameUnit.h"
#include "game\GameUnitRuntimeData.h"
#include "map\MapHexItem.h"
#include "game\GameUnitRepository.h"
#include "model\ModelUnitType.h"

GameUnitTransportController::GameUnitTransportController(GameUnit* playerUnit)
	: UnitToTransport(playerUnit),
	TransporterUnit(nullptr)
{

}

bool GameUnitTransportController::TransportUnit(const MapHexItem* destination)
{
	Q_ASSERT(destination);
	if (false == UnitToTransport->HasMovementPointsLeft())
	{
		return false;
	}
	
	if (false == CanBeTransported(destination))
	{
		return false;
	}

	EmbarkUnit();
	return true;
}

bool GameUnitTransportController::CanBeTransported(const MapHexItem* destination) const
{
	Q_ASSERT(destination);
	TransporterUnit = GetOwnUnitOnDestinationMapTile(destination->GetId());
	if (nullptr == TransporterUnit)
	{
		return false;
	}
	
	const ModelUnitType* transporterModel = TransporterUnit->GetModelUnitType();
	const ModelUnitType* transportedModel = UnitToTransport->GetModelUnitType();
	if (false == transporterModel->GetTransportCapacityByTerrainDomain(transportedModel->GetTerrainDomain()))
	{
		return false;
	}

	int freeTransportCapacity = GetFreeTransportCapacity(TransporterUnit);
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

void GameUnitTransportController::EmbarkUnit()
{

}

GameUnit* GameUnitTransportController::GetOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetByGameMapTileId(gameMapItemId);
	if (nullptr == gameUnitItem)
	{
		return nullptr;
	}

	if (gameUnitItem->GetModelOwnerTypeId() != UnitToTransport->GetModelOwnerTypeId())
	{
		return nullptr;
	}

	return const_cast<GameUnit*>(gameUnitItem);
}

