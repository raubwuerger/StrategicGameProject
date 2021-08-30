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
	GameModeSinglePlayer(GameDemonstrator* gameDemonstrator);
	/** */
	virtual void Activate();
	/** */
	virtual void Deavtivate();
	/** */
	bool DoInit() override;
private:
	/** Restricted */
	GameModeSinglePlayer();
	/** */
	void CreateGameTurnInfoDialog();
	/** */
	void ShowCreateNewGameDialog();
	/** */
	void CreateNewGame(CreateNewGameDialog* dialog);
private:
	GameTurnDialog*				GameTurnDialogInstance;
};

#endif // GAMEMODESTANDARD_H
