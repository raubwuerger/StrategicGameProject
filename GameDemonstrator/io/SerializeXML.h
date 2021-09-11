#ifndef SERIALIZEXML_H
#define SERIALIZEXML_H

#include "ISerializeGameInterface.h"
#include <QXmlStreamWriter>
class GameMapTile;
class QDomNode;
class QDomNodeList;
class GameUnit;
class GameCity;
class GameOwner;

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
	bool CreateSaveGameFile( const QString& saveGameName );
	/** */
	bool SaveGame( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveGameData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SavePlayerData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SavePlayer(QXmlStreamWriter& xmlWriter, const GameOwner* item);
	/** */
	bool SaveMapData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapSettings( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapItems( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveMapItem( QXmlStreamWriter& xmlWriter, const GameMapTile* modelMapItem );
	/** */
	bool SaveUnitData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveUnitItem( QXmlStreamWriter& xmlWriter, const GameUnit* gameUnitDItem );
	/** */
	bool SaveCityData( QXmlStreamWriter& xmlWriter );
	/** */
	bool SaveCitytItem( QXmlStreamWriter& xmlWriter, const GameCity* gameCityItem );
	/** */
	bool WriteCityProduction( QXmlStreamWriter& xmlWriter, const GameCity* gameCityItem );
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
	/** */
	bool LoadCityData(const QDomNode& domNode);
	/** */
	bool UpdateGameConfig();
};

#endif // SERIALIZEXML_H

