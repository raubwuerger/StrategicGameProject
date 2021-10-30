#include "stdafx.h"
#include "GameUnitRepository.h"
#include "GameUnit.h"
#include "LogInterface.h"
#include "gameController\GameObjectController.h"


GameUnitRepository*	GameUnitRepository::Instance = nullptr;

GameUnitRepository::GameUnitRepository()
	: UID(20000) //TODO: Get UID from somewhere else
{
}

GameUnitRepository::~GameUnitRepository()
{
}

GameUnitRepository* GameUnitRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameUnitRepository;
	return Instance;
}

bool GameUnitRepository::Init()
{
	GameUnits.clear();
	GameUnitsOnGameMapTile.clear();
	return true;
}

void GameUnitRepository::Release()
{
	delete Instance;
}

bool GameUnitRepository::Register(GameUnit* gameUnit)
{
	if (nullptr == gameUnit)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <gameUnit> parameter is null!"));
		return false;
	}
	if (true == GameUnits.contains(gameUnit->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameUnit with id=%1 already exists!").arg(gameUnit->GetId()));
		return false;
	}
	gameUnit->SetUID(GenerateUID(gameUnit));
	GameUnits.insert(gameUnit->GetId(), gameUnit);
	UpdateGameUnitOnGameMapTile(gameUnit);

	GameObjectController::GetInstance()->RegisterObject(gameUnit);

	return true;
}

int GameUnitRepository::GetCount() const
{
	return GameUnits.size();
}

QMap<int, GameUnit*>::const_iterator GameUnitRepository::GetFirstIterator() const
{
	return GameUnits.cbegin();
}

QMap<int, GameUnit*>::const_iterator GameUnitRepository::GetLastIterator() const
{
	return GameUnits.cend();
}

GameUnit* GameUnitRepository::GetById(int id)
{
	if (id < 0)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameUnitId invalid (below zero)!"));
		return nullptr;
	}

	if (false == GameUnits.contains(id))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameUnitId %1 is not registered!").arg(QString::number(id)));
		return nullptr;
	}

	return GameUnits[id];
}

const GameUnit* GameUnitRepository::GetFirstGameUnitByGameMapTileId(int gameMapTileId)
{
	if (false == GameUnitsOnGameMapTile.contains(gameMapTileId))
	{
		return nullptr;
	}

	QMap<int, int>::iterator unitsOnMapTile = GameUnitsOnGameMapTile.find(gameMapTileId);
	if (unitsOnMapTile == GameUnitsOnGameMapTile.end())
	{
		Q_ASSERT(false);
		return nullptr;
	}

	return GetById(unitsOnMapTile.value());
}

int GameUnitRepository::CreateNewId() const
{
	if (true == GameUnits.isEmpty())
	{
		return 1;
	}

	QMap<int, GameUnit*>::const_iterator lastGameUnit = GameUnits.cend();
	--lastGameUnit;
	int idOfLastGameUnit = lastGameUnit.key();
	return ++idOfLastGameUnit;
}

bool GameUnitRepository::IsGameUnitOnGameMapTile(int gameMapTileId) const
{
	return GameUnitsOnGameMapTile.contains(gameMapTileId);
}

QVector<GameUnit*> GameUnitRepository::RemoveGameUnitByGameMapTileId(int gameMapTileId)
{
	QVector<GameUnit*> gameUnits;
	if (false == GameUnitsOnGameMapTile.contains(gameMapTileId))
	{
		return gameUnits;
	}

	QMap<int,int>::iterator unitsOnMapTile = GameUnitsOnGameMapTile.find(gameMapTileId);
	while (unitsOnMapTile.key() == gameMapTileId)
	{
		gameUnits.push_back(RemoveGameUnit(GameUnits[unitsOnMapTile.value()]));
	}
	return gameUnits;
}

GameUnit* GameUnitRepository::RemoveGameUnit(const GameUnit* gameUnit)
{
	if (nullptr == gameUnit)
	{
		Q_ASSERT(gameUnit);
		return nullptr;
	}

	Q_ASSERT(GameUnitsOnGameMapTile.contains(gameUnit->GetGameTileId()));
	GameUnitsOnGameMapTile.remove(gameUnit->GetGameTileId());
	GameObjectController::GetInstance()->UnregisterObject(gameUnit);
	return GameUnits.take(gameUnit->GetId());
}

bool GameUnitRepository::UpdateGameUnitOnGameMapTile(const GameUnit* gameUnit)
{
	GameUnitsOnGameMapTile.insert(gameUnit->GetGameTileId(), gameUnit->GetId());
	return true;
}

bool GameUnitRepository::UpdateGameUnitOnGameMapTile(const GameUnit* movedUnit, int oldMapId)
{
	if (true == movedUnit->GetIsEmbarked())
	{
		GameUnitsOnGameMapTile.take(oldMapId);
		return UpdateGameUnitOnGameMapTile(movedUnit);
	}
	if (false == GameUnitsOnGameMapTile.contains(oldMapId))
	{
		Q_ASSERT(false);
		return false;
	}
	GameUnitsOnGameMapTile.take(oldMapId);
	return UpdateGameUnitOnGameMapTile(movedUnit);
}

bool GameUnitRepository::RemoveGameUnitFromMapTile(const GameUnit* gameUnit)
{
	if (nullptr == gameUnit)
	{
		Q_ASSERT(gameUnit);
		return nullptr;
	}

	Q_ASSERT(GameUnitsOnGameMapTile.contains(gameUnit->GetGameTileId()));
	GameUnitsOnGameMapTile.remove(gameUnit->GetGameTileId());
	return true;
}

int GameUnitRepository::GenerateUID(const GameUnit*gameUnit)
{
	return UID + gameUnit->GetId();
}
