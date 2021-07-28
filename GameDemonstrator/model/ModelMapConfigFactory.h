#pragma once

class GameMap;

/** Creates game map representation */
class ModelMapConfigFactory
{
public:
	/** */
	static ModelMapConfigFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	GameMap* CreateMap();
private:
	/** */
	ModelMapConfigFactory();
	/** */
	~ModelMapConfigFactory();
private:
	static ModelMapConfigFactory	*Instance;
	GameMap*	TheGameMap;
};
