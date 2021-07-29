#pragma once

class ModelMapRepository;

/** Creates game map representation */
class ModelMapConfigFactory
{
public:
	/** */
	static ModelMapConfigFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	ModelMapRepository* CreateMap();
private:
	/** */
	ModelMapConfigFactory();
	/** */
	~ModelMapConfigFactory();
private:
	static ModelMapConfigFactory	*Instance;
	ModelMapRepository*	TheGameMap;
};
