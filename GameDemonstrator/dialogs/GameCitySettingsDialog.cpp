#include "stdafx.h"
#include "GameCitySettingsDialog.h"
#include "game/GameUnitProduction.h"

GameCitySettingsDialog::GameCitySettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent),
	ChangedGameUnitProduction(nullptr),
	HasProductionChanged(NOT_INITIALIZED_BOOL),
	OriginalGameUnitProduction(nullptr)
{
	ui.setupUi(this);
	connect(ui.pushButtonOk, &QPushButton::click, this, &GameCitySettingsDialog::close);
	connect(ui.pushButtonCancel, &QPushButton::click, this, &GameCitySettingsDialog::close);
	InitProductionItems();
	InitConnections();
	InitDialog();
	ChangedGameUnitProduction = new GameUnitProduction(NOT_INITIALIZED_INT);
}


void GameCitySettingsDialog::InitConnections()
{
	connect(ui.pushButtonOk, &QPushButton::clicked, this, &QDialog::accept);
	connect(ui.pushButtonCancel, &QPushButton::clicked, this, &QDialog::reject);

	connect(ui.pushButtonProduceEfficiency, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedEfficiency);

	connect(ui.pushButtonProduceInfantry, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedInfantry);
	connect(ui.pushButtonProduceTank, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedTank);
	connect(ui.pushButtonProduceArtillery, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedArtillery);
	connect(ui.pushButtonProduceFighter, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedFighter);
	connect(ui.pushButtonProduceBomber, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedBomber);
	connect(ui.pushButtonProduceDestroyer, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedDestroyer);
	connect(ui.pushButtonProduceCruiser, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedCruiser);
	connect(ui.pushButtonProduceBattleship, &QPushButton::clicked, this, &GameCitySettingsDialog::SlotButtonPressedBattleship);
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

void GameCitySettingsDialog::SetGameUnitProduction(const GameUnitProduction* gameUnitProduction)
{
	OriginalGameUnitProduction = gameUnitProduction;
	SetProductionProgress(OriginalGameUnitProduction);
}

void GameCitySettingsDialog::SetProductionHasChanged(int unitTypeId)
{
	HasProductionChanged = unitTypeId != GetOriginalUnitTypeId();
}

void GameCitySettingsDialog::SetProductionProgress(const GameUnitProduction* gameUnitProduction)
{
	ResetProductionItems();

	if (gameUnitProduction->GetGameUnitId() <= 0)
	{
		Q_ASSERT(false);
		return;
	}

	int productionItemId = CreateProductionItemId(gameUnitProduction);
	ProductionItems[productionItemId]->setValue(gameUnitProduction->GetProductionProgress());
	ProductionItems[productionItemId]->setTextVisible(true);
	ProductionItemGroups[productionItemId]->setStyleSheet("background-color:cyan;");
}

int GameCitySettingsDialog::GetOriginalUnitTypeId() const
{
	return OriginalGameUnitProduction->GetGameUnitId();
}

int GameCitySettingsDialog::CreateProductionItemId(const GameUnitProduction* gameUnitProduction) const
{
	if (gameUnitProduction->GetGameUnitId() == GAME_UNIT_ID_EFFICIENCY)
	{
		return 0;
	}
	return gameUnitProduction->GetGameUnitId();
}

void GameCitySettingsDialog::SetGameUnitProduction(int unitTypeId)
{
	if (unitTypeId == GetOriginalUnitTypeId())
	{
		this->SetProductionProgress(OriginalGameUnitProduction);
	}
	else
	{
		this->SetProductionProgress(ChangedGameUnitProduction);
	}
}

GameUnitProduction* GameCitySettingsDialog::GetGameUnitProduction() const
{
	return ChangedGameUnitProduction;
}

void GameCitySettingsDialog::SlotButtonPressedEfficiency()
{
	int idEfficiency = GAME_UNIT_ID_EFFICIENCY;
	ChangedGameUnitProduction->SetGameUnitId(idEfficiency);
	SetProductionHasChanged(idEfficiency);
	SetGameUnitProduction(idEfficiency);
}

void GameCitySettingsDialog::SlotButtonPressedInfantry()
{
	int gameUnitIdInfantry = 1;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdInfantry);
	SetProductionHasChanged(gameUnitIdInfantry);
	SetGameUnitProduction(gameUnitIdInfantry);
}

