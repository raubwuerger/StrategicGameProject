#ifndef MapCreatorSaveGame_H
#define MapCreatorSaveGame_H

#include "IGameMapCreator.h"

class GameMapRepository;
class GameMapItem;
class GameUnitItem;
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
/** */
	bool CreateUnitItems(const QDomNode& units);
/** */
	GameUnitItem* CreateUnitItemFromXML(const QDomNode& unit);
private:
	const QDomNode* MapElements;
	int				Rows;
	int				Cols;
};

#endif