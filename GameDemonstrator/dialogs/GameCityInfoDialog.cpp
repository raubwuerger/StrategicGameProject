#include "stdafx.h"
#include "GameCityInfoDialog.h"

GameCityInfoDialog::GameCityInfoDialog(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
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
