#include "stdafx.h"
#include "GameInfoDialogController.h"
#include "dialogs\GameTurnDialog.h"
#include "dialogs\GameUnitInfoDialog.h"
#include "dialogs\GameCityInfoDialog.h"
#include "GameDemonstrator.h"
#include "game\GameUnitItem.h"
#include "game\GameUnitItemRepository.h"
#include "game\GameCityItem.h"
#include "game\GameCityItemRepository.h"
#include "game\GameOwnerItem.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "model\ModelUnitType.h"
#include "map\MapView.h"
#include "connectors\ConnectorMapUnitItem.h"
#include "connectors\ConnectorMapCityItem.h"
#include "game\GameConfig.h"
#include "dialogs\GameCitySettingsDialog.h"
#include "game\GameCityItem.h"
#include "game\GameUnitProduction.h"
#include "game\GameUnitProductionController.h"
#include "dialogs\GameUnitSettingsDialog.h"
#include "helper\ColorCreatorPercentage.h"

GameInfoDialogController::GameInfoDialogController()
	: MapViewObject(nullptr),
	GameTurnDialogObject(nullptr),
	GameUnitInfoDialogObject(nullptr),
	GameCityInfoDialogObject(nullptr),
	GameCitySettingsDialogObject(nullptr),
	GameDemonstratorObject(nullptr)
{
}

GameInfoDialogController::~GameInfoDialogController()
{
	delete GameTurnDialogObject;
	delete GameUnitInfoDialogObject;
	delete GameCityInfoDialogObject;
	delete GameCitySettingsDialogObject;
}

void GameInfoDialogController::Init()
{
	CreateGameTurnInfoDialog();
	CreateGameCityInfoDialog();
	CreateGameUnitInfoDialog();
	CreateGameCitySettingsDialog();
	CreateGameUnitSettingsDialog();

	connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameInfoDialogController::SlotShowGameUnitInfo);
	connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemEntered, this, &GameInfoDialogController::SlotShowGameUnitInfo);
	connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemDoubleClick, this, &GameInfoDialogController::SlotShowGameItemSettinsDialog);

	connect(MapViewObject->ConnectorMapCityItemInstance, &ConnectorMapCityItem::SignalCityItemEntered, this, &GameInfoDialogController::SlotShowGameCityInfo);
	connect(MapViewObject->ConnectorMapCityItemInstance, &ConnectorMapCityItem::SignalCityItemDoubleClick, this, &GameInfoDialogController::SlotShowGameCitySettingsDialog);

}

void GameInfoDialogController::ShowDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->show();
	}
}

void GameInfoDialogController::HideDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->hide();
	}
}

void GameInfoDialogController::SlotShowGameUnitInfo(int gameUnitId)
{
	GameUnitItem* gameUnit = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitId);
	if (nullptr == gameUnit)
	{
		Q_ASSERT(gameUnit);
		return;
	}

	GameUnitInfoDialogObject->SetId(QString::number(gameUnit->GetId()));
	GameUnitInfoDialogObject->SetName(gameUnit->GetName());
	GameUnitInfoDialogObject->SetType(gameUnit->GetModelUnitType()->GetName());
	GameUnitInfoDialogObject->SetMovementPoints(gameUnit->CreateMovementPointsString());
	GameUnitInfoDialogObject->SetMovementPointsColor(CreateMovementColor(gameUnit));
	GameUnitInfoDialogObject->SetStrength(gameUnit->CreatStrengthString());
	GameUnitInfoDialogObject->SetStrengthColor(CreateStrengthColor(gameUnit));
	GameUnitInfoDialogObject->SetOwner(gameUnit->GetGameOwnerItem()->GetName());
	GameUnitInfoDialogObject->SetOwnerColor(gameUnit->GetGameOwnerItem()->GetColor());
}

