#ifndef GAMEMAPFACTORY_H
#define GAMEMAPFACTORY_H

class GameMapItemRepository;
class IGameMapItemCreator;

/** Creates game map representation */
class GameMapItemFactory
{
public:
	/** */
	GameMapItemFactory();
	/** */
	~GameMapItemFactory();
	/** */
	void Release();
	/** Creates Map */
	bool Create();
private:
	GameMapItemRepository*		TheGameMap;
	IGameMapItemCreator*		MapCreator;
};

#endif // GAMEMAPFACTORY_H
