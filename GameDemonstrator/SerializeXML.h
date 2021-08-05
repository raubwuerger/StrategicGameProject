#ifndef SerializeXML_H
#define SerializeXML_H

#include "ISerializeGameInterface.h"
#include <QXmlStreamWriter>
class ModelMapItem;
class QDomNode;

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
	bool LoadGame( const QDomNode& domNode );
	/** */
	bool LoadGameData( const QDomNode& domNode );
	/** */
	bool LoadPlayerData( const QDomNode& domNode );
	/** */
	bool LoadMapData( const QDomNode& domNode );
};

#endif