void GameInfoDialogController::SlotShowGameCityInfo(int gameCityId)
{
	GameCityItem* gameCity = GameCityItemRepository::GetInstance()->GetGameCityItemById(gameCityId);
	if (nullptr == gameCity)
	{
		Q_ASSERT(gameCity);
		return;
	}

	GameCityInfoDialogObject->SetId(QString::number(gameCity->GetId()));
	GameCityInfoDialogObject->SetName(gameCity->GetName());
	GameCityInfoDialogObject->SetOwner(gameCity->GetGameOwnerItem()->GetName());
	GameCityInfoDialogObject->SetOwnerColor(gameCity->GetGameOwnerItem()->GetColor());
	GameCityInfoDialogObject->SetEfficiency( CreateCityEfficiency(gameCity));
	GameCityInfoDialogObject->SetSpecialization(GetSpecializedUnitName(gameCity));
	GameCityInfoDialogObject->SetStrength(CreateCityStrength(gameCity));
	GameCityInfoDialogObject->SetProductionProgress(gameCity->GetUnitProduction()->GetProductionProgress());
	GameCityInfoDialogObject->SetProductionText(GetProducedUnitName(gameCity->GetUnitProduction()->GetGameUnitId()));
}

QString GameInfoDialogController::GetProducedUnitName(int gameUnitId) const
{
	if (gameUnitId == GAME_UNIT_ID_EFFICIENCY )
	{
		return GAME_UNIT_STRING_EFFICIENCY;
	}

	GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameUnitId);
	if (nullptr == gameUnitItem)
	{
		Q_ASSERT(gameUnitItem);
		return "???";
	}
	return gameUnitItem->GetModelUnitType()->GetName();
}

void GameInfoDialogController::SlotShowTurnInfoDialog()
{
	GameTurnDialogObject->SetGameTurn(QString::number(GameConfig::CurrentTurn));
	GameTurnDialogObject->SetPlayerName(GameConfig::Player->GetName());
	GameTurnDialogObject->SetPlayerColor(GameConfig::Player->GetColor());
}

void GameInfoDialogController::SlotShowGameCitySettingsDialog(int gameCityId)
{
	const GameCityItem* gameCity = GameCityItemRepository::GetInstance()->GetGameCityItemById(gameCityId);
	if (nullptr == gameCity)
	{
		Q_ASSERT(gameCity);
		return;
	}
	GameCitySettingsDialogObject->SetName(gameCity->GetName());
	GameCitySettingsDialogObject->SetEfficiency(QString::number(gameCity->GetCurrentEfficiency()));
	GameCitySettingsDialogObject->SetStrength(QString::number(gameCity->GetCurrentStrength()));
	GameCitySettingsDialogObject->SetSpecialization(GetUnitType(gameCity->GetSpezializedUnitTypeId()));
	GameCitySettingsDialogObject->SetGameUnitProduction(gameCity->GetUnitProduction());
	if (GameCitySettingsDialogObject->exec() == QDialog::Rejected)
	{
		return;
	}

	if (true == GameCitySettingsDialogObject->GetHaseNameChanged())
	{
		QString newName = GameCitySettingsDialogObject->GetName();
		const_cast<GameCityItem*>(gameCity)->SetName(newName);
	}

	if (false == GameCitySettingsDialogObject->GetHasProductionChanged())
	{
		return;
	}


	if (false == GameUnitProductionController::GetInstance()->UpdateGameUnitProduction(*GameCitySettingsDialogObject->GetChangedGameUnitProduction()))
	{
		Q_ASSERT(false);
	}
}

void GameInfoDialogController::SlotShowGameItemSettinsDialog(int gameItemId)
{
	const GameUnitItem* gameUnit = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(gameItemId);
	if (nullptr == gameUnit)
	{
		Q_ASSERT(gameUnit);
		return;
	}

	GameUnitSettingsDialogObject->SetName(gameUnit->GetName());
	GameUnitSettingsDialogObject->SetStrength(gameUnit->CreatStrengthString());
	GameUnitSettingsDialogObject->SetStrengthColor(CreateStrengthColor(gameUnit));
	GameUnitSettingsDialogObject->SetMovementPoints(gameUnit->CreateMovementPointsString());
	GameUnitSettingsDialogObject->SetMovementPointsColor(CreateMovementColor(gameUnit));
	GameUnitSettingsDialogObject->SetOwner(gameUnit->GetGameOwnerItem()->GetName());
	GameUnitSettingsDialogObject->SetOwnerColor(gameUnit->GetGameOwnerItem()->GetColor());
	GameUnitSettingsDialogObject->SetModelUnitType(gameUnit->GetModelUnitType());

	if (GameUnitSettingsDialogObject->exec() == QDialog::Rejected)
	{
		return;
	}

	if (true == GameUnitSettingsDialogObject->GetNameChanged())
	{
		gameUnit->SetName(GameUnitSettingsDialogObject->GetName());
	}
}

