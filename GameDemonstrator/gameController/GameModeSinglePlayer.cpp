// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeSinglePlayer.h"
#include "dialogs\GameTurnDialog.h"
#include "dialogs\GameUnitInfoDialog.h"
#include "GameDemonstrator.h"
#include "dialogs/CreateNewGameDialog.h"
#include "ActionRepository.h"
#include "GameFactory.h"
#include "GameConfig.h"
#include "map\MapHexItemFactory.h"
#include "map\MapUnitItemFactory.h"
#include "map\MapCityItemFactory.h"
#include "model\ModelOwnerTypeRepository.h"
#include "map\MapView.h"
#include "connectors\ConnectorMapUnitItem.h"

//=================================================================================================
GameModeSinglePlayer::GameModeSinglePlayer(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
	GameTurnDialogObject(nullptr),
	GameUnitInfoDialogObject(nullptr),
	GameMenu(nullptr),
	MenuTitle("&Game")
{

}

//=================================================================================================
bool GameModeSinglePlayer::DoInit()
{
	CreateGameTurnInfoDialog();
	CreateGameUnitInfoDialog();
	CreateGameMenu();
	CreateMenuEntries();

	HideDockWidgets();
	HideMenu();

	QObject::connect(MapViewObject->ConnectorMapUnitItemInstance, &ConnectorMapUnitItem::SignalUnitItemPressedLeftButton, this, &GameModeSinglePlayer::SlotShowGameUnitInfo);

	return true;
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameMenu()
{
	GameMenu = GameDemonstratorObject->menuBar()->addMenu(MenuTitle);
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameTurnInfoDialog()
{
	QDockWidget *dockTurnInfoDialog = new QDockWidget(tr("Game turn"), GameDemonstratorObject);
	dockTurnInfoDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameTurnDialogObject = new GameTurnDialog(dockTurnInfoDialog);
	dockTurnInfoDialog->setWidget(GameTurnDialogObject);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockTurnInfoDialog);

	DockWidgets.push_back(dockTurnInfoDialog);
}

//=================================================================================================
void GameModeSinglePlayer::CreateGameUnitInfoDialog()
{
	QDockWidget *dockGameUnitInfoDialog = new QDockWidget(tr("Game Unit Info"), GameDemonstratorObject);
	dockGameUnitInfoDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	GameUnitInfoDialogObject = new GameUnitInfoDialog(dockGameUnitInfoDialog);
	dockGameUnitInfoDialog->setWidget(GameUnitInfoDialogObject);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockGameUnitInfoDialog);

	DockWidgets.push_back(dockGameUnitInfoDialog);
}

//=================================================================================================
void GameModeSinglePlayer::Activate(int type)
{
	ShowDockWidgets();
	ShowMenu();
}

//=================================================================================================
void GameModeSinglePlayer::Deactivate(int type)
{
	HideMenu();
	HideDockWidgets();
}

//=================================================================================================
void GameModeSinglePlayer::ShowMenu()
{
	if (nullptr != GameMenu)
	{
		GameMenu->setTitle(MenuTitle);
	}
}

//=================================================================================================
void GameModeSinglePlayer::HideMenu()
{
	if (nullptr != GameMenu)
	{
		GameMenu->setTitle(QString(""));
	}
}

//=================================================================================================
void GameModeSinglePlayer::ShowDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->show();
	}
}

//=================================================================================================
void GameModeSinglePlayer::CreateMenuEntries()
{
	QIcon next(QPixmap(".//Resources//media_end.ico"));
	QAction* nextTurnAction = new QAction(next, tr("&Next turn"), this);
	nextTurnAction->setStatusTip(tr("Next turn"));
//	connect(nextTurnAction, &QAction::triggered, MainGameLoopInstance, &GameMainLoop::SlotStep, Qt::QueuedConnection);
	GameMenu->addAction(nextTurnAction);
	ActionRepository::GetInstance()->AddAction(nextTurnAction);
}

//=================================================================================================
void GameModeSinglePlayer::HideDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->hide();
	}
}

//=================================================================================================
void GameModeSinglePlayer::LoadSaveGame()
{
	QString savegameName;
	if (false == LoadGame(savegameName))
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
	CreateGameTurnInfoDialog();
}

//=================================================================================================
bool GameModeSinglePlayer::ShowCreateNewGameDialog()
{
	CreateNewGameDialog* dialog = new CreateNewGameDialog();
	if (QDialog::Accepted == dialog->exec())
	{
		GetGameCreationData(dialog);
		return true;
	}
	return false;
}

//=================================================================================================
bool GameModeSinglePlayer::GetGameCreationData(CreateNewGameDialog* dialog)
{
	int rows = dialog->GetTilesRows();
	int cols = dialog->GetTilesCols();

	int owner = dialog->GetOwnerTypeId();
	int opponents = dialog->GetOpponentCount();
	int diffuclty = dialog->GetDifficultyLevel();

	GameConfig::MapRows = rows;
	GameConfig::MapCols = cols;
	GameConfig::OwnerType = const_cast<ModelOwnerType*>(ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(owner));

	GameFactory gameFactory;
	gameFactory.Create();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	return false;
}

//=================================================================================================
void GameModeSinglePlayer::CreateNewGame()
{
	if (false == ShowCreateNewGameDialog())
	{
		GameDemonstratorObject->ShowGameMainDialog();
		return;
	}
}
//=================================================================================================
bool GameModeSinglePlayer::LoadGame(QString& savegameName)
{
	savegameName = QFileDialog::getOpenFileName(GameDemonstratorObject, tr("Open Save Game"), "./savegames", tr("Savegame files (*.xml )"));
	if (true == savegameName.isNull())
	{
		return false;
	}

	GameConfig::CurrentSaveGameName = savegameName;

	GameFactory gameFactory;
	gameFactory.CreateFromSavegame();

	MapHexItemFactory mapHexItemFactory;
	mapHexItemFactory.Create(MapViewObject);

	MapUnitItemFactory mapUnitItemFactory;
	mapUnitItemFactory.Create(MapViewObject);

	MapCityItemFactory mapCityItemFactory;
	mapCityItemFactory.Create(MapViewObject);

	return true;
}


#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"
#include "model/ModelUnitType.h"
//=================================================================================================
void GameModeSinglePlayer::SlotShowGameUnitInfo(int gameUnitId)
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
}

//=================================================================================================
QString GameModeSinglePlayer::CreateMovement(const GameUnitItem* gameUnit)
{
	QString movementPoints;
	movementPoints += QString::number(gameUnit->GetCurrentMovementPoints());
	movementPoints += " / ";
	movementPoints += QString::number(gameUnit->GetBaseMovementPoints());
	return movementPoints;
}

//=================================================================================================
QString GameModeSinglePlayer::CreateStrength(const GameUnitItem* gameUnit)
{
	QString currentStrength;
	currentStrength += QString::number(gameUnit->GetCurrentStrength());
	currentStrength += " / ";
	currentStrength += QString::number(gameUnit->GetBaseStrength());
	return currentStrength;
}

