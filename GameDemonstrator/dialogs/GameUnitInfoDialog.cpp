#include "stdafx.h"
#include "GameUnitInfoDialog.h"
#include "helper/TextColorAdjuster.h"

GameUnitInfoDialog::GameUnitInfoDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void GameUnitInfoDialog::SetId(const QString& id)
{
	ui.lineEditId->setText(id);
}

void GameUnitInfoDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}

void GameUnitInfoDialog::SetType(const QString& type)
{
	ui.lineEditType->setText(type);
}

void GameUnitInfoDialog::SetMovementPoints(const QString& movement)
{
	ui.lineEditTypeMovement->setText(movement);
}

void GameUnitInfoDialog::SetMovementPointsColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, TextColorAdjuster::GetAdjustedTextColor(color));
	ui.lineEditTypeMovement->setPalette(palette);
}

void GameUnitInfoDialog::SetStrength(const QString& strength)
{
	ui.lineEditStrength->setText(strength);
}

void GameUnitInfoDialog::SetStrengthColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, TextColorAdjuster::GetAdjustedTextColor(color));
	ui.lineEditStrength->setPalette(palette);
}

void GameUnitInfoDialog::SetOwner(const QString& owner)
{
	ui.lineEditOwner->setText(owner);
}

void GameUnitInfoDialog::SetOwnerColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, TextColorAdjuster::GetAdjustedTextColor(color));
	ui.lineEditOwner->setPalette(palette);
}
