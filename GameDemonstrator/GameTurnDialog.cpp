#include "stdafx.h"
#include "GameTurnDialog.h"

CGameTurnDialog::CGameTurnDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CGameTurnDialog::~CGameTurnDialog()
{

}

void CGameTurnDialog::UpdateGameTurnInfo( QDate date )
{
	ui.turnInfoEdit->setPlainText( date.toString("MMMM, yyyy") );
}
