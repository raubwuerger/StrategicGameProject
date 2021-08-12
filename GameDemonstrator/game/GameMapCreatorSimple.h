#ifndef GAMEMAPCREATORSIMPLE_H
#define GAMEMAPCREATORSIMPLE_H

#include "IGameMapCreator.h"
class GameMapItem;

class GameMapCreatorSimple : public IGameMapCreator
{
public:
	/** */
	GameMapCreatorSimple();
	/** */
	virtual bool CreateMap();
	/** */
	GameMapRepository* GetMap();
private:
	GameMapItem* CreateModelMapItem( unsigned int row, unsigned int col );
private:
	int MapItemId;
};

#endif // GAMEMAPCREATORSIMPLE_H