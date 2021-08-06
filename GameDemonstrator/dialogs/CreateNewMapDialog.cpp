#include "stdafx.h"
#include "CreateNewMapDialog.h"

CreateNewMapDialog::CreateNewMapDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect( ui.pushButtonOk, SIGNAL(clicked()), this, SLOT(accept()) );
	connect( ui.pushButtonCancel, SIGNAL(clicked()), this, SLOT(reject()) );
}

CreateNewMapDialog::~CreateNewMapDialog()
{

}

int CreateNewMapDialog::GetTilesX() const
{
	return ui.lineEditTilesX->text().toInt();
}

int CreateNewMapDialog::GetTilesY() const
{
	return ui.lineEditTilesY->text().toInt();
}
