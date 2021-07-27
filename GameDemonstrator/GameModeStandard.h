// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 jha Exp $
//--------------------------------

#pragma once

#include "GameMode.h"

/** @stereotype Strategie*/
class GameModeStandard : public GameMode
{
public:
	/** */
	virtual void Activate();
	/** */
	virtual void Deavtivate();
};
