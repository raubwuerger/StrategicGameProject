#include "stdafx.h"
#include "SerializeXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "SerializeXMLItems.h"
#include "game/GameMainCounter.h"
#include "model/ModelMapRepository.h"
#include "model/ModelMapItem.h"
#include "model/ModelTerrainType.h"

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
	if( false == SaveFramework(saveGameName) )
	{
		return false;
	}
	return false;
}

//==============================================================================
bool SerializeXML::SaveFramework( const QString& saveGameName )
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
	if( false == SaveMapItems(xmlWriter) )
	{
		xmlWriter.writeEndElement();
		return false;
	}
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
	if( false == LoadFramework(saveGameName) )
	{
		return false;
	}
	return false;
}

//==============================================================================
bool SerializeXML::LoadFramework( const QString& saveGameName )
{
	QString saveGamePath(".\\savegames\\");
	QString saveGameFile( saveGamePath +saveGamePath );

	QFile file(saveGameFile);

	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		jha::GetLog()->Log_ERROR( QObject::tr("Unable to create savegame file: %1 ").arg(saveGameFile) );
		return false;
	}

	QDomDocument saveGameDocument;
	saveGameDocument.setContent(&file);

	if( false == LoadGame(saveGameDocument.documentElement()) )
	{
		file.close();
		return false;
	}

	file.close();
	jha::GetLog()->Log_INFO( QObject::tr("Succesfull loaded savegame: %1").arg(saveGameFile) );

	return true;
}

//==============================================================================
bool SerializeXML::LoadGame( const QDomElement& xmlElement )
{
	if( false == LoadGameData(xmlElement) )
	{
		return false;
	}
	if( false == LoadPlayerData(xmlElement) )
	{
		return false;
	}
	if( false == LoadMapData(xmlElement) )
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::LoadGameData( const QDomElement& xmlElement )
{
	QString tagName = xmlElement.tagName();
	return true;
}

//==============================================================================
bool SerializeXML::LoadPlayerData( const QDomElement& xmlElement )
{
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapData( const QDomElement& xmlElement )
{
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapItems( const QDomElement& xmlElement )
{
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapItem( const QDomElement& xmlElement, const ModelMapItem* modelMapItem)
{
	return true;
}
