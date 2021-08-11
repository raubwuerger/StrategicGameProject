#include "stdafx.h"
#include "GameUnitItemRepository.h"
#include "GameMapItem.h"
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

GameUnitItemRepository::GameUnitItemRepository()
{
}

GameUnitItemRepository::~GameUnitItemRepository()
{
}
