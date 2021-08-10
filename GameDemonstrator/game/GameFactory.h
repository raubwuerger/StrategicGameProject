#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

class GameConfig;

/* Creates the hole game. From scratch or from savegame. */
class GameFactory
{
	public:
		/** */
		GameFactory();
		/** */
		bool Create(const GameConfig* gameConfig);
		/** */
		bool CreateFromSavegame();
};

#endif // GAMEFACTORY_H