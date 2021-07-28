#pragma once

class GameMap;

/** Creates game map representation */
class GameMapFactory
{
public:
	/** */
	static GameMapFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	GameMap* CreateMap();
private:
	/** */
	GameMapFactory();
	/** */
	~GameMapFactory();
private:
	static GameMapFactory	*Instance;
	GameMap*	TheGameMap;
};
