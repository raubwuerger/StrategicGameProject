#pragma once

#include "IMapCreator.h"

class ModelMapRepository;
class QDomNodeList;
class QDomNode;

class MapCreatorSaveGame : public IMapCreator
{
public:
/** */
	MapCreatorSaveGame( const QDomNodeList& mapElement );
/** */
	virtual bool CreateMap();
/** */
	virtual ModelMapRepository* GetMap();
private:
/** */
	const QDomNode* FindDomNodeByName( const QString& domNodeName );
/** */
	bool InitializeMap( const QDomNode *settings );
/** */
	bool CreateMapItems( const QDomNode *mapItems );
private:
	const QDomNodeList& MapElements;
};