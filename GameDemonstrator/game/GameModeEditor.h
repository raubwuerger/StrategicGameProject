// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GAMEMODEEDITOR_H
#define GAMEMODEEDITOR_H

#include "GameMode.h"

class GameDemonstrator;

/** @stereotype Strategie*/
class GameModeEditor : public GameMode
{
public:
	/** */
	GameModeEditor(GameDemonstrator* gameDemonstrator);;
public slots:
	/** */
	virtual void Activate();
	/** */
	virtual void Deavtivate();
private:
	/** Restricted */
	GameModeEditor();
};

#endif // GAMEMODEEDITOR_H


