#include "stdafx.h"
#include "GameMapConfig.h"

GameMapConfig* GameMapConfig::Instance = nullptr;

GameMapConfig* GameMapConfig::GetInstance()
{
	//TODO: Mit lock versehen
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameMapConfig;
	return Instance;
}

void GameMapConfig::Release()
{
	delete Instance;
	Instance = nullptr;
}

GameMapConfig::GameMapConfig()
	: Rows(1),
	Cols(1)
{
}

GameMapConfig::~GameMapConfig()
{

}
