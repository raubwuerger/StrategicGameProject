#ifndef MAPCREATORSIMPLE_H
#define MAPCREATORSIMPLE_H

#include "IModelMapCreator.h"
class ModelMapItem;

class ModelMapCreatorSimple : public IModelMapCreator
{
public:
	/** */
	ModelMapCreatorSimple();
	/** */
	virtual bool CreateMap();
	/** */
	ModelMapRepository* GetMap();
private:
	ModelMapItem* CreateModelMapItem( unsigned int row, unsigned int col );
private:
	int MapItemId;
};

#endif // MAPCREATORSIMPLE_H