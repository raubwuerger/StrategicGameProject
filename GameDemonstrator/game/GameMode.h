#ifndef GAMEMODE_H
#define GAMEMODE_H

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

#endif // GAMEMODE_H



