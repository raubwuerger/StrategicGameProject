#include "stdafx.h"
#include "GameCitySettingsDialog.h"
#include "game/GameUnitProduction.h"

GameCitySettingsDialog::GameCitySettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.pushButtonOk, &QPushButton::click, this, &GameCitySettingsDialog::close);
	connect(ui.pushButtonCancel, &QPushButton::click, this, &GameCitySettingsDialog::close);
	InitProductionItems();
}

void GameCitySettingsDialog::SetName(const QString& name)
{
	ui.lineEditName->setText(name);
}

void GameCitySettingsDialog::SetProductionProgress(const GameUnitProduction* gameUnitProduction)
{
	ResetProductionItems();

	if (gameUnitProduction->GetGameUnitId() <= 0)
	{
		Q_ASSERT(false);
		return;
	}

	if (gameUnitProduction->GetGameUnitId() >= ProductionItems.size())
	{
		ProductionItems.last()->setValue(gameUnitProduction->GetProductionProgress());
		return;
	}
	ProductionItems[gameUnitProduction->GetGameUnitId() - 1]->setValue(gameUnitProduction->GetProductionProgress());
}

void GameCitySettingsDialog::InitProductionItems()
{
	ProductionItems.push_back(ui.progressBarProgressInfantry);
	ProductionItems.push_back(ui.progressBarProgressTank);
	ProductionItems.push_back(ui.progressBarProgressArtillery);
	ProductionItems.push_back(ui.progressBarProgressFighter);
	ProductionItems.push_back(ui.progressBarProgressBomber);
	ProductionItems.push_back(ui.progressBarProgressDestroyer);
	ProductionItems.push_back(ui.progressBarProgressCruiser);
	ProductionItems.push_back(ui.progressBarProgressBattleship);
	ProductionItems.push_back(ui.progressBarProgressCarrier);
	ProductionItems.push_back(ui.progressBarProgressSubmarine);
	ProductionItems.push_back(ui.progressBarProgressTransport);
	ProductionItems.push_back(ui.progressBarProgressEfficieny);
}

void GameCitySettingsDialog::ResetProductionItems()
{
	QVectorIterator<QProgressBar*> iterator(ProductionItems);
	while (iterator.hasNext())
	{
		iterator.next()->setValue(0);
	}
}
