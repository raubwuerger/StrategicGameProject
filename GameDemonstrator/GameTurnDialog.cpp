#include "stdafx.h"
#include "GameTurnDialog.h"

GameTurnDialog::GameTurnDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GameTurnDialog::~GameTurnDialog()
{

}

void GameTurnDialog::UpdateGameTurnInfo( QDate date )
{
	ui.turnInfoEdit->setPlainText( date.toString("MMMM, yyyy") );
}
