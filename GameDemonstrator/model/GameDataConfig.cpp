#include "stdafx.h"
#include "GameDataConfig.h"

GameDataConfig* GameDataConfig::Instance = nullptr;

GameDataConfig* GameDataConfig::GetInstance()
{
	//TODO: Mit semaphore oder mutex absichern!
	if( Instance != nullptr )
	{
		return Instance;
	}

	Instance = new GameDataConfig;
	return Instance;
}

GameMapConfig* GameDataConfig::GetGameMapConfig()
{
	return GameMapConfig::GetInstance();
}
