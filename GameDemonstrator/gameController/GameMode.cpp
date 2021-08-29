#include "stdafx.h"
#include "GameMode.h"
#include "LogInterface.h"
#include "GameDemonstrator.h"
#include "ActionRepository.h"

GameMode::GameMode(GameDemonstrator* gameDemonstrator)
	: GameDemonstratorObject(gameDemonstrator),
	MapViewObject(nullptr)
{
}

GameMode::~GameMode()
{
}

bool GameMode::Init()
{
	if (nullptr == GameDemonstratorObject)
	{
		Q_ASSERT(GameDemonstratorObject);
		jha::GetLog()->Log_WARNING(tr("Member <GameDemonstrator> must not be null!"));
		return false;
	}

	if (nullptr == MapViewObject)
	{
		Q_ASSERT(MapViewObject);
		jha::GetLog()->Log_WARNING(tr("Member <MapView> must not be null!"));
		return false;
	}

	return DoInit();
}
