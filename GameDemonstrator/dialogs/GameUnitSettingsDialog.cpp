#include "stdafx.h"
#include "GameUnitSettingsDialog.h"
#include "gui/ModelUnitTypeStatistics.h"

GameUnitSettingsDialog::GameUnitSettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent),
	OriginalName(NOT_INITIALIZED_STRING),
	ModelUnitTypeStatisticsObject(nullptr)
{
	ui.setupUi(this);

	connect(ui.pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);

	setWindowFlags(Qt::FramelessWindowHint);

	ModelUnitTypeStatisticsObject = new ModelUnitTypeStatistics(this);
	ModelUnitTypeStatisticsObject->move(20, 210);
	ModelUnitTypeStatisticsObject->show();
}

void GameUnitSettingsDialog::SetName(const QString& name)
{
	OriginalName = name;
	ui.lineEditName->setText(name);
}

void GameUnitSettingsDialog::SetStrength(const QString& strength)
{
	ui.lineEditStrength->setText(strength);
}

void GameUnitSettingsDialog::SetStrengthColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditStrength->setPalette(palette);
}

void GameUnitSettingsDialog::SetMovementPoints(const QString& movement)
{
	ui.lineEditMovementPoints->setText(movement);
}

void GameUnitSettingsDialog::SetMovementPointsColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditMovementPoints->setPalette(palette);
}

void GameUnitSettingsDialog::SetOwner(const QString& owner)
{
	ui.lineEditOwner->setText(owner);
}

void GameUnitSettingsDialog::SetOwnerColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditOwner->setPalette(palette);
}

bool GameUnitSettingsDialog::GetNameChanged() const
{
	return ui.lineEditName->text() != OriginalName;
}

QString GameUnitSettingsDialog::GetName() const
{
	return ui.lineEditName->text();
}

void GameUnitSettingsDialog::SetModelUnitType(const ModelUnitType* modelUnitType)
{
	ModelUnitTypeStatisticsObject->Fill(modelUnitType);
}

QColor GameUnitSettingsDialog::GetAdjustedTextColor(const QColor& color)
{
	if (color == Qt::blue || color == Qt::green || color == Qt::darkGreen)
	{
		return Qt::white;
	}
	return Qt::black;
}
