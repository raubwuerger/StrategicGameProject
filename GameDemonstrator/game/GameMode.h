#pragma once
/** @stereotype Strategie*/
class GameMode
{
public:
	/** */
	GameMode();
	/** */
	~GameMode();
	/** */
	virtual void Activate() = 0;
	/** */
	virtual void Deavtivate() = 0;
};



