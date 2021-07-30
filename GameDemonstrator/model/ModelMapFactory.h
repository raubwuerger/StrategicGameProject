#pragma once

class ModelMapRepository;
class IMapCreator;

/** Creates game map representation */
class ModelMapFactory
{
public:
	/** */
	static ModelMapFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	ModelMapRepository* CreateMap();
private:
	/** */
	ModelMapFactory();
	/** */
	~ModelMapFactory();
private:
	static ModelMapFactory	*Instance;
	ModelMapRepository*	TheGameMap;
	IMapCreator*		MapCreator;
};
