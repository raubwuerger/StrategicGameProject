#include "stdafx.h"
#include "GameUnitInfoDialog.h"

GameUnitInfoDialog::GameUnitInfoDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void GameUnitInfoDialog::SetMovementColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditTypeMovement->setPalette(palette);
}

void GameUnitInfoDialog::SetStrengthColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditStrength->setPalette(palette);
}

void GameUnitInfoDialog::SetOwnerColor(const QColor& color)
{
	QPalette palette;
	palette.setColor(QPalette::Base, color);
	palette.setColor(QPalette::Text, GetAdjustedTextColor(color));
	ui.lineEditOwner->setPalette(palette);
}

QColor GameUnitInfoDialog::GetAdjustedTextColor(const QColor& color)
{
	if (color == Qt::blue || color == Qt::green || color == Qt::darkGreen)
	{
		return Qt::white;
	}
	return Qt::black;
}
