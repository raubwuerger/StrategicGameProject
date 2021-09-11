#ifndef GAMEMAPCREATORSIMPLE_H
#define GAMEMAPCREATORSIMPLE_H

#include "IGameMapCreator.h"
class GameMapTile;

class GameMapCreatorSimple : public IGameMapCreator
{
public:
	/** */
	GameMapCreatorSimple();
	/** */
	virtual bool CreateMap();
private:
	/** */
	GameMapTile* CreateGameMapTile( unsigned int row, unsigned int col );
};

#endif // GAMEMAPCREATORSIMPLE_H