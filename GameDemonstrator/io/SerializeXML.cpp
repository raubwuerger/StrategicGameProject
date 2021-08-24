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
#include "game/GameUnitItemRepository.h"
#include "game/GameUnitItem.h"

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
	if (false == SaveUnitData(xmlWriter))
	{
		return false;
	}
	if (false == SaveCityData(xmlWriter))
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
bool SerializeXML::SaveUnitData(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement(SerializeXMLItems::UNITS);
	
	QMap<int, GameUnitItem*>::const_iterator gameUnitItems = GameUnitItemRepository::GetInstance()->GetFirstIterator();
	while (gameUnitItems != GameUnitItemRepository::GetInstance()->GetLastIterator())
	{
		if (false == SaveUnitItem(xmlWriter,gameUnitItems.value()))
		{
			return false;
		}
		gameUnitItems++;
	}

	xmlWriter.writeEndElement();
	return true;
}

#include "model/ModelUnitType.h"
#include "model/ModelOwnerType.h"
//==============================================================================
bool SerializeXML::SaveUnitItem(QXmlStreamWriter& xmlWriter, const GameUnitItem* gameUnitItem)
{
	xmlWriter.writeStartElement(SerializeXMLItems::UNITS_UNIT);
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_ID, QString::number(gameUnitItem->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_UNITTYPEID, QString::number(gameUnitItem->GetModelUnitType()->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_GAMEMAPITEMID, QString::number(gameUnitItem->GetGameMapItemId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_NAME, gameUnitItem->GetName());
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_OWNERTYPEID, QString::number(gameUnitItem->GetModelOwnerType()->GetId()));
	xmlWriter.writeEndElement();
	return true;
}

#include "game/GameCityItemRepository.h"
#include "game/GameCityItem.h"
bool SerializeXML::SaveCityData(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement(SerializeXMLItems::CITIES);

	QMap<int, GameCityItem*>::const_iterator gameCityItems = GameCityItemRepository::GetInstance()->GetFirstIterator();
	while (gameCityItems != GameCityItemRepository::GetInstance()->GetLastIterator())
	{
		if (false == SaveCitytItem(xmlWriter, gameCityItems.value()))
		{
			return false;
		}
		gameCityItems++;
	}

	xmlWriter.writeEndElement();
	return true;
}

bool SerializeXML::SaveCitytItem(QXmlStreamWriter& xmlWriter, const GameCityItem* gameCityItem)
{
	xmlWriter.writeStartElement(SerializeXMLItems::CITIES_CITY);
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_ID, QString::number(gameCityItem->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_CITYTYPEID, QString::number(gameCityItem->GetModelOwnerTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_OWNERTYPEID, QString::number(gameCityItem->GetModelOwnerTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_GAMEMAPITEMID, QString::number(gameCityItem->GetGameMapItemId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_NAME, gameCityItem->GetName());
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_EFFICIENCY, QString::number(gameCityItem->GetEfficiency()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_SPEZIALIZEDUNITTYPEID, QString::number(gameCityItem->GetSpezializedUnitTypeId()));
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
	if (false == LoadCityData(domNodeListFinder.FindDomNodeByName(SerializeXMLItems::CITIES)))
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

#include "game/GameCityItemFactory.h"
//==============================================================================
bool SerializeXML::LoadCityData(const QDomNode& domNode)
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameCityItemFactory factory;
	return factory.Create(domNode);
}
