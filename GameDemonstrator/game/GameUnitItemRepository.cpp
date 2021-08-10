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

GameUnitItemRepository::GameUnitItemRepository()
{
}

GameUnitItemRepository::~GameUnitItemRepository()
{
}
