#include "stdafx.h"
#include "GameTurnController.h"
#include "game\GameConfig.h"

GameTurnController::GameTurnController()
{

}

void GameTurnController::SlotStartNextTurn()
{
	GameConfig::CurrentTurn++;
	emit SignalUpdateTurnObjects();
	emit SignalUpdateTurnDialog();
}
