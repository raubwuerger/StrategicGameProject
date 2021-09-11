#include "stdafx.h"
#include "GameCityRepository.h"
#include "GameCity.h"
#include "LogInterface.h"
#include "game\GameOwner.h"
#include "gameController\GameObjectController.h"

GameCityRepository*	GameCityRepository::Instance = nullptr;

GameCityRepository::GameCityRepository()
	: UID(10000) //TODO: Get UID from somewhere else
{
}

GameCityRepository::~GameCityRepository()
{
}

GameCityRepository* GameCityRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameCityRepository;
	return Instance;
}

bool GameCityRepository::Init()
{
	GameCitys.clear();
	GameCitysOnGameMapTile.clear();
	return true;
}

void GameCityRepository::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool GameCityRepository::Register(GameCity* gameCity)
{
	if (nullptr == gameCity)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <GameCity> parameter is null!"));
		return false;
	}
	if (true == GameCitys.contains(gameCity->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameCity with id=%1 already exists!").arg(gameCity->GetId()));
		return false;
	}
	GameCitys.insert(gameCity->GetId(), gameCity);
	UpdateGameCitysOnGameMapTile(gameCity);

	gameCity->SetUID(GenerateUID(gameCity));
	GameObjectController::GetInstance()->RegisterObject(gameCity);

	return true;
}

int GameCityRepository::GetCount() const
{
	return GameCitys.size();
}

QMap<int, GameCity*>::const_iterator GameCityRepository::GetFirstIterator() const
{
	return GameCitys.cbegin();
}

QMap<int, GameCity*>::const_iterator GameCityRepository::GetLastIterator() const
{
	return GameCitys.cend();
}

GameCity* GameCityRepository::GetById(int gameCityId)
{
	if (gameCityId < 0)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityId invalid (below zero)!"));
		return nullptr;
	}

	if (false == GameCitys.contains(gameCityId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityId %1 is not registered!").arg(QString::number(gameCityId)));
		return nullptr;
	}

	return GameCitys[gameCityId];

}

GameCity* GameCityRepository::RemoveById(int gameCityId)
{
	if (false == GameCitys.contains(gameCityId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityId %1 is not registered!").arg(QString::number(gameCityId)));
		return nullptr;
	}
	GameCity* toRemove = GameCitys.take(gameCityId);
	GameCitysOnGameMapTile.take(gameCityId);
	return toRemove;
}

GameCity* GameCityRepository::RemoveByGameMapTileId(int mapTileId)
{
	if (false == GameCitysOnGameMapTile.contains(mapTileId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("No GameCity registered on gameMapTile id=!").arg(QString::number(mapTileId)));
		return nullptr;
	}

	int gameCityId = GameCitysOnGameMapTile.take(mapTileId);
	return GameCitys.take(gameCityId);
}

bool GameCityRepository::IsCityOnGameMapTileId(int mapTileId) const
{
	if (false == GameCitysOnGameMapTile.contains(mapTileId))
	{
		return false;
	}
	return true;
}

GameCity* GameCityRepository::GetGameCityByGameMapTileId(int mapTileId)
{
	if (false == GameCitysOnGameMapTile.contains(mapTileId))
	{
		return nullptr;
	}

	return GetById(GameCitysOnGameMapTile[mapTileId]);
}

int GameCityRepository::CreateNewId() const
{
	if (true == GameCitys.isEmpty())
	{
		return 1;
	}

	QMap<int, GameCity*>::const_iterator lastGameUnit = GameCitys.cend();
	--lastGameUnit;
	int idOfLastGameUnit = lastGameUnit.key();
	return ++idOfLastGameUnit;
}

bool GameCityRepository::ChangeOwner(const GameCity* gameCity, const GameOwner* gameOwner)
{
	GameCity* gameCityToChange = GetById(gameCity->GetId());
	gameCityToChange->SetGameOwner(gameOwner);
	gameCityToChange->SetGameOwnerId(gameOwner->GetId());
	return true;
}

bool GameCityRepository::UpdateGameCitysOnGameMapTile(const GameCity* gameCity)
{
	if (true == GameCitysOnGameMapTile.contains(gameCity->GetGameMapTileId()))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameCityId %1 already registered at MapTileId %2!").arg(QString::number(gameCity->GetId())).arg(QString::number(gameCity->GetGameMapTileId())));
		return false;
	}
	GameCitysOnGameMapTile.insert(gameCity->GetGameMapTileId(), gameCity->GetId());
	return true;
}

int GameCityRepository::GenerateUID(GameCity* gameCity)
{
	return UID + gameCity->GetId();
}
