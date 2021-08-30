#include "stdafx.h"
#include "CreateNewGameDialog.h"

CreateNewGameDialog::CreateNewGameDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.pushButtonOk, SIGNAL(clicked()), this, SLOT(accept()) );
	connect( ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(reject()) );
}

CreateNewGameDialog::~CreateNewGameDialog()
{

}

int CreateNewGameDialog::GetTilesRows() const
{
	return ui.lineEditTilesRows->text().toInt();
}

int CreateNewGameDialog::GetTilesCols() const
{
	return ui.lineEditTilesCols->text().toInt();
}

int CreateNewGameDialog::GetOwnerTypeId() const
{
	return ui.comboBoxChoosePlayer->currentIndex();
}

int CreateNewGameDialog::GetOpponentCount() const
{
	return ui.comboBoxOpponentCount->currentIndex();
}

int CreateNewGameDialog::GetDifficultyLevel() const
{
	return ui.comboDifficulty->currentIndex();
}
