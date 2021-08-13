#include "stdafx.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"
#include "LogInterface.h"

GameUnitItemRepository*	GameUnitItemRepository::Instance = nullptr;

GameUnitItemRepository* GameUnitItemRepository::GetInstance()
{
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameUnitItemRepository;
	return Instance;
}

void GameUnitItemRepository::Init()
{
	GameUnitItems.clear();
	GameUnitItemsGameMapItems.clear();
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
	UpdateGameUnitItemsGameMapItems(gameUnitItem);
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

int GameUnitItemRepository::GetLastIndex() const
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

int GameUnitItemRepository::GetGameMapItemGameUnitItems(int gameMapItemId) const
{
	if ( false == GameUnitItemsGameMapItems.contains(gameMapItemId))
	{
		return 0;
	}
	return 1;
}

GameUnitItemRepository::GameUnitItemRepository()
{
}

GameUnitItemRepository::~GameUnitItemRepository()
{
}

void GameUnitItemRepository::UpdateGameUnitItemsGameMapItems(GameUnitItem* gameUnitItem)
{
	GameUnitItemsGameMapItems.insert(gameUnitItem->GetGameMapItemId(), gameUnitItem->GetId());
}
