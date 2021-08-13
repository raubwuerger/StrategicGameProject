#ifndef SERIALIZEXML_H
#define SERIALIZEXML_H

#include "ISerializeGameInterface.h"
#include <QXmlStreamWriter>
class GameMapItem;
class QDomNode;
class QDomNodeList;

class SerializeXML : public ISerializeGameInterface
{
public:
/** */
	SerializeXML();
/** */
	~SerializeXML();
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
	bool SaveMapItem( QXmlStreamWriter& xmlWriter, const GameMapItem* modelMapItem );
public:
	/** */
	bool LoadGame( const QString& saveGameName );
private:
	/** */
	bool LoadGame(const QDomNodeList& saveGameNodeList);
	/** */
	bool LoadGameData( const QDomNode& domNode );
	/** */
	bool LoadPlayerData( const QDomNode& domNode );
	/** */
	bool LoadMapData( const QDomNode& domNode );
	/** */
	bool LoadUnitData(const QDomNode& domNode);
};

#endif // SERIALIZEXML_H

