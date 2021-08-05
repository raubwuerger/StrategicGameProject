// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#ifndef GameModeEditor_H
#define GameModeEditor_H
#include "GameMode.h"

/** @stereotype Strategie*/
class GameModeEditor : public GameMode
{
public:
	/** */
	virtual void Activate();
	/** */
	virtual void Deavtivate();
};

#endif


