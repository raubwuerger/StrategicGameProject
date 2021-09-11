#ifndef GAMEMAPCREATORHEIGHTMAP_H
#define GAMEMAPCREATORHEIGHTMAP_H

#include "IGameMapCreator.h"

class GameMapCreatorHeightMap : public IGameMapCreator
{
public:
	/** */
	bool CreateMap() override;

};

#endif // GAMEMAPCREATORHEIGHTMAP_H