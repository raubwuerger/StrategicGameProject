// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GAMEMODEEDITOR_H
#define GAMEMODEEDITOR_H

#include "GameMode.h"

class GameDemonstrator;
class HexItemInfoDialog;
class UnitTypeInfoDialog;
class CityTypeInfoDialog;
class EditorToolbox;

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
	virtual void Activate();
	/** */
	virtual void Deavtivate();
private:
	/** Restricted */
	GameModeEditor();
	/** */
	void CreateEditorToolbox();
	/** */
	void CreateHexItemInfoDialog();
	/** */
	void CreateUnitTypeInfoDialog();
	/** */
	void CreateCityTypeInfoDialog();
private:
	EditorToolbox*				EditorToolboxInstance;
	HexItemInfoDialog*			HexItemInfoDialogInstance;
	UnitTypeInfoDialog*			UnitTypeInfoDialogInstance;
	CityTypeInfoDialog*			CityTypeInfoDialogInstance;
	QMenu*						EditorMenu;
	QSize						DockWidgetMinimumSize;
	QSize						DockWidgetMaximumSize;
};

#endif // GAMEMODEEDITOR_H


