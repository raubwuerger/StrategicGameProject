// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#include "stdafx.h"
#include "GameModeEditor.h"
#include "dialogs\HexItemInfoDialog.h"
#include "dialogs\UnitTypeInfoDialog.h"
#include "dialogs\CityTypeInfoDialog.h"
#include "map\MapView.h"
#include "map\MapHexItemEventManager.h"
#include "GameDemonstrator.h"
#include "editors\EditorToolbox.h"

//=================================================================================================
GameModeEditor::GameModeEditor(GameDemonstrator* gameDemonstrator)
	: GameMode(gameDemonstrator),
		HexItemInfoDialogInstance(nullptr),
		UnitTypeInfoDialogInstance(nullptr),
		CityTypeInfoDialogInstance(nullptr),
		EditorMenu(nullptr)
{
	DockWidgetMinimumSize.setWidth(200);
	DockWidgetMinimumSize.setHeight(120);

	DockWidgetMaximumSize.setWidth(300);
	DockWidgetMaximumSize.setHeight(200);
}

//=================================================================================================
void GameModeEditor::CreateEditorToolbox()
{
	QDockWidget *editorToolbox = new QDockWidget(tr("Editor Palette"), GameDemonstratorObject);
	editorToolbox->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	EditorToolboxInstance = new EditorToolbox(editorToolbox);
	EditorToolboxInstance->MapViewInstance = MapViewObject;
	EditorToolboxInstance->Create();

	editorToolbox->setWidget(EditorToolboxInstance);
	GameDemonstratorObject->addDockWidget(Qt::LeftDockWidgetArea, editorToolbox);
}

//=================================================================================================
bool GameModeEditor::DoInit()
{
	HexItemInfoDialogInstance = new HexItemInfoDialog();
	UnitTypeInfoDialogInstance = new UnitTypeInfoDialog();
	CityTypeInfoDialogInstance = new CityTypeInfoDialog();
	return true;
}

//=================================================================================================
void GameModeEditor::Activate(int type)
{
	if (nullptr != EditorMenu)
	{
		return;
	}
	EditorMenu = GameDemonstratorObject->menuBar()->addMenu(tr("&Editor"));
	CreateEditorToolbox();
	CreateHexItemInfoDialog();
	CreateUnitTypeInfoDialog();
	CreateCityTypeInfoDialog();
}

//=================================================================================================
void GameModeEditor::Deactivate(int type)
{
	if(nullptr != EditorMenu)
	{
		EditorMenu->hide();
	}

	if (nullptr != EditorToolboxInstance)
	{
		EditorToolboxInstance->hide();
	}

	if (nullptr != HexItemInfoDialogInstance)
	{
		HexItemInfoDialogInstance->hide();
	}

	if (nullptr != UnitTypeInfoDialogInstance)
	{
		UnitTypeInfoDialogInstance->hide();
	}

	if (nullptr != CityTypeInfoDialogInstance)
	{
		CityTypeInfoDialogInstance->hide();
	}
}

//=================================================================================================
void GameModeEditor::CreateHexItemInfoDialog()
{
	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), GameDemonstratorObject);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	HexItemInfoDialogInstance = new HexItemInfoDialog(dockHexItem);
	HexItemInfoDialogInstance->setMinimumSize(DockWidgetMinimumSize);
	HexItemInfoDialogInstance->setMaximumSize(DockWidgetMaximumSize);

	dockHexItem->setWidget(HexItemInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockHexItem);

	EditorMenu->addAction(dockHexItem->toggleViewAction());
	MapViewObject->MapEventManagerInstance->HexItemInfoDialog = HexItemInfoDialogInstance; //TODO: Sollte das hier passieren
}

//=================================================================================================
void GameModeEditor::CreateUnitTypeInfoDialog()
{
	QDockWidget *dockUnitType = new QDockWidget(tr("Unit type"), GameDemonstratorObject);
	dockUnitType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	UnitTypeInfoDialogInstance = new UnitTypeInfoDialog(dockUnitType);
	UnitTypeInfoDialogInstance->setMinimumSize(DockWidgetMinimumSize);
	UnitTypeInfoDialogInstance->setMaximumSize(DockWidgetMaximumSize);

	dockUnitType->setWidget(UnitTypeInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockUnitType);
	
	EditorMenu->addAction(dockUnitType->toggleViewAction());
	MapViewObject->MapEventManagerInstance->UnitTypeInfoDialog = UnitTypeInfoDialogInstance; //TODO: Sollte das hier passieren
}

//=================================================================================================
void GameModeEditor::CreateCityTypeInfoDialog()
{
	QDockWidget *dockCityType = new QDockWidget(tr("City type"), GameDemonstratorObject);
	dockCityType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	CityTypeInfoDialogInstance = new CityTypeInfoDialog(dockCityType);
	CityTypeInfoDialogInstance->setMinimumSize(DockWidgetMinimumSize);
	CityTypeInfoDialogInstance->setMaximumSize(DockWidgetMaximumSize);

	dockCityType->setWidget(CityTypeInfoDialogInstance);
	GameDemonstratorObject->addDockWidget(Qt::RightDockWidgetArea, dockCityType);

	EditorMenu->addAction(dockCityType->toggleViewAction());
	MapViewObject->MapEventManagerInstance->CityTypeInfoDialog = CityTypeInfoDialogInstance; //TODO: Sollte das hier passieren
}


