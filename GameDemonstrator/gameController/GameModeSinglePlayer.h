// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GAMEMODESTANDARD_H
#define GAMEMODESTANDARD_H

#include "GameMode.h"

class GameDemonstrator;
class GameTurnDialog;
class CreateNewGameDialog;

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
	void LoadGame();
private:
	/** Restricted */
	GameModeSinglePlayer();
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	bool ShowCreateNewGameDialog();
	/** */
	bool CreateNewGame(CreateNewGameDialog* dialog);
	/** */
	bool LoadSaveGame( QString& savegameName);
	/** */
	void ShowGameTurnInfoDialog();
private:
	GameTurnDialog*				GameTurnDialogInstance;
};

#endif // GAMEMODESTANDARD_H
