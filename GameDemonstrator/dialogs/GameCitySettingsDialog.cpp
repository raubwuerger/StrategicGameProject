#include "stdafx.h"
#include "GameCitySettingsDialog.h"
#include "game/GameUnitProduction.h"
#include "model/ModelUnitTypeRepository.h"
#include "model/ModelUnitType.h"
#include "model/ModelCityTypeRepository.h"
#include "model/ModelCityType.h"

static int EFFICIENCY_ID = 0;

GameCitySettingsDialog::GameCitySettingsDialog(QWidget *parent /*= 0*/)
	: QDialog(parent),
	ChangedGameUnitProduction(nullptr),
	ProductionChanged(NOT_INITIALIZED_BOOL),
	OriginalGameUnitProduction(nullptr),
	NameHasChanged(NOT_INITIALIZED_BOOL),
	OriginalName(NOT_INITIALIZED_STRING)
{
	ui.setupUi(this);
	connect(ui.pushButtonOk, &QPushButton::click, this, &GameCitySettingsDialog::close);
	connect(ui.pushButtonCancel, &QPushButton::click, this, &GameCitySettingsDialog::close);
	InitProductionItems();
	InitConnections();
	InitDialog();
	CreateModelUnitTypeStatsWidget();
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
	OriginalGameUnitProduction = gameUnitProduction;
	ChangedGameUnitProduction = new GameUnitProduction(gameUnitProduction->GetGameCityId());
	SetProductionProgress(OriginalGameUnitProduction);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(gameUnitProduction->GetGameUnitId()));
}

void GameCitySettingsDialog::SetProductionHasChanged(int unitTypeId)
{
	ProductionChanged = unitTypeId != GetOriginalUnitTypeId();
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
		return EFFICIENCY_ID;
	}
	return gameUnitProduction->GetGameUnitId();
}


const QString& GameCitySettingsDialog::GetImagePathFromUnitItem(int unitTypeId) const
{
	const ModelUnitType* type = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(unitTypeId);
	Q_ASSERT(type);
	return type->GetPictureName();
}

const QString& GameCitySettingsDialog::GetImagePathFromCityItem() const
{
	const ModelCityType* type = ModelCityTypeRepository::GetInstance()->GetTypeById(1);
	Q_ASSERT(type);
	return type->GetPictureName();
}

void GameCitySettingsDialog::SetNameHasChanged()
{
	NameHasChanged = ui.lineEditName->text() != OriginalName;
}

void GameCitySettingsDialog::SetEfficiencyIcon()
{
	ClearModelUnitTypeStatsWidget();
	LabelUnitImage->setPixmap(QPixmap(GetImagePathFromCityItem()));
	LineEditUnitProductionCost->setText(QString::number(100)); //TODO: Sollte ein property von ModelCityItem sein!
	LineEditUnitStrength->setText(QString::number(10));	//TODO: Sollte ein property von ModelCityItem sein!
}

#include "game\GameUnitItemRepository.h"
#include "game\GameUnitItem.h"
const ModelUnitType* GameCitySettingsDialog::GetModelUnitTypeFromGameUnitId(int gameUnitId) const
{
	const GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitId);
	if (nullptr == gameUnitItem)
	{
		Q_ASSERT(gameUnitItem);
		return nullptr;
	}

	const ModelUnitType* modelUnitType = gameUnitItem->GetModelUnitType();
	Q_ASSERT(modelUnitType);
	return modelUnitType;
}

void GameCitySettingsDialog::FillModelUnitTypeStatsWidget(const ModelUnitType* modelUnitType)
{
	Q_ASSERT(modelUnitType);
	LabelUnitImage->setPixmap(QPixmap(modelUnitType->GetPictureName()));
	LineEditUnitType->setText(modelUnitType->GetName());
	LineEditUnitProductionCost->setText(QString::number(modelUnitType->GetProductionCost()));
	LineEditUnitMovementPoints->setText(QString::number(modelUnitType->GetMovementPoints()));
	LineEditUnitStrength->setText(QString::number(modelUnitType->GetStrength()));
	LineEditUnitRange->setText(QString::number(modelUnitType->GetRange()));
	CheckBoxUnitOccupyCity->setCheckState(modelUnitType->GetCanOccupieCity() ? Qt::Checked : Qt::Unchecked);
	CheckBoxUnitGetCounterAttack->setCheckState(modelUnitType->GetReceiveCounterattack() ? Qt::Checked : Qt::Unchecked);
}

