#pragma once

#include "IMapCreator.h"

class ModelMapRepository;
class ModelMapItem;
class QDomNode;

class MapCreatorSaveGame : public IMapCreator
{
public:
/** */
	MapCreatorSaveGame( const QDomNode mapElements );
/** */
	~MapCreatorSaveGame();
/** */
	virtual bool CreateMap();
/** */
	virtual ModelMapRepository* GetMap();
private:
/** */
	bool InitializeMap( const QDomNode& settings );
/** */
	bool CreateMapItems( const QDomNode& mapItems );
/** */
	ModelMapItem* CreateFromXML( const QDomNode& node );
private:
	const QDomNode* MapElements;
	int				Rows;
	int				Cols;
};