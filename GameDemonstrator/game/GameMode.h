#ifndef GAMEMODE_H
#define GAMEMODE_H

class GameDemonstrator;

/** @stereotype Strategie*/
class GameMode : public QObject
{
	Q_OBJECT
public:
	/** */
	GameMode(GameDemonstrator* gameDemonstrator);
	/** */
	~GameMode();
	/** */
	bool Init();
	/** */
	virtual void Activate() = 0;
	/** */
	virtual void Deavtivate() = 0;
protected:
	GameDemonstrator*	GameDemonstratorObject;
};

#endif // GAMEMODE_H



