#ifndef ModelMapFactory_H
#define ModelMapFactory_H

class ModelMapRepository;
class IModelMapCreator;

/** Creates game map representation */
class ModelMapFactory
{
public:
	/** */
	static ModelMapFactory* GetInstance();
	/** */
	void Release();
	/** Creates Map */
	ModelMapRepository* CreateModelMap();
private:
	/** */
	ModelMapFactory();
	/** */
	~ModelMapFactory();
private:
	static ModelMapFactory	*Instance;
	ModelMapRepository*	TheGameMap;
	IModelMapCreator*		MapCreator;
};

#endif
