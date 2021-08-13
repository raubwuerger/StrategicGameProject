#include "stdafx.h"
#include "SerializeXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "SerializeXMLItems.h"
#include "game/GameMainCounter.h"
#include "game/GameMapItemRepository.h"
#include "game/GameMapItem.h"
#include "model/ModelTerrainType.h"
#include "game/GameMapItemCreatorSaveGame.h"
#include "game/GameUnitItemFactory.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "DomNodeFinder.h"
#include "io/ConfigFileLoader.h"

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
		xmlWriter.writeTextElement( SerializeXMLItems::ROWS, QString::number(GameMapItemRepository::GetInstance()->GetRows()) );
		xmlWriter.writeTextElement( SerializeXMLItems::COLS, QString::number(GameMapItemRepository::GetInstance()->GetCols()) );
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapItems(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAPITEMS );

	const QVector< QVector<GameMapItem*> >* modelMap = GameMapItemRepository::GetInstance()->GetMapItems();
	if( nullptr == modelMap )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to save game map!") );
		xmlWriter.writeEndElement();
		return false;
	}

	int rows = modelMap->size();
	for( int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapItem*> row = modelMap->at(currentRow);
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
bool SerializeXML::SaveMapItem(QXmlStreamWriter& xmlWriter, const GameMapItem* modelMapItem)
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
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(saveGameName, SerializeXMLItems::SAVEGAME))
	{
		return false;
	}

	if (false == LoadGame(configFileLoader.GetQDomNodeList()))
	{
		return false;
	}

	return true;
}

#include "DomNodeListFinder.h"
//==============================================================================
bool SerializeXML::LoadGame(const QDomNodeList& saveGameNodeList)
{
	DomNodeListFinder domNodeListFinder(saveGameNodeList);
	if (false == LoadGameData(domNodeListFinder.FindDomNodeByName(SerializeXMLItems::GAME)))
	{
		return false;
	}
	if (false == LoadPlayerData(domNodeListFinder.FindDomNodeByName(SerializeXMLItems::PLAYERS)))
	{
		return false;
	}
	if (false == LoadMapData(domNodeListFinder.FindDomNodeByName(SerializeXMLItems::MAP)))
	{
		return false;
	}
	if (false == LoadUnitData(domNodeListFinder.FindDomNodeByName(SerializeXMLItems::UNITS)))
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::LoadGameData( const QDomNode& domNode )
{
	if (true == domNode.isNull())
	{
		return false;
	}
	QString domNodeName = domNode.nodeName();
	return true;
}

//==============================================================================
bool SerializeXML::LoadPlayerData( const QDomNode& domNode )
{
	if (true == domNode.isNull())
	{
		return false;
	}
	QString domNodeName = domNode.nodeName();
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapData( const QDomNode& domNode )
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameMapItemCreatorSaveGame mapCreatorSaveGame(domNode.cloneNode(true));
	return mapCreatorSaveGame.CreateMap();
}

//==============================================================================
bool SerializeXML::LoadUnitData(const QDomNode& domNode)
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameUnitItemFactory gameUnitItemFactory;
	return gameUnitItemFactory.CreateGameUnitItemsFromSaveGame(domNode);
}
