#include "stdafx.h"
#include "GameCityInfoDialog.h"

GameCityInfoDialog::GameCityInfoDialog(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
}

void GameCityInfoDialog::SetId(const QString& id)
{
	ui.lineEditId->setText(id);
}

void GameCityInfoDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}

void GameCityInfoDialog::SetOwner(const QString& owner)
{
	ui.lineEditOwner->setText(owner);
}

void GameCityInfoDialog::SetOwnerColor(QColor ownerColor)
{
	QPalette palette;
	palette.setColor(QPalette::Base, ownerColor);
	if (ownerColor == Qt::blue || ownerColor == Qt::green || ownerColor == Qt::darkGreen)
	{
		palette.setColor(QPalette::Text, Qt::white);
	}
	ui.lineEditOwner->setPalette(palette);
}

void GameCityInfoDialog::SetEfficiency(const QString& efficiency)
{
	ui.lineEditEfficiency->setText(efficiency);
}

void GameCityInfoDialog::SetSpecialization(const QString& specialization)
{
	ui.lineEditSpecialization->setText(specialization);
}

void GameCityInfoDialog::SetStrength(const QString& strength)
{
	ui.lineEditStrength->setText(strength);
}

void GameCityInfoDialog::SetProductionProgress(int productionPorgress)
{
	ui.progressBarProduction->setValue(productionPorgress);
}

void GameCityInfoDialog::SetProductionText(const QString& productionText)
{
	ui.progressBarProduction->setFormat(productionText);
}
