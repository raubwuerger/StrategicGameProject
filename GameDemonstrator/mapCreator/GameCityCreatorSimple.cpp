#include "stdafx.h"
#include "GameCityCreatorSimple.h"
#include "LogInterface.h"
#include "Game\GameMapTileRepository.h"

bool GameCityCreatorSimple::Create()
{
	if (true == ValidTerrainTypesProcent.empty())
	{
		jha::GetLog()->Log_INFO("Member <ValidTerrainTypesProcent> is empty!");
		return false;
	}

	return false;
}

bool GameCityCreatorSimple::AddValidTerrainTypeProcent(std::map<int, int> validTerrainTypeProcent)
{
	return false;
}
