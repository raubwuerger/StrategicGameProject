#ifndef GAMEMAPCREATORSIMPLE_H
#define GAMEMAPCREATORSIMPLE_H

#include "IGameMapItemCreator.h"
class GameMapItem;

class GameMapItemCreatorSimple : public IGameMapItemCreator
{
public:
	/** */
	GameMapItemCreatorSimple();
	/** */
	virtual bool CreateMap();
private:
	GameMapItem* CreateModelMapItem( unsigned int row, unsigned int col );
private:
	int MapItemId;
};

#endif // GAMEMAPCREATORSIMPLE_H