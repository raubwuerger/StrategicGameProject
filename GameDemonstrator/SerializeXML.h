#pragma once

#include "ISerializeGameInterface.h"
#include <QXmlStreamWriter>
class ModelMapItem;
class QDomElement;

class SerializeXML : public ISerializeGameInterface
{
public:
/** */
	SerializeXML();
/** */
	~SerializeXML();
public:
	/** */
	bool SaveGame( const QString& saveGameName );
private:
	/** */
	bool SaveXMLHeader( const QString& saveGameName );
	/** */
	bool SaveGame( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveGameData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SavePlayerData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapSettings( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapItems( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapItem( QXmlStreamWriter& xmlWriter, const ModelMapItem* modelMapItem );
public:
	/** */
	bool LoadGame( const QString& saveGameName );
private:
	/** */
	bool LoadXMLHeader( const QString& saveGameName );
	/** */
	bool LoadGame( const QDomElement& xmlElement );
	/** */
	bool LoadGameData( const QDomElement& xmlElement );
	/** */
	bool LoadPlayerData( const QDomElement& xmlElement );
	/** */
	bool LoadMapData( const QDomElement& xmlElement );
};

