#include "stdafx.h"
#include "GameTurnDialog.h"
#include "gameController/GameConfig.h"
#include "game/GameOwnerItem.h"

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
	ui.lineEditTurn->setText(QString::number(GameConfig::CurrentTurn));
	
	QString ownerName("");
	QColor ownerColor(Qt::white);
	GameOwnerItem* gameOwnerItem = GameConfig::Player;
	if (nullptr != gameOwnerItem)
	{
		ownerName = gameOwnerItem->GetName();
		ownerColor = gameOwnerItem->GetColor();
	}
	ui.lineEditOwner->setText(ownerName);

	QPalette palette;
	palette.setColor(QPalette::Base, ownerColor);
	if (ownerColor == Qt::blue || ownerColor == Qt::green || ownerColor == Qt::darkGreen)
	{
		palette.setColor(QPalette::Text, Qt::white);
	}
	ui.lineEditOwner->setPalette(palette);
}
