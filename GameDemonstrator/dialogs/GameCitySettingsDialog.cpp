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
	InitConnections();
	InitDialog();
}


void GameCitySettingsDialog::InitConnections()
{
	connect(ui.pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);

	connect(ui.pushButtonProduceInfantry, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedInfantry);
	connect(ui.pushButtonProduceTank, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedTank);
	connect(ui.pushButtonProduceArtillery, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedArtillery);
	connect(ui.pushButtonProduceFighter, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedFighter);
	connect(ui.pushButtonProduceBomber, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedBomber);
	connect(ui.pushButtonProduceDestroyer, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedDestroyer);
	connect(ui.pushButtonProduceCruiser, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedCruiser);
	connect(ui.pushButtonProduceBattleshitp, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedBattleship);
	connect(ui.pushButtonProduceCarrier, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedCarrier);
	connect(ui.pushButtonProduceSubmarine, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedSubmarine);
	connect(ui.pushButtonProduceTransport, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedTransport);
}

void GameCitySettingsDialog::InitDialog()
{
	setWindowFlags(Qt::FramelessWindowHint);
	ui.lineEditEfficiency->setStyleSheet("QLineEdit { background: rgb(211, 211, 211); }");
	ui.lineEditSpecialization->setStyleSheet("QLineEdit { background: rgb(211, 211, 211); }");
	ui.lineEditStrength->setStyleSheet("QLineEdit { background: rgb(211, 211, 211); }");
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
	QString safe = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #78d,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );border-bottom-right-radius: 7px;border-bottom-left-radius: 7px;border: 1px solid black;}";
	int productionItemId = gameUnitProduction->GetGameUnitId() - 1;
	ProductionItems[productionItemId]->setValue(gameUnitProduction->GetProductionProgress());
//	ProductionItems[productionItemId]->setStyleSheet(safe);
	ProductionItems[productionItemId]->setTextVisible(true);
	ProductionItemGroups[productionItemId]->setStyleSheet("background-color:cyan;");
}

void GameCitySettingsDialog::SlotButtonPressedInfantry()
{
	emit SignalUnitProductionChanged(1);
}

void GameCitySettingsDialog::SlotButtonPressedTank()
{
	emit SignalUnitProductionChanged(2);
}

void GameCitySettingsDialog::SlotButtonPressedArtillery()
{
	emit SignalUnitProductionChanged(3);
}

void GameCitySettingsDialog::SlotButtonPressedFighter()
{
	emit SignalUnitProductionChanged(4);
}

void GameCitySettingsDialog::SlotButtonPressedBomber()
{
	emit SignalUnitProductionChanged(5);
}

void GameCitySettingsDialog::SlotButtonPressedDestroyer()
{
	emit SignalUnitProductionChanged(6);
}

void GameCitySettingsDialog::SlotButtonPressedCruiser()
{
	emit SignalUnitProductionChanged(7);
}

void GameCitySettingsDialog::SlotButtonPressedBattleship()
{
	emit SignalUnitProductionChanged(8);
}

void GameCitySettingsDialog::SlotButtonPressedCarrier()
{
	emit SignalUnitProductionChanged(9);
}

void GameCitySettingsDialog::SlotButtonPressedSubmarine()
{
	emit SignalUnitProductionChanged(10);
}

void GameCitySettingsDialog::SlotButtonPressedTransport()
{
	emit SignalUnitProductionChanged(11);
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

	ProductionItemGroups.push_back(ui.groupBoxInfantry);
	ProductionItemGroups.push_back(ui.groupBoxTank);
	ProductionItemGroups.push_back(ui.groupBoxArtillery);
	ProductionItemGroups.push_back(ui.groupBoxFighter);
	ProductionItemGroups.push_back(ui.groupBoxBomber);
	ProductionItemGroups.push_back(ui.groupBoxDestroyer);
	ProductionItemGroups.push_back(ui.groupBoxCruiser);
	ProductionItemGroups.push_back(ui.groupBoxBattleShip);
	ProductionItemGroups.push_back(ui.groupBoxCarrier);
	ProductionItemGroups.push_back(ui.groupBoxSubmarine);
	ProductionItemGroups.push_back(ui.groupBoxTransport);
	ProductionItemGroups.push_back(ui.groupBoxEfficiency);

	ProductionChange.insert(ui.pushButtonProduceInfantry, 1);
	ProductionChange.insert(ui.pushButtonProduceTank, 2);
	ProductionChange.insert(ui.pushButtonProduceArtillery, 3);
	ProductionChange.insert(ui.pushButtonProduceFighter, 4);
	ProductionChange.insert(ui.pushButtonProduceBomber, 5);
	ProductionChange.insert(ui.pushButtonProduceDestroyer, 6);
	ProductionChange.insert(ui.pushButtonProduceCruiser, 7);
	ProductionChange.insert(ui.pushButtonProduceBattleshitp, 8);
	ProductionChange.insert(ui.pushButtonProduceCarrier, 9);
	ProductionChange.insert(ui.pushButtonProduceSubmarine, 10);
	ProductionChange.insert(ui.pushButtonProduceTransport, 11);
}

void GameCitySettingsDialog::ResetProductionItems()
{
//	QString danger = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #FF0350,stop: 0.4999 #FF0020,stop: 0.5 #FF0019,stop: 1 #FF0000 );border-bottom-right-radius: 5px;border-bottom-left-radius: 5px;border: .px solid black;}";
//	QString danger = "QProgressBar::chunk {background: green}";

	QVectorIterator<QProgressBar*> iteratorProgressBar(ProductionItems);
	while (iteratorProgressBar.hasNext())
	{
		QProgressBar* current = iteratorProgressBar.next();
		current->setValue(0);
		current->setTextVisible(false);
//		iterator.next()->setStyleSheet(danger);
	}

	QVectorIterator<QGroupBox*> iteratorGroupBox(ProductionItemGroups);
	while (iteratorGroupBox.hasNext())
	{
		QGroupBox* current = iteratorGroupBox.next();
		current->setFlat(true);
		current->setStyleSheet("background-color:lightGray;");
	}
}
