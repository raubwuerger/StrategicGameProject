#include "stdafx.h"
#include "GameCitySettingsDialog.h"

GameCitySettingsDialog::GameCitySettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonOk, &QPushButton::click, this, &GameCitySettingsDialog::close);
	connect(ui.pushButtonCancel, &QPushButton::click, this, &GameCitySettingsDialog::close);
}

void GameCitySettingsDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}
