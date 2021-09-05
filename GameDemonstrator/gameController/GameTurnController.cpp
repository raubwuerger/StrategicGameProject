#include "stdafx.h"
#include "GameTurnController.h"
#include "GameConfig.h"

GameTurnController::GameTurnController()
{

}

void GameTurnController::SlotStartNextTurn()
{
	GameConfig::CurrentTurn++;
	emit SignalUpdateTurnDialog();
	emit SignalUpdateTurnObjects();
}
