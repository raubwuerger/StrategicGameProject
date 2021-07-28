#include "stdafx.h"
#include "GameMapFactory.h"
#include "GameMap.h"
#include "GameMapConfig.h"

GameMapFactory* GameMapFactory::Instance = nullptr; 

GameMapFactory* GameMapFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameMapFactory;
	return Instance;
}

void GameMapFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

GameMapFactory::GameMapFactory()
	: TheGameMap(nullptr)
{
}

GameMapFactory::~GameMapFactory()
{
	delete TheGameMap;
	TheGameMap = nullptr;
}

GameMap* GameMapFactory::CreateMap()
{
	TheGameMap = new GameMap();
	TheGameMap->Init( GameMapConfig::GetInstance()->Rows, GameMapConfig::GetInstance()->Cols );
	return TheGameMap;
}
