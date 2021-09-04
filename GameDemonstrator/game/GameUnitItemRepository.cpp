#include "stdafx.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"
#include "LogInterface.h"

GameUnitItemRepository*	GameUnitItemRepository::Instance = nullptr;

GameUnitItemRepository::GameUnitItemRepository()
{
}

GameUnitItemRepository::~GameUnitItemRepository()
{
}

GameUnitItemRepository* GameUnitItemRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameUnitItemRepository;
	return Instance;
}

bool GameUnitItemRepository::Init()
{
	GameUnitItems.clear();
	GameUnitItemsOnGameMapItem.clear();
	return true;
}

void GameUnitItemRepository::Release()
{
	delete Instance;
}

bool GameUnitItemRepository::RegisterGameUnitItem(GameUnitItem* gameUnitItem)
{
	if (nullptr == gameUnitItem)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Handover <gameUnitItem> parameter is null!"));
		return false;
	}
	if (true == GameUnitItems.contains(gameUnitItem->GetId()))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("GameUnitItem with id=%1 already exists!").arg(gameUnitItem->GetId()));
		return false;
	}
	GameUnitItems.insert(gameUnitItem->GetId(), gameUnitItem);
	UpdateGameUnitItemsOnGameMapItem(gameUnitItem);

	return true;
}

int GameUnitItemRepository::GetCount() const
{
	return GameUnitItems.size();
}

QMap<int, GameUnitItem*>::const_iterator GameUnitItemRepository::GetFirstIterator() const
{
	return GameUnitItems.cbegin();
}

QMap<int, GameUnitItem*>::const_iterator GameUnitItemRepository::GetLastIterator() const
{
	return GameUnitItems.cend();
}

GameUnitItem* GameUnitItemRepository::GetGameUnitItemById(int gameUnitItemId)
{
	if (gameUnitItemId < 0)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameUnitItemId invalid (below zero)!"));
		return nullptr;
	}

	if (false == GameUnitItems.contains(gameUnitItemId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Requested GameUnitItemId %1 is not registered!").arg(QString::number(gameUnitItemId)));
		return nullptr;
	}

	return GameUnitItems[gameUnitItemId];

}

const GameUnitItem* GameUnitItemRepository::GetGameUnitItemByGameMapItemId(int gameMapItemId)
{
	if (false == GameUnitItemsOnGameMapItem.contains(gameMapItemId))
	{
		return nullptr;
	}
	return GetGameUnitItemById(GameUnitItemsOnGameMapItem[gameMapItemId]);
}

int GameUnitItemRepository::CreateNewId() const
{
	if (true == GameUnitItems.isEmpty())
	{
		return 1;
	}

	QMap<int, GameUnitItem*>::const_iterator lastGameUnit = GameUnitItems.cend();
	--lastGameUnit;
	int idOfLastGameUnit = lastGameUnit.key();
	return ++idOfLastGameUnit;
}

bool GameUnitItemRepository::IsGameUnitItemOnGameMapItem(int gameMapItemId) const
{
	return GameUnitItemsOnGameMapItem.contains(gameMapItemId);
}

GameUnitItem* GameUnitItemRepository::RemoveGameUnitItemByGameMapItemId(int gameMapItemId)
{
	if (false == GameUnitItemsOnGameMapItem.contains(gameMapItemId))
	{
		return nullptr;
	}

	int gemeUnitItemToDelete = GameUnitItemsOnGameMapItem.take(gameMapItemId);
	GameUnitItem* toDelete = GameUnitItems.take(gemeUnitItemToDelete);
	if (nullptr == toDelete)
	{
		jha::GetLog()->Log_FATAL(QObject::tr("Requested GameUnitItemId %1 is not registered!").arg(QString::number(gemeUnitItemToDelete)));
		return nullptr;
	}

	jha::GetLog()->Log_MESSAGE(QObject::tr("Removed GameUnit (%1) from map!").arg(toDelete->GetName()));
	return toDelete;
}

GameUnitItem* GameUnitItemRepository::RemoveGameUnitItem(const GameUnitItem* gameUnitItem)
{
	Q_ASSERT(gameUnitItem);
	if (nullptr == gameUnitItem)
	{
		return nullptr;
	}

	Q_ASSERT(GameUnitItemsOnGameMapItem.contains(gameUnitItem->GetGameMapItemId()));
	GameUnitItemsOnGameMapItem.remove(gameUnitItem->GetGameMapItemId());
	return GameUnitItems.take(gameUnitItem->GetId());
}

bool GameUnitItemRepository::UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* gameUnitItem)
{
	if (true == GameUnitItemsOnGameMapItem.contains(gameUnitItem->GetGameMapItemId()))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameUnitItemId %1 already registered at MapItemId %2!").arg(QString::number(gameUnitItem->GetId())).arg(QString::number(gameUnitItem->GetGameMapItemId())));
		return false;
	}
	GameUnitItemsOnGameMapItem.insert(gameUnitItem->GetGameMapItemId(), gameUnitItem->GetId());
	return true;
}

bool GameUnitItemRepository::UpdateGameUnitItemsOnGameMapItem(const GameUnitItem* movedUnitItem, int oldMapId)
{
	if (false == GameUnitItemsOnGameMapItem.contains(oldMapId))
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("GameUnitItemId %1 not registered at MapItemId %2!").arg(QString::number(movedUnitItem->GetId())).arg(QString::number(oldMapId)));
	}
	GameUnitItemsOnGameMapItem.take(oldMapId);
	return UpdateGameUnitItemsOnGameMapItem(movedUnitItem);
}
