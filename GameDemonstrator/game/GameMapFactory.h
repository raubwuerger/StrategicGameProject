#ifndef GAMEMAPFACTORY_H
#define GAMEMAPFACTORY_H

class GameMapRepository;
class IGameMapCreator;

/** Creates game map representation */
class GameMapFactory
{
public:
	/** */
	GameMapFactory();
	/** */
	~GameMapFactory();
	/** */
	void Release();
	/** Creates Map */
	bool Create();
private:
	GameMapRepository*		TheGameMap;
	IGameMapCreator*		MapCreator;
};

#endif // GAMEMAPFACTORY_H