void GameCitySettingsDialog::SlotButtonPressedTank()
{
	int gameUnitIdTank = 2;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdTank);
	SetProductionHasChanged(gameUnitIdTank);
	SetGameUnitProduction(gameUnitIdTank);
}

void GameCitySettingsDialog::SlotButtonPressedArtillery()
{
	int gameUnitIdArtillery = 3;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdArtillery);
	SetProductionHasChanged(gameUnitIdArtillery);
	SetGameUnitProduction(gameUnitIdArtillery);
}

void GameCitySettingsDialog::SlotButtonPressedFighter()
{
	int gameUnitIdFighter = 4;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdFighter);
	SetProductionHasChanged(gameUnitIdFighter);
	SetGameUnitProduction(gameUnitIdFighter);
}

void GameCitySettingsDialog::SlotButtonPressedBomber()
{
	int gameUnitIdBomber = 5;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdBomber);
	SetProductionHasChanged(gameUnitIdBomber);
	SetGameUnitProduction(gameUnitIdBomber);
}

void GameCitySettingsDialog::SlotButtonPressedDestroyer()
{
	int gameUnitIdDestroyer = 6;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdDestroyer);
	SetProductionHasChanged(gameUnitIdDestroyer);
	SetGameUnitProduction(gameUnitIdDestroyer);
}

void GameCitySettingsDialog::SlotButtonPressedCruiser()
{
	int gameUnitIdCruiser = 7;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdCruiser);
	SetProductionHasChanged(gameUnitIdCruiser);
	SetGameUnitProduction(gameUnitIdCruiser);
}

void GameCitySettingsDialog::SlotButtonPressedBattleship()
{
	int gameUnitIdBattleship = 8;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdBattleship);
	SetProductionHasChanged(gameUnitIdBattleship);
	SetGameUnitProduction(gameUnitIdBattleship);
}

void GameCitySettingsDialog::SlotButtonPressedCarrier()
{
	int gameUnitIdCarrier = 9;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdCarrier);
	SetProductionHasChanged(gameUnitIdCarrier);
	SetGameUnitProduction(gameUnitIdCarrier);
}

void GameCitySettingsDialog::SlotButtonPressedSubmarine()
{
	int gameUnitIdSubmarine = 10;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdSubmarine);
	SetProductionHasChanged(gameUnitIdSubmarine);
	SetGameUnitProduction(gameUnitIdSubmarine);
}

void GameCitySettingsDialog::SlotButtonPressedTransport()
{
	int gameUnitIdTransport = 11;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdTransport);
	SetProductionHasChanged(gameUnitIdTransport);
	SetGameUnitProduction(gameUnitIdTransport);
}

void GameCitySettingsDialog::InitProductionItems()
{
	ProductionItems.push_back(ui.progressBarProgressEfficieny);
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

	ProductionItemGroups.push_back(ui.groupBoxEfficiency);
	ProductionItemGroups.push_back(ui.groupBoxInfantry);
	ProductionItemGroups.push_back(ui.groupBoxTank);
	ProductionItemGroups.push_back(ui.groupBoxArtillery);
	ProductionItemGroups.push_back(ui.groupBoxFighter);
	ProductionItemGroups.push_back(ui.groupBoxBomber);
	ProductionItemGroups.push_back(ui.groupBoxDestroyer);
	ProductionItemGroups.push_back(ui.groupBoxCruiser);
	ProductionItemGroups.push_back(ui.groupBoxBattleship);
	ProductionItemGroups.push_back(ui.groupBoxCarrier);
	ProductionItemGroups.push_back(ui.groupBoxSubmarine);
	ProductionItemGroups.push_back(ui.groupBoxTransport);
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
