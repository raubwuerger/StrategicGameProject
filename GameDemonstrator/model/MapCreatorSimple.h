#ifndef MAPCREATORSIMPLE_H
#define MAPCREATORSIMPLE_H

#include "IMapCreator.h"

class MapCreatorSimple : public IMapCreator
{
	/** */
	virtual bool CreateMap();
	/** */
	ModelMapRepository* GetMap();
};

#endif // MAPCREATORSIMPLE_H