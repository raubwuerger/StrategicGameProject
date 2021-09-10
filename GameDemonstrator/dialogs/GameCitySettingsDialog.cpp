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
	CreateUnitStatsWidget();
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
	ShowProductionItem(CreateProductionItemId(gameUnitProduction));
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

void GameCitySettingsDialog::ShowProductionItem(int unitTypeId)
{
	QString imagePath;
	if (unitTypeId == GAME_UNIT_ID_EFFICIENCY || unitTypeId == EFFICIENCY_ID)
	{
		imagePath = GetImagePathFromCityItem();
	}
	else
	{
		imagePath = GetImagePathFromUnitItem(unitTypeId);
	}
	QIcon untitIcon(imagePath);
	ui.pushButtonUnitImage->setIcon(untitIcon);
	ui.pushButtonUnitImage->setIconSize(QSize(64, 64));
}

const QString& GameCitySettingsDialog::GetImagePathFromUnitItem(int unitTypeId)
{
	const ModelUnitType* type = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(unitTypeId);
	Q_ASSERT(type);
	return type->GetPictureName();
}

const QString& GameCitySettingsDialog::GetImagePathFromCityItem()
{
	const ModelCityType* type = ModelCityTypeRepository::GetInstance()->GetTypeById(1);
	Q_ASSERT(type);
	return type->GetPictureName();
}

void GameCitySettingsDialog::SetNameHasChanged()
{
	NameHasChanged = ui.lineEditName->text() != OriginalName;
}

void GameCitySettingsDialog::CreateUnitStatsWidget()
{
	ShowProductionItem(1,ui.gridLayoutUnitStats);
	int rowIndex = 0;
	ui.gridLayoutUnitStats->addWidget(new QLabel("Name:"), ++rowIndex, 0);
	QLineEdit* lineEditName = new QLineEdit("Infantry");
	lineEditName->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(lineEditName, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(new QLabel("Strength:"), ++rowIndex, 0);
	QLineEdit* lineEditStrength = new QLineEdit();
	lineEditStrength->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(lineEditStrength, rowIndex, 1);
	ui.gridLayoutUnitStats->addWidget(new QLabel("Production costs:"), rowIndex, 2);
	QLineEdit* lineEditCost = new QLineEdit();
	lineEditCost->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(lineEditCost, rowIndex, 3);

	ui.gridLayoutUnitStats->addWidget(new QLabel("Range:"), ++rowIndex, 0);
	QLineEdit* lineEditRange = new QLineEdit();
	lineEditRange->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(lineEditRange, rowIndex, 1);
	ui.gridLayoutUnitStats->addWidget(new QLabel("Movement points:"), rowIndex, 2);
	QLineEdit* lineEditMovement = new QLineEdit();
	lineEditMovement->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(lineEditMovement, rowIndex, 3);

	ui.gridLayoutUnitStats->addWidget(new QLabel("Occupy city:"), ++rowIndex, 0);
	QCheckBox* occupyCity = new QCheckBox("");
	occupyCity->setEnabled(false);
	occupyCity->setCheckState(Qt::Checked);
	ui.gridLayoutUnitStats->addWidget(occupyCity, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(new QLabel("Counterattack:"), rowIndex, 2);
	QCheckBox* counterAttack = new QCheckBox("");
	counterAttack->setCheckState(Qt::Checked);
	counterAttack->setEnabled(false);
	ui.gridLayoutUnitStats->addWidget(counterAttack, rowIndex, 3);

	QLabel* labelTerrainType1 = new QLabel("Plains:");
	QCheckBox* terrainType1 = new QCheckBox();
	terrainType1->setChecked(true);
	terrainType1->setEnabled(false);

	QLabel* labelTerrainType2 = new QLabel("Woods:");
	QCheckBox* terrainType2 = new QCheckBox();
	terrainType2->setChecked(true);
	terrainType2->setEnabled(false);

	QLabel* labelTerrainType3 = new QLabel("Ocean:");
	QCheckBox* terrainType3 = new QCheckBox();
	terrainType3->setEnabled(false);

	QLabel* labelTerrainType4 = new QLabel("Hills:");
	QCheckBox* terrainType4 = new QCheckBox();
	terrainType4->setChecked(true);
	terrainType4->setEnabled(false);

	QLabel* labelTerrainType5 = new QLabel("Mountains:");
	QCheckBox* terrainType5 = new QCheckBox();
	terrainType5->setChecked(true);
	terrainType5->setEnabled(false);

	QLabel* labelTerrainType6 = new QLabel("Mountains 1:");
	QCheckBox* terrainType6 = new QCheckBox();
	terrainType6->setChecked(true);
	terrainType6->setEnabled(false);

	QLabel* labelTerrainType7 = new QLabel("Mountains 2:");
	QCheckBox* terrainType7 = new QCheckBox();
	terrainType7->setChecked(true);
	terrainType7->setEnabled(false);

	QLabel* labelTerrainType8 = new QLabel("Mountains 3:");
	QCheckBox* terrainType8 = new QCheckBox();
	terrainType8->setChecked(true);
	terrainType8->setEnabled(false);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType1, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType1, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType2, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType2, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType3, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType3, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType4, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType4, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType5, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType5, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType6, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType6, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType7, ++rowIndex, 0);
	ui.gridLayoutUnitStats->addWidget(terrainType7, rowIndex, 1);

	ui.gridLayoutUnitStats->addWidget(labelTerrainType8, ++rowIndex, 0, 2, 0 );
	ui.gridLayoutUnitStats->addWidget(terrainType8, rowIndex, 1, 2, 0 );
}

void GameCitySettingsDialog::ShowProductionItem(int unitTypeId, QGridLayout* layout)
{
	QString imagePath;
	if (unitTypeId == GAME_UNIT_ID_EFFICIENCY || unitTypeId == EFFICIENCY_ID)
	{
		imagePath = GetImagePathFromCityItem();
	}
	else
	{
		imagePath = GetImagePathFromUnitItem(unitTypeId);
	}
	QLabel* unitLabel = new QLabel();
	QPixmap unitPixmap(imagePath);
	unitLabel->setPixmap(unitPixmap);
	layout->addWidget(unitLabel, 0, 0);
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
	ShowProductionItem(idEfficiency);
}

void GameCitySettingsDialog::SlotButtonPressedInfantry()
{
	int gameUnitIdInfantry = 1;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdInfantry);
	SetProductionHasChanged(gameUnitIdInfantry);
	SetGameUnitProduction(gameUnitIdInfantry);
	ShowProductionItem(gameUnitIdInfantry);
}

