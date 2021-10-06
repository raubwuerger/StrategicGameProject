#include "stdafx.h"
#include "GameCitySettingsDialog.h"
#include "game/GameUnitProduction.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"
#include "model/ModelCityTypeRepository.h"
#include "model/ModelCityType.h"
#include "gui/ModelUnitTypeStatistics.h"
#include "game\GameUnitRepository.h"
#include "game\GameUnit.h"

static int EFFICIENCY_ID = 0;

GameCitySettingsDialog::GameCitySettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent),
	ChangedGameUnitProduction(nullptr),
	ProductionChanged(NOT_INITIALIZED_BOOL),
	OriginalGameUnitProduction(nullptr),
	NameHasChanged(NOT_INITIALIZED_BOOL),
	OriginalName(NOT_INITIALIZED_STRING),
	ModelUnitTypeStatisticsObject(nullptr)
{
	ui.setupUi(this);
	InitProductionItems();
	InitConnections();
	InitDialog();
	ModelUnitTypeStatisticsObject = new ModelUnitTypeStatistics(this);
	ModelUnitTypeStatisticsObject->move(380, 120);
	ModelUnitTypeStatisticsObject->show();
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

	connect(ui.lineEditName, &QLineEdit::textEdited, this, &GameCitySettingsDialog::SlotNameEdited);
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
	OriginalName = name;
	ui.lineEditName->setText(name);
}

const QString GameCitySettingsDialog::GetName() const
{
	return ui.lineEditName->text();
}

void GameCitySettingsDialog::SetGameUnitProduction(const GameUnitProduction* gameUnitProduction)
{
	NameHasChanged = false;
	ProductionChanged = false;
	OriginalGameUnitProduction = gameUnitProduction;
	ChangedGameUnitProduction = new GameUnitProduction(gameUnitProduction->GetGameCityId());
	SetProductionProgress(OriginalGameUnitProduction);
	if (MODEL_UNIT_ID_EFFICIENCY == gameUnitProduction->GetModelTypeId())
	{
		SetEfficiencyIcon();
	}
	else
	{
		ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(gameUnitProduction->GetModelTypeId()));
	}
}

void GameCitySettingsDialog::SetProductionHasChanged(int unitTypeId)
{
	ProductionChanged = unitTypeId != GetOriginalUnitTypeId();
}

void GameCitySettingsDialog::SetProductionProgress(const GameUnitProduction* gameUnitProduction)
{
	ResetProductionItems();

	if (gameUnitProduction->GetModelTypeId() <= 0)
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
	return OriginalGameUnitProduction->GetModelTypeId();
}

int GameCitySettingsDialog::CreateProductionItemId(const GameUnitProduction* gameUnitProduction) const
{
	if (gameUnitProduction->GetModelTypeId() == MODEL_UNIT_ID_EFFICIENCY)
	{
		return EFFICIENCY_ID;
	}
	return gameUnitProduction->GetModelTypeId();
}


const QString& GameCitySettingsDialog::GetImagePathFromUnitItem(int unitTypeId) const
{
	const ModelUnitType* type = ModelUnitTypeRepository::GetInstance()->GetById(unitTypeId);
	Q_ASSERT(type);
	return type->GetPictureName();
}

const QString& GameCitySettingsDialog::GetImagePathFromCityItem() const
{
	const ModelCityType* type = ModelCityTypeRepository::GetInstance()->GetById(1);
	Q_ASSERT(type);
	return type->GetPictureName();
}

void GameCitySettingsDialog::SetNameHasChanged()
{
	NameHasChanged = ui.lineEditName->text() != OriginalName;
}

void GameCitySettingsDialog::SetEfficiencyIcon()
{
	ModelUnitTypeStatisticsObject->Clear();
	ModelUnitTypeStatisticsObject->LabelUnitImage->setPixmap(QPixmap(GetImagePathFromCityItem()));
	ModelUnitTypeStatisticsObject->LineEditUnitProductionCost->setText(QString::number(100)); //TODO: Sollte ein property von ModelCityItem sein!
	ModelUnitTypeStatisticsObject->LineEditUnitStrength->setText(QString::number(10));	//TODO: Sollte ein property von ModelCityItem sein!
}

const ModelUnitType* GameCitySettingsDialog::GetModelUnitType(int unitTypeId) const
{
	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->GetById(unitTypeId);
	Q_ASSERT(modelUnitType);
	return modelUnitType;
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

GameUnitProduction* GameCitySettingsDialog::GetChangedGameUnitProduction() const
{
	return ChangedGameUnitProduction;
}

void GameCitySettingsDialog::accept()
{
	SetNameHasChanged();
	this->done(1);
}

void GameCitySettingsDialog::SlotButtonPressedEfficiency()
{
	int idEfficiency = MODEL_UNIT_ID_EFFICIENCY;
	ChangedGameUnitProduction->SetModelTypeId(idEfficiency);
	SetProductionHasChanged(idEfficiency);
	SetGameUnitProduction(idEfficiency);
	ModelUnitTypeStatisticsObject->Clear();
	SetEfficiencyIcon();
}

void GameCitySettingsDialog::SlotButtonPressedInfantry()
{
	int unitTypeId = 1;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedTank()
{
	int unitTypeId = 2;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedArtillery()
{
	int unitTypeId = 3;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedFighter()
{
	int unitTypeId = 4;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedBomber()
{
	int unitTypeId = 5;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedDestroyer()
{
	int unitTypeId = 6;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedCruiser()
{
	int unitTypeId = 7;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedBattleship()
{
	int unitTypeId = 8;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedCarrier()
{
	int unitTypeId = 9;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedSubmarine()
{
	int unitTypeId = 10;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedTransport()
{
	int unitTypeId = 11;
	ChangedGameUnitProduction->SetModelTypeId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	ModelUnitTypeStatisticsObject->Fill(GetModelUnitType(unitTypeId));
}

void GameCitySettingsDialog::SlotNameEdited(const QString & text)
{
	NameHasChanged = true;
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
	QVectorIterator<QProgressBar*> iteratorProgressBar(ProductionItems);
	while (iteratorProgressBar.hasNext())
	{
		QProgressBar* current = iteratorProgressBar.next();
		current->setValue(0);
		current->setTextVisible(false);
	}

	QVectorIterator<QGroupBox*> iteratorGroupBox(ProductionItemGroups);
	while (iteratorGroupBox.hasNext())
	{
		QGroupBox* current = iteratorGroupBox.next();
		current->setFlat(true);
		current->setStyleSheet("background-color:lightGray;");
	}
}
