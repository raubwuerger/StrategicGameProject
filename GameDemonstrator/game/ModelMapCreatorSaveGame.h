#ifndef MapCreatorSaveGame_H
#define MapCreatorSaveGame_H

#include "IModelMapCreator.h"

class ModelMapRepository;
class ModelMapItem;
class QDomNode;

class ModelMapCreatorSaveGame : public IModelMapCreator
{
public:
/** */
	ModelMapCreatorSaveGame( const QDomNode mapElements );
/** */
	~ModelMapCreatorSaveGame();
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
	ModelMapItem* CreateFromXML( const QDomNode& mapNode );
private:
	const QDomNode* MapElements;
	int				Rows;
	int				Cols;
};

#endif