void GameCitySettingsDialog::SlotButtonPressedTank()
{
	int gameUnitIdTank = 2;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdTank);
	SetProductionHasChanged(gameUnitIdTank);
	SetGameUnitProduction(gameUnitIdTank);
	ShowProductionItem(gameUnitIdTank);
}

void GameCitySettingsDialog::SlotButtonPressedArtillery()
{
	int gameUnitIdArtillery = 3;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdArtillery);
	SetProductionHasChanged(gameUnitIdArtillery);
	SetGameUnitProduction(gameUnitIdArtillery);
	ShowProductionItem(gameUnitIdArtillery);
}

void GameCitySettingsDialog::SlotButtonPressedFighter()
{
	int gameUnitIdFighter = 4;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdFighter);
	SetProductionHasChanged(gameUnitIdFighter);
	SetGameUnitProduction(gameUnitIdFighter);
	ShowProductionItem(gameUnitIdFighter);
}

void GameCitySettingsDialog::SlotButtonPressedBomber()
{
	int gameUnitIdBomber = 5;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdBomber);
	SetProductionHasChanged(gameUnitIdBomber);
	SetGameUnitProduction(gameUnitIdBomber);
	ShowProductionItem(gameUnitIdBomber);
}

void GameCitySettingsDialog::SlotButtonPressedDestroyer()
{
	int gameUnitIdDestroyer = 6;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdDestroyer);
	SetProductionHasChanged(gameUnitIdDestroyer);
	SetGameUnitProduction(gameUnitIdDestroyer);
	ShowProductionItem(gameUnitIdDestroyer);
}

void GameCitySettingsDialog::SlotButtonPressedCruiser()
{
	int gameUnitIdCruiser = 7;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdCruiser);
	SetProductionHasChanged(gameUnitIdCruiser);
	SetGameUnitProduction(gameUnitIdCruiser);
	ShowProductionItem(gameUnitIdCruiser);
}

void GameCitySettingsDialog::SlotButtonPressedBattleship()
{
	int gameUnitIdBattleship = 8;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdBattleship);
	SetProductionHasChanged(gameUnitIdBattleship);
	SetGameUnitProduction(gameUnitIdBattleship);
	ShowProductionItem(gameUnitIdBattleship);
}

void GameCitySettingsDialog::SlotButtonPressedCarrier()
{
	int gameUnitIdCarrier = 9;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdCarrier);
	SetProductionHasChanged(gameUnitIdCarrier);
	SetGameUnitProduction(gameUnitIdCarrier);
	ShowProductionItem(gameUnitIdCarrier);
}

void GameCitySettingsDialog::SlotButtonPressedSubmarine()
{
	int gameUnitIdSubmarine = 10;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdSubmarine);
	SetProductionHasChanged(gameUnitIdSubmarine);
	SetGameUnitProduction(gameUnitIdSubmarine);
	ShowProductionItem(gameUnitIdSubmarine);
}

void GameCitySettingsDialog::SlotButtonPressedTransport()
{
	int gameUnitIdTransport = 11;
	ChangedGameUnitProduction->SetGameUnitId(gameUnitIdTransport);
	SetProductionHasChanged(gameUnitIdTransport);
	SetGameUnitProduction(gameUnitIdTransport);
	ShowProductionItem(gameUnitIdTransport);
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
