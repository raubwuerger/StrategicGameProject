#include "stdafx.h"
#include "SerializeXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "SerializeXMLItems.h"
#include "game/GameMainCounter.h"
#include "model/ModelMapRepository.h"
#include "model/ModelMapItem.h"
#include "model/ModelTerrainType.h"
#include "model/MapCreatorSaveGame.h"
#include "DomNodeFinder.h"

//==============================================================================
SerializeXML::SerializeXML()
{
}

//==============================================================================
SerializeXML::~SerializeXML()
{
}

//==============================================================================
bool SerializeXML::SaveGame( const QString& saveGameName )
{
	if( false == SaveXMLHeader(saveGameName) )
	{
		return false;
	}
	return false;
}

//==============================================================================
bool SerializeXML::SaveXMLHeader( const QString& saveGameName )
{
	QFile file(saveGameName);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		jha::GetLog()->Log_ERROR( QObject::tr("Unable to create savegame file: %1 ").arg(saveGameName) );
		return false;
	}

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement( SerializeXMLItems::SAVEGAME );

	if( false == SaveGame(xmlWriter) )
	{
		file.close();
		return false;
	}

	xmlWriter.writeEndElement();

	file.close();
	jha::GetLog()->Log_INFO( QObject::tr("Succesfull create savegame: %1").arg(saveGameName) );

	return true;
}


//==============================================================================
bool SerializeXML::SaveGame( QXmlStreamWriter& xmlWriter )
{
	if( false == SaveGameData(xmlWriter) )
	{
		return false;
	}
	if( false == SavePlayerData(xmlWriter) )
	{
		return false;
	}
	if( false == SaveMapData(xmlWriter) )
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::SaveGameData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement( SerializeXMLItems::GAME );
		xmlWriter.writeTextElement( SerializeXMLItems::VERSION, "0.9" );
		xmlWriter.writeTextElement( SerializeXMLItems::PLAYERCOUNT, "2");
		xmlWriter.writeTextElement( SerializeXMLItems::GAMETURN, GameMainCounter::GetInstance()->GetCurrentDate().toString("yyyy-MM"));
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SavePlayerData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement( SerializeXMLItems::PLAYERS );
		xmlWriter.writeStartElement( SerializeXMLItems::PLAYER );
			xmlWriter.writeTextElement( SerializeXMLItems::ID, "1" );
			xmlWriter.writeTextElement( SerializeXMLItems::NAME, "Spieler 1" );
			xmlWriter.writeTextElement( SerializeXMLItems::HUMAN, "1" );
		xmlWriter.writeEndElement();
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAP );
	if( false == SaveMapSettings(xmlWriter) )
	{
		xmlWriter.writeEndElement();
		return false;
	}

	if( false == SaveMapItems(xmlWriter) )
	{
		xmlWriter.writeEndElement();
		return false;
	}
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapSettings(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement( SerializeXMLItems::SETTINGS );
		xmlWriter.writeTextElement( SerializeXMLItems::ROWS, QString::number(ModelMapRepository::GetInstance()->GetRows()) );
		xmlWriter.writeTextElement( SerializeXMLItems::COLS, QString::number(ModelMapRepository::GetInstance()->GetCols()) );
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapItems(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAPITEMS );

	const QVector< QVector<ModelMapItem*> >* modelMap = ModelMapRepository::GetInstance()->GetMapItems();
	if( nullptr == modelMap )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to save game map!") );
		xmlWriter.writeEndElement();
		return false;
	}

	int rows = modelMap->size();
	for( int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<ModelMapItem*> row = modelMap->at(currentRow);
		int cols = row.size();
		for( int currentCol = 0; currentCol < cols; currentCol++ )
		{
			if( false == SaveMapItem( xmlWriter, row.at(currentCol) ) )
			{
				return false;
			}
		}
	}

	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapItem(QXmlStreamWriter& xmlWriter, const ModelMapItem* modelMapItem)
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAPITEM );
		xmlWriter.writeTextElement( SerializeXMLItems::ID, QString::number(modelMapItem->GetId()) );
		xmlWriter.writeTextElement( SerializeXMLItems::ROW, QString::number(modelMapItem->GetRow()) );
		xmlWriter.writeTextElement( SerializeXMLItems::COL, QString::number(modelMapItem->GetCol()) );
		xmlWriter.writeTextElement( SerializeXMLItems::TERRAINTYPE, QString::number(modelMapItem->GetTerrainType()->GetId()) );
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::LoadGame( const QString& saveGameName )
{
	if( false == LoadXMLHeader(saveGameName) )
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::LoadXMLHeader( const QString& saveGameName )
{
	QString saveGamePath(".\\savegames\\");
	QString saveGameFile( saveGamePath +saveGameName );

	QFile file(saveGameFile);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		jha::GetLog()->Log_ERROR( QObject::tr("Unable to create savegame file: %1 ").arg(saveGameFile) );
		return false;
	}

	QDomDocument saveGameDocument;
	saveGameDocument.setContent(&file);

	QDomNodeList rootNodeList = saveGameDocument.elementsByTagName(SerializeXMLItems::SAVEGAME);
	if( 0 == rootNodeList.count() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("No root node named: %1").arg(SerializeXMLItems::SAVEGAME) );
		return false;
	}

	if( false == LoadGame( rootNodeList.at(0) ) )
	{
		file.close();
		return false;
	}

	file.close();
	jha::GetLog()->Log_INFO( QObject::tr("Succesfull loaded savegame: %1").arg(saveGameFile) );

	return true;
}

//==============================================================================
bool SerializeXML::LoadGame( const QDomNode& domNode )
{
	if( false == LoadGameData(domNode) )
	{
		return false;
	}
	if( false == LoadPlayerData(domNode) )
	{
		return false;
	}
	if( false == LoadMapData(domNode) )
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::LoadGameData( const QDomNode& domNode )
{
	QString domNodeName = domNode.nodeName();
	return true;
}

//==============================================================================
bool SerializeXML::LoadPlayerData( const QDomNode& domNode )
{
	QString domNodeName = domNode.nodeName();
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapData( const QDomNode& domNode )
{
	QString domNodeName = domNode.nodeName();

	DomNodeFinder domNodeFinder(domNode);
	const QDomNode mapNode = domNodeFinder.FindDomeNodeByNameClone(SerializeXMLItems::MAP);
	MapCreatorSaveGame mapCreatorSaveGame( mapNode.cloneNode(true) );
	return mapCreatorSaveGame.CreateMap();
}