QString GameInfoDialogController::GetUnitType(int id)
{
	const ModelUnitType* unitType = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(id);
	if (nullptr == unitType)
	{
		Q_ASSERT(unitType);
		return NOT_INITIALIZED_STRING;
	}
	return unitType->GetName();
}

void GameInfoDialogController::CreateGameTurnInfoDialog()
{
	QDockWidget *dockTurnInfoDialog = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockTurnInfoDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogObject = new GameTurnDialog(dockTurnInfoDialog);
	dockTurnInfoDialog->setWidget(GameTurnDialogObject);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockTurnInfoDialog);

	DockWidgets.push_back(dockTurnInfoDialog);
}

void GameInfoDialogController::CreateGameUnitInfoDialog()
{
	QDockWidget *dockWidget = new QDockWidget(tr("Game Unit Info"), GameDemonstratorObject);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	GameUnitInfoDialogObject = new GameUnitInfoDialog(dockWidget);
	dockWidget->setWidget(GameUnitInfoDialogObject);

	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	DockWidgets.push_back(dockWidget);
}

void GameInfoDialogController::CreateGameCityInfoDialog()
{
	QDockWidget *dockWidget = new QDockWidget(tr("Game City Info"), GameDemonstratorObject);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	GameCityInfoDialogObject = new GameCityInfoDialog(dockWidget);
	dockWidget->setWidget(GameCityInfoDialogObject);

	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	DockWidgets.push_back(dockWidget);
}

void GameInfoDialogController::CreateGameCitySettingsDialog()
{
	GameCitySettingsDialogObject = new GameCitySettingsDialog();
	GameCitySettingsDialogObject->hide();
}

void GameInfoDialogController::CreateGameUnitSettingsDialog()
{
	GameUnitSettingsDialogObject = new GameUnitSettingsDialog();
	GameUnitSettingsDialogObject->hide();
}

QColor GameInfoDialogController::CreateMovementColor(const GameUnitItem* gameUnit) const
{
	return ColorCreatorPercentage::Create(static_cast<double>(gameUnit->GetCurrentMovementPoints()) / static_cast<double>(gameUnit->GetBaseMovementPoints()));
}

QColor GameInfoDialogController::CreateStrengthColor(const GameUnitItem* gameUnit) const
{
	return ColorCreatorPercentage::Create(static_cast<double>(gameUnit->GetCurrentStrength()) / static_cast<double>(gameUnit->GetBaseStrength()));
}

QString GameInfoDialogController::CreateCityEfficiency(const GameCityItem* gameCity) const
{
	QString efficiency;
	efficiency += QString::number(gameCity->GetCurrentEfficiency());
	efficiency += " / ";
	efficiency += QString::number(gameCity->GetBaseEfficiency());
	return efficiency;
}

QString GameInfoDialogController::CreateCityStrength(const GameCityItem* gameCity) const
{
	QString currentStrength;
	currentStrength += QString::number(gameCity->GetCurrentStrength());
	currentStrength += " / ";
	currentStrength += QString::number(gameCity->GetBaseStrength());
	return currentStrength;
}

QString GameInfoDialogController::GetSpecializedUnitName(const GameCityItem* gameCity)
{
	QString notSpecialized("Not specialized!");
	if (NOT_INITIALIZED_INT == gameCity->GetSpezializedUnitTypeId())
	{
		return notSpecialized;
	}
	const ModelUnitType* specialized = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(gameCity->GetSpezializedUnitTypeId());
	if (nullptr == specialized)
	{
		return notSpecialized;
	}
	return specialized->GetName();
}

