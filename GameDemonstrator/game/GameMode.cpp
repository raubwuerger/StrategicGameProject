#include "stdafx.h"
#include "GameMode.h"


GameMode::GameMode(GameDemonstrator* gameDemonstrator)
	: GameDemonstratorObject(gameDemonstrator)
{
}

GameMode::~GameMode()
{
}

bool GameMode::Init()
{
	return false;
}
