#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

class GameConfig;
class GameUnitController;
class GameModeController;
class MapView;
class GameMainDialog;
class GameInfoDialogController;
class GameTurnController;

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
	/** */
	void InitGameInfoDialogController();
	/** */
	void InitGameTurnController();
	/** */
	void SetDefaultOwnerType();
	/** */
	void InitSignalConnections();
private:
	friend class GameDemonstrator;
	static GameUnitController*	GameControllerObject;
	static GameModeController*	GameModeControllerObject;
	static GameInfoDialogController*	GameInfoDialogControllerObject;
	static GameTurnController*	GameTurnControllerObject;

	static GameDemonstrator*	GameDemonstratorObject;
	static MapView*				MapViewObject;
	static GameMainDialog*		GameMainDialogObject;
};

#endif // GAMEFACTORY_H