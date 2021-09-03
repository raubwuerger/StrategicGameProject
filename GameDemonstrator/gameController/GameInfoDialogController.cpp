#include "stdafx.h"
#include "GameInfoDialogController.h"
#include "dialogs\GameTurnDialog.h"
#include "dialogs\GameUnitInfoDialog.h"
#include "dialogs\GameCityInfoDialog.h"
#include "GameDemonstrator.h"
#include "game\GameUnitItem.h"
#include "game\GameUnitItemRepository.h"
#include "model\ModelUnitType.h"
#include "model\ModelOwnerType.h"
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
	CreateGameUnitInfoDialog();
	QObject::connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameInfoDialogController::SlotShowGameUnitInfo);
	QObject::connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemEntered, this, &GameInfoDialogController::SlotShowGameUnitInfo);
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
	GameUnitInfoDialogObject->SetMovement(CreateMovement(gameUnit));
	GameUnitInfoDialogObject->SetStrength(CreateStrength(gameUnit));
	GameUnitInfoDialogObject->SetOwner(gameUnit->GetModelOwnerType()->GetName());
	GameUnitInfoDialogObject->SetOwnerColor(gameUnit->GetModelOwnerType()->GetColor());
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
	QDockWidget *dockGameUnitInfoDialog = new QDockWidget(tr("Game Unit Info"), GameDemonstratorObject);
	dockGameUnitInfoDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameUnitInfoDialogObject = new GameUnitInfoDialog(dockGameUnitInfoDialog);
	dockGameUnitInfoDialog->setWidget(GameUnitInfoDialogObject);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockGameUnitInfoDialog);

	DockWidgets.push_back(dockGameUnitInfoDialog);
}

QString GameInfoDialogController::CreateMovement(const GameUnitItem* gameUnit)
{
	QString movementPoints;
	movementPoints += QString::number(gameUnit->GetCurrentMovementPoints());
	movementPoints += " / ";
	movementPoints += QString::number(gameUnit->GetBaseMovementPoints());
	return movementPoints;
}

QString GameInfoDialogController::CreateStrength(const GameUnitItem* gameUnit)
{
	QString currentStrength;
	currentStrength += QString::number(gameUnit->GetCurrentStrength());
	currentStrength += " / ";
	currentStrength += QString::number(gameUnit->GetBaseStrength());
	return currentStrength;
}
