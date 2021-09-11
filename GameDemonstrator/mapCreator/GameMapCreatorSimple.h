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
	GameMapTile* CreateGameMapItem( unsigned int row, unsigned int col );
private:
	int MapItemId;
};

#endif // GAMEMAPCREATORSIMPLE_H