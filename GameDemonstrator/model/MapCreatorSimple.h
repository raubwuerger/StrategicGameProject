#ifndef MAPCREATORSIMPLE_H
#define MAPCREATORSIMPLE_H

#include "IMapCreator.h"

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
	int MapItemId;
};

#endif // MAPCREATORSIMPLE_H