#include "stdafx.h"
#include "GameUnitTransportController.h"
#include "game\GameUnit.h"
#include "game\GameUnitRuntimeData.h"
#include "game\GameUnitRepository.h"
#include "game\GameCityRuntimeData.h"
#include "model\ModelUnitType.h"
#include "map\MapUnitItemRepository.h"
#include "map\MapHexItem.h"
#include "game\GameUnitHelper.h"
#include "game\GameUnitTransportContainer.h"
#include "TerrainAccessTester.h"

GameUnitTransportController::GameUnitTransportController(GameUnit* playerUnit)
	: UnitToTransport(playerUnit),
	TransporterUnit(nullptr)
{

}

bool GameUnitTransportController::EmbarkUnit(const MapHexItem* destination)
{
	Q_ASSERT(destination);
	
	if (false == CanBeTransported(destination))
	{
		return false;
	}

	return EmbarkUnit();
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
	if (0 >= transporterModel->GetTransportCapacityByTerrainDomain(transportedModel->GetTerrainDomain()))
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

bool GameUnitTransportController::EmbarkUnit()
{
	TransporterUnit->GetUnitTransportContainerNonConst()->EmbarkUnit(UnitToTransport);
	MapUnitItem* mapUnitToTransport = MapUnitItemRepository::GetInstance()->Hide(UnitToTransport->GetId());
	if (nullptr == mapUnitToTransport)
	{
		Q_ASSERT(false);
		return false;
	}
	UnitToTransport->SetEmbarked(TransporterUnit);

	return true;
}

bool GameUnitTransportController::DisembarkUnit(const MapHexItem* destination)
{
	if (false == UnitToTransport->GetIsEmbarked()) //No jump from one transporter to another
	{
		return false;
	}

	if (false == UnitToTransport->CanMove())
	{
		return false;
	}

	if (true == GameUnitHelper::IsOwnUnitOnDestinationMapTile(UnitToTransport, destination->GetId()))
	{
		return false;
	}

	if (true == GameUnitHelper::IsEnemyOnDestinationMapTile(UnitToTransport, destination->GetId()))
	{
		return false;
	}

	if (false == TerrainAccessTester::Accessable(UnitToTransport, destination))
	{
		return false;
	}

	TransporterUnit = UnitToTransport->GetIsEmbarkedOn();
	UnitToTransport->SetDismbarked();
	TransporterUnit->DisembarkUnit(UnitToTransport);
	MapUnitItemRepository::GetInstance()->Show(TransporterUnit->GetId());
	return true;
}

int GameUnitTransportController::GetFreeTransportCapacity(GameUnit* gameUnit) const
{
	return gameUnit->GetUnitTransportContainerNonConst()->GetFreeCapacity();
}

GameUnit* GameUnitTransportController::GetOwnUnitOnDestinationMapTile(int gameMapItemId) const
{
	const GameUnit* gameUnitItem = GameUnitRepository::GetInstance()->GetTransporterUnitByGameMapTileId(gameMapItemId);
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

