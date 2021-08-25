#include "stdafx.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"
#include "LogInterface.h"

GameCityItemRepository*	GameCityItemRepository::Instance = nullptr;

GameCityItemRepository* GameCityItemRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameCityItemRepository;
	return Instance;
}

void GameCityItemRepository::Init()
{
	GameCityItems.clear();
	GameCityItemsOnGameMapItem.clear();
}

void GameCityItemRepository::Release()
{
	delete Instance;
}

bool GameCityItemRepository::RegisterItem(GameCityItem* gameCityItem)
{
	if (nullptr == gameCityItem)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <GameCityItem> parameter is null!"));
		return false;
	}
	if (true == GameCityItems.contains(gameCityItem->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameCityItem with id=%1 already exists!").arg(gameCityItem->GetId()));
		return false;
	}
	GameCityItems.insert(gameCityItem->GetId(), gameCityItem);
	UpdateGameCityItemsOnGameMapItem(gameCityItem);

	return true;
}

int GameCityItemRepository::GetCount() const
{
	return GameCityItems.size();
}

QMap<int, GameCityItem*>::const_iterator GameCityItemRepository::GetFirstIterator() const
{
	return GameCityItems.cbegin();
}

QMap<int, GameCityItem*>::const_iterator GameCityItemRepository::GetLastIterator() const
{
	return GameCityItems.cend();
}

GameCityItem* GameCityItemRepository::GetGameCityItemById(int GameCityItemId)
{
	if (GameCityItemId < 0)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityItemId invalid (below zero)!"));
		return nullptr;
	}

	if (false == GameCityItems.contains(GameCityItemId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityItemId %1 is not registered!").arg(QString::number(GameCityItemId)));
		return nullptr;
	}

	return GameCityItems[GameCityItemId];

}

GameCityItem* GameCityItemRepository::RemoveCityItemById(int cityItemId)
{
	if (false == GameCityItems.contains(cityItemId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameCityItemId %1 is not registered!").arg(QString::number(cityItemId)));
		return nullptr;
	}
	GameCityItem* toRemove = GameCityItems.take(cityItemId);
	GameCityItemsOnGameMapItem.take(cityItemId);
	return toRemove;
}

GameCityItem* GameCityItemRepository::RemoveCityItemByGameMapItemId(int mapItemId)
{
	if (false == GameCityItemsOnGameMapItem.contains(mapItemId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("No GameCityItem registered on gameMapItem id=!").arg(QString::number(mapItemId)));
		return nullptr;
	}

	int cityItemId = GameCityItemsOnGameMapItem.take(mapItemId);
	return GameCityItems.take(cityItemId);
}

bool GameCityItemRepository::IsCityOnGameMapItemId(int mapItemId) const
{
	if (false == GameCityItemsOnGameMapItem.contains(mapItemId))
	{
		return false;
	}
	return true;
}

GameCityItem* GameCityItemRepository::GetCityItemByGameMapItemId(int mapItemId)
{
	if (false == GameCityItemsOnGameMapItem.contains(mapItemId))
	{
		return nullptr;
	}

	return GetGameCityItemById(GameCityItemsOnGameMapItem[mapItemId]);
}

int GameCityItemRepository::CreateNewId() const
{
	if (true == GameCityItems.isEmpty())
	{
		return 1;
	}

	QMap<int, GameCityItem*>::const_iterator lastGameUnit = GameCityItems.cend();
	--lastGameUnit;
	int idOfLastGameUnit = lastGameUnit.key();
	return ++idOfLastGameUnit;
}

GameCityItemRepository::GameCityItemRepository()
{
}

GameCityItemRepository::~GameCityItemRepository()
{
}

bool GameCityItemRepository::UpdateGameCityItemsOnGameMapItem(const GameCityItem* gameCityItem)
{
	if (true == GameCityItemsOnGameMapItem.contains(gameCityItem->GetGameMapItemId()))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameCityItemId %1 already registered at MapItemId %2!").arg(QString::number(gameCityItem->GetId())).arg(QString::number(gameCityItem->GetGameMapItemId())));
		return false;
	}
	GameCityItemsOnGameMapItem.insert(gameCityItem->GetGameMapItemId(), gameCityItem->GetId());
	return true;
}
