#include "stdafx.h"
#include "GameMainDialog.h"
#include "GameDemonstrator.h"

GameMainDialog::GameMainDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

void GameMainDialog::Init(GameDemonstrator* gameDemonstrator)
{
	GameDemonstratorObject = gameDemonstrator;
	QObject::connect(ui.CloseGame, &QPushButton::clicked, gameDemonstrator, &GameDemonstrator::close);
	QObject::connect(ui.CloseGame, &QPushButton::clicked, this, &QDialog::accept);
	QObject::connect(ui.StartEditor, &QPushButton::clicked, this, &QDialog::accept);
	QObject::connect(ui.StartSingleplayer, &QPushButton::clicked, this, &QDialog::accept);
}
