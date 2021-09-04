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
//#include "model\ModelOwnerType.h"
#include "model\ModelUnitTypeRepository.h"
#include "model\ModelUnitType.h"
#include "map\MapView.h"
#include "connectors\ConnectorMapUnitItem.h"
#include "connectors\ConnectorMapCityItem.h"

GameInfoDialogController::GameInfoDialogController()
	: MapViewObject(nullptr),
	GameTurnDialogObject(nullptr),
	GameUnitInfoDialogObject(nullptr),
	GameCityInfoDialogObject(nullptr),
	GameDemonstratorObject(nullptr)
{

}

void GameInfoDialogController::Init()
{
	CreateGameTurnInfoDialog();
	CreateGameCityInfoDialog();
	CreateGameUnitInfoDialog();

	QObject::connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameInfoDialogController::SlotShowGameUnitInfo);
	QObject::connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemEntered, this, &GameInfoDialogController::SlotShowGameUnitInfo);

	QObject::connect(MapViewObject->ConnectorMapCityItemInstance, &ConnectorMapCityItem::SignalCityItemEntered, this, &GameInfoDialogController::SlotShowGameCityInfo);
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
	GameUnitInfoDialogObject->SetMovement(CreateUnitMovementPoints(gameUnit));
	GameUnitInfoDialogObject->SetStrength(CreateUnitStrength(gameUnit));
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

QString GameInfoDialogController::CreateUnitMovementPoints(const GameUnitItem* gameUnit) const
{
	QString movementPoints;
	movementPoints += QString::number(gameUnit->GetCurrentMovementPoints());
	movementPoints += " / ";
	movementPoints += QString::number(gameUnit->GetBaseMovementPoints());
	return movementPoints;
}

QString GameInfoDialogController::CreateUnitStrength(const GameUnitItem* gameUnit) const
{
	QString currentStrength;
	currentStrength += QString::number(gameUnit->GetCurrentStrength());
	currentStrength += " / ";
	currentStrength += QString::number(gameUnit->GetBaseStrength());
	return currentStrength;
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
