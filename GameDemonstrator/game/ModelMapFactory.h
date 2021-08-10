#ifndef ModelMapFactory_H
#define ModelMapFactory_H

class ModelMapRepository;
class IModelMapCreator;

/** Creates game map representation */
class ModelMapFactory
{
public:
	/** */
	ModelMapFactory();
	/** */
	~ModelMapFactory();
	/** */
	void Release();
	/** Creates Map */
	ModelMapRepository* CreateModelMap();
private:
	ModelMapRepository*		TheGameMap;
	IModelMapCreator*		MapCreator;
};

#endif
