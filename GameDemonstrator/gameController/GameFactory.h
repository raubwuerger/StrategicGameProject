#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

class GameConfig;
class GameController;

/* Creates the hole game. From scratch or from savegame. */
class GameFactory
{
public:
	/** */
	GameFactory();
	/** */
	void InitGameController();
	/** */
	bool Create(const GameConfig* gameConfig);
	/** */
	bool CreateFromSavegame();
private:
	static GameController*	GameControllerObject;
};

#endif // GAMEFACTORY_H