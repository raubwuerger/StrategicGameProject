#ifndef GAMEMODE_H
#define GAMEMODE_H

class GameDemonstrator;
class MapView;

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
	virtual void Activate( int type ) = 0;
	/** */
	virtual void Deactivate(int type ) = 0;
private:
	/** */
	virtual bool DoInit() = 0;
protected:
	friend class GameModeController;
	GameDemonstrator*	GameDemonstratorObject;
	MapView*			MapViewObject;
};

#endif // GAMEMODE_H



