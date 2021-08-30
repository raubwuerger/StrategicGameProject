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
	QObject::connect(ui.Close, &QPushButton::clicked, gameDemonstrator, &GameDemonstrator::close);
	QObject::connect(ui.Close, &QPushButton::clicked, this, &QDialog::accept);
	QObject::connect(ui.StartEditor, &QPushButton::clicked, this, &QDialog::accept);
	QObject::connect(ui.CreateGame, &QPushButton::clicked, this, &QDialog::accept);
	QObject::connect(ui.LoadGame, &QPushButton::clicked, this, &QDialog::accept);
}
