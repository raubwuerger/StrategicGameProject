#include "stdafx.h"
#include "GameTurnDialog.h"
#include "game/GameConfig.h"
#include "game/GameOwnerItem.h"

GameTurnDialog::GameTurnDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GameTurnDialog::~GameTurnDialog()
{

}

void GameTurnDialog::SetGameTurn(const QString& gameTurn)
{
	ui.lineEditTurn->setText(gameTurn);
}

void GameTurnDialog::SetPlayerName(const QString& playerName)
{
	ui.lineEditOwner->setText(playerName);
}

void GameTurnDialog::SetPlayerColor(QColor color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	if (color == Qt::blue || color == Qt::green || color == Qt::darkGreen)
	{
		palette.setColor(QPalette::Text, Qt::white);
	}
	ui.lineEditOwner->setPalette(palette);
}

void GameTurnDialog::SetPlayerTextColor(QColor color)
{
	QPalette palette;
	palette.setColor(QPalette::Text, color);
	ui.lineEditOwner->setPalette(palette);
}
