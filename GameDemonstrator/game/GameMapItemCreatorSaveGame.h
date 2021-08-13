#ifndef GAMEMAPCREATORSAVEGAME_H
#define GAMEMAPCREATORSAVEGAME_H

#include "IGameMapItemCreator.h"

class GameMapItemRepository;
class GameMapItem;
class QDomNode;

class GameMapItemCreatorSaveGame : public IGameMapItemCreator
{
public:
/** */
	GameMapItemCreatorSaveGame( const QDomNode mapElements );
/** */
	~GameMapItemCreatorSaveGame();
/** */
	virtual bool CreateMap();
private:
/** */
	bool InitializeMap( const QDomNode& settings );
/** */
	bool CreateMapItems( const QDomNode& mapItems );
/** */
	GameMapItem* CreateFromXML( const QDomNode& mapNode );
private:
	const QDomNode* MapElements;
	int				Rows;
	int				Cols;
};

#endif // GAMEMAPCREATORSAVEGAME_H