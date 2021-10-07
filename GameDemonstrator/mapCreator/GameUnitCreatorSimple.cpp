#include "stdafx.h"
#include "GameUnitCreatorSimple.h"

#include "game\GameCityRepository.h"
#include "game\GameCity.h"

#include "game\GameUnitFactory.h"

GameUnitCreatorSimple::GameUnitCreatorSimple()
{
	GameUnitParameterObjectTemporary = new GameUnitParameterObject();
}

GameUnitCreatorSimple::~GameUnitCreatorSimple()
{
	delete GameUnitParameterObjectTemporary;
	GameUnitParameterObjectTemporary = nullptr;
}

bool GameUnitCreatorSimple::Create()
{
	const int OWNER_ID_NEUTRAL = 1;
	GameUnitFactory gameUnitFactory;

	QMap<int, GameCity*>::const_iterator cityIterator = GameCityRepository::GetInstance()->GetFirstIterator();

	while (cityIterator != GameCityRepository::GetInstance()->GetLastIterator())
	{
		int ownerTypeId = (*cityIterator)->GetGameOwnerId();
		if (OWNER_ID_NEUTRAL == ownerTypeId)
		{
			cityIterator++;
			continue;
		}

		int mapTileId = (*cityIterator)->GetGameMapTileId();
		GameUnitParameterObject* newGameUnitParameterObject = CreateDefaultGameUnitParameterObject(mapTileId, ownerTypeId);
		GameUnit* newGameUnit = gameUnitFactory.Create(*newGameUnitParameterObject);
		if ( nullptr == newGameUnit)
		{
			Q_ASSERT(newGameUnit);
			return false;
		}
		cityIterator++;
	}
	return true;
}

GameUnitParameterObject* GameUnitCreatorSimple::CreateDefaultGameUnitParameterObject(int mapTileId, int ownerTypeId) const
{
	const int MODEL_UNIT_TYPE_ID_INFANTRY = 1;
	GameUnitParameterObjectTemporary->ModelUnitTypeId = MODEL_UNIT_TYPE_ID_INFANTRY;
	GameUnitParameterObjectTemporary->GameMapTileId = mapTileId;
	GameUnitParameterObjectTemporary->GameOwnerId = ownerTypeId;
	return GameUnitParameterObjectTemporary;
}
