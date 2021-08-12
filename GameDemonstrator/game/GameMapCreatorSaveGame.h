#ifndef GAMEMAPCREATORSAVEGAME_H
#define GAMEMAPCREATORSAVEGAME_H

#include "IGameMapCreator.h"

class GameMapRepository;
class GameMapItem;
class QDomNode;

class GameMapCreatorSaveGame : public IGameMapCreator
{
public:
/** */
	GameMapCreatorSaveGame( const QDomNode mapElements );
/** */
	~GameMapCreatorSaveGame();
/** */
	virtual bool CreateMap();
/** */
	virtual GameMapRepository* GetMap();
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