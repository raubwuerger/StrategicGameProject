// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GAMEMODEEDITOR_H
#define GAMEMODEEDITOR_H

#include "GameMode.h"
#include "mapCreator/GameMapCreatorHeightMapData.h"

class GameDemonstrator;
class HexItemInfoDialog;
class UnitTypeInfoDialog;
class CityTypeInfoDialog;
class EditorToolbox;
class MapCreatorHeightMapDialog;

/** @stereotype Strategie*/
class GameModeEditor : public GameMode
{
public:
	/** */
	GameModeEditor(GameDemonstrator* gameDemonstrator);
	/** */
	bool DoInit() override;
public slots:
	/** */
	virtual void Activate(int type);
	/** */
	virtual void Deactivate(int type);
private:
	/** Restricted */
	GameModeEditor();
	/** */
	void CreateEditorMenu();
	/** */
	void CreateEditorToolbox();
	/** */
	void CreateHexItemInfoDialog();
	/** */
	void CreateUnitTypeInfoDialog();
	/** */
	void CreateCityTypeInfoDialog();
	/** */
	void CreateMapCreatorHeightMap();
	/** */
	void HideMenu();
	/** */
	void ShowMenu();
	/** */
	void HideDockWidgets();
	/** */
	void ShowDockWidgets();
	/** */
	void InitConnections();
	/** */
	void SlotReceiveCreationDataHeightMap(GameMapCreatorHeightMapData creationData);
private:
	EditorToolbox*				EditorToolboxInstance;
	HexItemInfoDialog*			HexItemInfoDialogInstance;
	UnitTypeInfoDialog*			UnitTypeInfoDialogInstance;
	CityTypeInfoDialog*			CityTypeInfoDialogInstance;
	MapCreatorHeightMapDialog*	MapCreatorHeightMapDialogObject;
	QMenu*						EditorMenu;
	QVector<QDockWidget*>		DockWidgets;
	const QString				MenuTitle;
};

#endif // GAMEMODEEDITOR_H


