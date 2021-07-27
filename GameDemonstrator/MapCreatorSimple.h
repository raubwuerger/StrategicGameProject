#ifndef MAPCREATORSIMPLE_H
#define MAPCREATORSIMPLE_H

#include "IMapCreator.h"

class MapCreatorSimple : public IMapCreator
{
	virtual bool CreateMap();
};

#endif // MAPCREATORSIMPLE_H