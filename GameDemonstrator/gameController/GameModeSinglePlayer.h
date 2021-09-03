// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GAMEMODESTANDARD_H
#define GAMEMODESTANDARD_H

#include "GameMode.h"

class GameDemonstrator;
class GameTurnDialog;
class CreateNewGameDialog;
class GameUnitInfoDialog;
class GameUnitItem;

/** @stereotype Strategie*/
class GameModeSinglePlayer : public GameMode
{
public:
	/** */
	bool DoInit() override;
	/** */
	GameModeSinglePlayer(GameDemonstrator* gameDemonstrator);
	/** */
	virtual void Activate(int type);
	/** */
	virtual void Deactivate(int type);
	/** */
	void LoadSaveGame();
	/** */
	void CreateNewGame();
public slots:
	/** */
	void SlotShowGameUnitInfo(int gameUnitId);
private:
	/** Restricted */
	GameModeSinglePlayer();
	/** */
	void CreateGameMenu();
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	void CreateGameUnitInfoDialog();
	/** */
	bool ShowCreateNewGameDialog();
	/** */
	bool GetGameCreationData(CreateNewGameDialog* dialog);
	/** */
	bool LoadGame( QString& savegameName);
	/** */
	void HideMenu();
	/** */
	void ShowMenu();
	/** */
	void HideDockWidgets();
	/** */
	void ShowDockWidgets();
	/** */
	void CreateMenuEntries();
	/** */
	QString CreateMovement(const GameUnitItem* gameUnit);
	/** */
	QString CreateStrength(const GameUnitItem* gameUnit);
private:
	GameTurnDialog*				GameTurnDialogObject;
	GameUnitInfoDialog*			GameUnitInfoDialogObject;
	QVector<QDockWidget*>		DockWidgets;
	const QString				MenuTitle;
	QMenu*						GameMenu;
};

#endif // GAMEMODESTANDARD_H