void GameCitySettingsDialog::ClearModelUnitTypeStatsWidget()
{
	QString clear("---");
	LabelUnitImage->setPixmap(QPixmap());
	LineEditUnitType->setText(clear);
	LineEditUnitProductionCost->setText(clear);
	LineEditUnitMovementPoints->setText(clear);
	LineEditUnitStrength->setText(clear);
	LineEditUnitRange->setText(clear);
	CheckBoxUnitOccupyCity->setCheckState(Qt::Unchecked);
	CheckBoxUnitGetCounterAttack->setCheckState(Qt::Unchecked);
}

void GameCitySettingsDialog::CreateModelUnitTypeStatsWidget()
{
	GridLayoutUnitStatistics = new QGridLayout;
	LabelUnitImage = new QLabel();
	QPixmap unitPixmap;
	LabelUnitImage->setPixmap(unitPixmap);

	LabelUnitType = new QLabel("Unit type:");
	LineEditUnitType = new QLineEdit();
	LineEditUnitType->setEnabled(false);

	LabelProductionCost = new QLabel("Production cost:");
	LineEditUnitProductionCost = new QLineEdit();
	LineEditUnitProductionCost->setEnabled(false);

	LabelMovementPoints = new QLabel("Movement points:");
	LineEditUnitMovementPoints = new QLineEdit();
	LineEditUnitMovementPoints->setEnabled(false);

	LabelStrength = new QLabel("Strength:");
	LineEditUnitStrength = new QLineEdit();
	LineEditUnitStrength->setEnabled(false);

	LabelRange = new QLabel("Range:");
	LineEditUnitRange = new QLineEdit();
	LineEditUnitRange->setEnabled(false);

	LabelOccupyCity = new QLabel("Occupy city:");
	CheckBoxUnitOccupyCity = new QCheckBox();
	CheckBoxUnitOccupyCity->setEnabled(false);

	LabelCounterattack = new QLabel("Counterattack:");
	CheckBoxUnitGetCounterAttack = new QCheckBox();
	CheckBoxUnitGetCounterAttack->setEnabled(false);

	int rowIndex = 0;
	GridLayoutUnitStatistics->addWidget(LabelUnitImage, 0, 0);

	GridLayoutUnitStatistics->addWidget(LabelUnitType, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitType, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelProductionCost, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitProductionCost, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelMovementPoints, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitMovementPoints, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelStrength, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitStrength, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelRange, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(LineEditUnitRange, rowIndex, 2, 1, 2);

	GridLayoutUnitStatistics->addWidget(LabelOccupyCity, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(CheckBoxUnitOccupyCity, rowIndex, 2);

	GridLayoutUnitStatistics->addWidget(LabelCounterattack, ++rowIndex, 0, 1, 2);
	GridLayoutUnitStatistics->addWidget(CheckBoxUnitGetCounterAttack, rowIndex, 2);

	ui.groupBoxProductionStats->setLayout(GridLayoutUnitStatistics);
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
	int idEfficiency = GAME_UNIT_ID_EFFICIENCY;
	ChangedGameUnitProduction->SetGameUnitId(idEfficiency);
	SetProductionHasChanged(idEfficiency);
	SetGameUnitProduction(idEfficiency);
	ClearModelUnitTypeStatsWidget();
	SetEfficiencyIcon();
}

void GameCitySettingsDialog::SlotButtonPressedInfantry()
{
	int unitTypeId = 1;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedTank()
{
	int unitTypeId = 2;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedArtillery()
{
	int unitTypeId = 3;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedFighter()
{
	int unitTypeId = 4;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedBomber()
{
	int unitTypeId = 5;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedDestroyer()
{
	int unitTypeId = 6;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedCruiser()
{
	int unitTypeId = 7;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedBattleship()
{
	int unitTypeId = 8;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedCarrier()
{
	int unitTypeId = 9;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedSubmarine()
{
	int unitTypeId = 10;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
}

void GameCitySettingsDialog::SlotButtonPressedTransport()
{
	int unitTypeId = 11;
	ChangedGameUnitProduction->SetGameUnitId(unitTypeId);
	SetProductionHasChanged(unitTypeId);
	SetGameUnitProduction(unitTypeId);
	FillModelUnitTypeStatsWidget(GetModelUnitTypeFromGameUnitId(unitTypeId));
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
