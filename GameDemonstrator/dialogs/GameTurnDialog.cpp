#include "stdafx.h"
#include "GameTurnDialog.h"
#include "gameController/GameConfig.h"

GameTurnDialog::GameTurnDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GameTurnDialog::~GameTurnDialog()
{

}

void GameTurnDialog::SlotUpdateGameTurnInfo()
{
	ui.turnInfoEdit->setPlainText(QString::number(GameConfig::CurrentTurn));
}
