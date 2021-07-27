#include "stdafx.h"
#include "GameData.h"
#include "GameMapConfig.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

void GameData::Init()
{
}

void GameData::Release()
{
}

GameMapConfig* GameData::GetGameMapConfig()
{
	return GameMapConfig::GetInstance();
}
