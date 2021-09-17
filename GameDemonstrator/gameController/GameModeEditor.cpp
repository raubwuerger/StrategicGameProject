// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeEditor.h"
#include "dialogs\HexItemInfoDialog.h"
#include "dialogs\UnitTypeInfoDialog.h"
#include "dialogs\CityTypeInfoDialog.h"
#include "dialogs\MapCreatorHeightMapDialog.h"
#include "map\MapView.h"
#include "map\MapHexItemEventManager.h"
#include "GameDemonstrator.h"
#include "editors\EditorToolbox.h"
#include "command\CommandCreateHeightMap.h"
#include "game\GameOwnerFactory.h"

//=================================================================================================
GameModeEditor::GameModeEditor(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
		EditorToolboxInstance(nullptr),
		HexItemInfoDialogInstance(nullptr),
		UnitTypeInfoDialogInstance(nullptr),
		CityTypeInfoDialogInstance(nullptr),
		EditorMenu(nullptr),
		MapCreatorHeightMapDialogObject(nullptr),
		MenuTitle("&Editor")
{
}

//=================================================================================================
bool GameModeEditor::DoInit()
{
	CreateMapCreatorHeightMap();
	CreateEditorMenu();
	CreateEditorToolbox();
	CreateHexItemInfoDialog();
	CreateUnitTypeInfoDialog();
	CreateCityTypeInfoDialog();

	HideDockWidgets();
	HideMenu();
	InitConnections();
	InitNecessaryGameMechanics();
	return true;
}

//=================================================================================================
void GameModeEditor::CreateEditorMenu()
{
	EditorMenu = GameDemonstratorObject->menuBar()->addMenu(MenuTitle);
}

//=================================================================================================
void GameModeEditor::Activate(int type)
{
	ShowDockWidgets();
	ShowMenu();
}

//=================================================================================================
void GameModeEditor::ShowDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->show();
	}
}

//=================================================================================================
void GameModeEditor::InitConnections()
{
	connect(MapCreatorHeightMapDialogObject, &MapCreatorHeightMapDialog::SignalGameMapCreationData, this, &GameModeEditor::SlotReceiveCreationDataHeightMap);
}

//=================================================================================================
void GameModeEditor::SlotReceiveCreationDataHeightMap(GameMapCreatorHeightMapData creationData)
{
	CommandCreateHeightMap createHeightMap;
	createHeightMap.CreateHeightMap(creationData, MapViewObject);
}

//=================================================================================================
void GameModeEditor::InitNecessaryGameMechanics()
{
	GameOwnerFactory ownerFactory;
	ownerFactory.Create();
}

//=================================================================================================
void GameModeEditor::Deactivate(int type)
{
	HideMenu();
	HideDockWidgets();
}

//=================================================================================================
void GameModeEditor::HideMenu()
{
	if (nullptr != EditorMenu)
	{
		EditorMenu->setTitle(QString(""));
	}
}

//=================================================================================================
void GameModeEditor::ShowMenu()
{
	if (nullptr != EditorMenu)
	{
		EditorMenu->setTitle(MenuTitle);
	}
}

//=================================================================================================
void GameModeEditor::HideDockWidgets()
{
	QVectorIterator<QDockWidget*> dockWidgets(DockWidgets);
	while (dockWidgets.hasNext())
	{
		dockWidgets.next()->hide();
	}
}

//=================================================================================================
void GameModeEditor::CreateEditorToolbox()
{
	if (nullptr != EditorToolboxInstance)
	{
		return;
	}
	QDockWidget *editorToolbox = new QDockWidget(tr("Editor Palette"), GameDemonstratorObject);
	editorToolbox->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	EditorToolboxInstance = new EditorToolbox(editorToolbox);
	EditorToolboxInstance->MapViewInstance = MapViewObject;
	EditorToolboxInstance->Create();

	editorToolbox->setWidget(EditorToolboxInstance);
	GameDemonstratorObject->addDockWidget(Qt::LeftDockWidgetArea, editorToolbox);

	DockWidgets.push_back(editorToolbox);
}

//=================================================================================================
void GameModeEditor::CreateHexItemInfoDialog()
{
	if (nullptr != HexItemInfoDialogInstance)
	{
		return;
	}

	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), GameDemonstratorObject);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	HexItemInfoDialogInstance = new HexItemInfoDialog(dockHexItem);

	dockHexItem->setWidget(HexItemInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockHexItem);

	EditorMenu->addAction(dockHexItem->toggleViewAction());
	MapViewObject->MapEventManagerInstance->HexItemInfoDialog = HexItemInfoDialogInstance; //TODO: Sollte das hier passieren

	DockWidgets.push_back(dockHexItem);
}

//=================================================================================================
void GameModeEditor::CreateUnitTypeInfoDialog()
{
	if (nullptr != UnitTypeInfoDialogInstance)
	{
		return;
	}

	QDockWidget *dockUnitType = new QDockWidget(tr("Unit type"), GameDemonstratorObject);
	dockUnitType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	UnitTypeInfoDialogInstance = new UnitTypeInfoDialog(dockUnitType);

	dockUnitType->setWidget(UnitTypeInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockUnitType);
	
	EditorMenu->addAction(dockUnitType->toggleViewAction());
	MapViewObject->MapEventManagerInstance->UnitTypeInfoDialog = UnitTypeInfoDialogInstance; //TODO: Sollte das hier passieren

	DockWidgets.push_back(dockUnitType);
}

//=================================================================================================
void GameModeEditor::CreateCityTypeInfoDialog()
{
	if (nullptr != CityTypeInfoDialogInstance)
	{
		return;
	}

	QDockWidget *dockCityType = new QDockWidget(tr("City type"), GameDemonstratorObject);
	dockCityType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	CityTypeInfoDialogInstance = new CityTypeInfoDialog(dockCityType);

	dockCityType->setWidget(CityTypeInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockCityType);

	EditorMenu->addAction(dockCityType->toggleViewAction());
	MapViewObject->MapEventManagerInstance->CityTypeInfoDialog = CityTypeInfoDialogInstance; //TODO: Sollte das hier passieren

	DockWidgets.push_back(dockCityType);
}

//=================================================================================================
void GameModeEditor::CreateMapCreatorHeightMap()
{
	if (nullptr != MapCreatorHeightMapDialogObject)
	{
		return;
	}

	QDockWidget *dockWidget = new QDockWidget(tr("Height Map"), GameDemonstratorObject);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea);
	MapCreatorHeightMapDialogObject = new MapCreatorHeightMapDialog(dockWidget);

	dockWidget->setWidget(MapCreatorHeightMapDialogObject);
	GameDemonstratorObject->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

	DockWidgets.push_back(dockWidget);
}
