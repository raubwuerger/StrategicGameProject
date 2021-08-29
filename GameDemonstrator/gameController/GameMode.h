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
	virtual void Activate() = 0;
	/** */
	virtual void Deavtivate() = 0;
private:
	/** */
	virtual bool DoInit() = 0;
	/** */
	void CreateGameModeChangeMenu();
	/** */
	void CreateMenuEntryEditor();
	/** */
	void CreateMenuEntrySinglePlayer();
protected:
	friend class GameDemonstrator;
	GameDemonstrator*	GameDemonstratorObject;
	MapView*			MapViewObject;
	static QMenu*		GameModeChangeMenu;
};

#endif // GAMEMODE_H



