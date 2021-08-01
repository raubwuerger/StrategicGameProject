#pragma once

#include "ISerializeGameInterface.h"
#include <QXmlStreamWriter>
class ModelMapItem;

class SaveToXML : public ISerializeGameInterface
{
public:
/** */
	SaveToXML();
/** */
	~SaveToXML();
public:
	/** */
	bool SaveGame();
	/** */
	bool LoadGame();
private:
	/** */
	bool CreateFramework();
	/** */
	bool SaveGame( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveGameData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SavePlayerData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapData( QXmlStreamWriter& xmlWriter );
	/** */
	bool CreateMapItems( QXmlStreamWriter& xmlWriter );
	/** */
	bool CreateMapItem( QXmlStreamWriter& xmlWriter, const ModelMapItem* modelMapItem );
};

