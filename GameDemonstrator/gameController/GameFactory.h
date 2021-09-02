#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

class GameConfig;
class GameController;
class GameModeController;
class MapView;
class GameMainDialog;

/* Creates the hole game. From scratch or from savegame. */
class GameFactory
{
public:
	/** */
	GameFactory();
	/** */
	bool Create();
	/** */
	bool CreateFromSavegame();
private:
	/** */
	void InitGameController();
	/** */
	void InitGameModeController();
private:
	friend class GameDemonstrator;
	static GameController*		GameControllerObject;
	static GameModeController*	GameModeControllerObject;
	static GameDemonstrator*	GameDemonstratorObject;
	static MapView*				MapViewObject;
	static GameMainDialog*		GameMainDialogObject;
};

#endif // GAMEFACTORY_H