#ifndef MAPCREATORSIMPLE_H
#define MAPCREATORSIMPLE_H

#include "IMapCreator.h"
class ModelMapItem;

class MapCreatorSimple : public IMapCreator
{
public:
	/** */
	MapCreatorSimple();
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