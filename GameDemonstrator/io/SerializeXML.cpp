#include "stdafx.h"
#include "SerializeXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "SerializeXMLItems.h"
#include "game/GameMapTileRepository.h"
#include "game/GameMapTileFactory.h"
#include "game/GameMapTile.h"
#include "game/GameUnitRepository.h"
#include "game/GameUnitFactory.h"
#include "game/GameUnit.h"
#include "game/GameCityRepository.h"
#include "game/GameCityFactory.h"
#include "game/GameCity.h"
#include "game/GameOwner.h"
#include "game/GameOwnerFactory.h"
#include "game/GameOwnerRepository.h"
#include "model/ModelUnitType.h"
#include "model/ModelOwnerType.h"
#include "model/ModelOwnerTypeRepository.h"
#include "model/ModelTerrainType.h"
#include "DomNodeFinder.h"
#include "io/ConfigFileLoader.h"
#include "DomNodeListFinder.h"
#include "game/GameConfig.h"
#include "game/GameDataFactory.h"
#include "game/GameUnitProduction.h"


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
	if( false == CreateSaveGameFile(saveGameName) )
	{
		return false;
	}
	return true;
}

//==============================================================================
bool SerializeXML::CreateSaveGameFile( const QString& saveGameName )
{
	QFile file(saveGameName);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		jha::GetLog()->Log_ERROR( QObject::tr("Unable to create save game file: %1 ").arg(saveGameName) );
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
	jha::GetLog()->Log_INFO( QObject::tr("Successful create save game: %1").arg(saveGameName) );

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
		xmlWriter.writeTextElement( SerializeXMLItems::GAME_VERSION_MAJOR, QString::number(GameConfig::VersionMajor) );
		xmlWriter.writeTextElement(SerializeXMLItems::GAME_VERSION_MINOR, QString::number(GameConfig::VersionMinor));
		xmlWriter.writeTextElement(SerializeXMLItems::GAME_VERSION_REVISION, QString::number(GameConfig::VersionRevision));
		xmlWriter.writeTextElement(SerializeXMLItems::GAME_PLAYER, QString::number(GameConfig::PlayerId));
		xmlWriter.writeTextElement( SerializeXMLItems::GAME_PLAYERCOUNT, QString::number(GameConfig::PlayerCount));
		xmlWriter.writeTextElement( SerializeXMLItems::GAME_GAMETURN, QString::number(GameConfig::CurrentTurn));
		xmlWriter.writeTextElement( SerializeXMLItems::GAME_DIFFICULTYLEVEL, QString::number(GameConfig::DifficultyLevel));
		xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SavePlayerData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement( SerializeXMLItems::PLAYERS );
	QMap<int, GameOwner*>::const_iterator iterator = GameOwnerRepository::GetInstance()->GetFirstIterator();
	while (iterator != GameOwnerRepository::GetInstance()->GetLastIterator())
	{
		SavePlayer(xmlWriter, iterator.value());
		iterator++;
	}
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SavePlayer(QXmlStreamWriter& xmlWriter, const GameOwner* item)
{
	xmlWriter.writeStartElement(SerializeXMLItems::PLAYERS_PLAYER);
		xmlWriter.writeTextElement(SerializeXMLItems::PLAYER_ID, QString::number(item->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::PLAYER_OWNERTYPEID, QString::number(item->GetModelOwnerTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::PLAYER_NAME, item->GetName());
		xmlWriter.writeTextElement(SerializeXMLItems::PLAYER_HUMAN, QString::number(item->GetIsHuman()));
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
	xmlWriter.writeStartElement( SerializeXMLItems::MAP_SETTINGS );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_SETTINGS_ROWS, QString::number(GameMapTileRepository::GetInstance()->GetRows()) );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_SETTINGS_COLS, QString::number(GameMapTileRepository::GetInstance()->GetCols()) );
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveMapItems(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAP_MAPITEMS );

	const QVector< QVector<GameMapTile*> >* modelMap = GameMapTileRepository::GetInstance()->GetMapTiles();
	if( nullptr == modelMap )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("No GameMap present!") );
		xmlWriter.writeEndElement();
		return false;
	}

	int rows = modelMap->size();
	for( int currentRow = 0; currentRow < rows; currentRow++ )
	{
		QVector<GameMapTile*> row = modelMap->at(currentRow);
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
bool SerializeXML::SaveMapItem(QXmlStreamWriter& xmlWriter, const GameMapTile* modelMapItem)
{
	xmlWriter.writeStartElement( SerializeXMLItems::MAP_MAPITEM );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_ID, QString::number(modelMapItem->GetId()) );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_ROW, QString::number(modelMapItem->GetRow()) );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_COL, QString::number(modelMapItem->GetCol()) );
		xmlWriter.writeTextElement( SerializeXMLItems::MAP_TERRAINTYPE, QString::number(modelMapItem->GetTerrainType()->GetId()) );
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveUnitData(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement(SerializeXMLItems::UNITS);
	
	QMap<int, GameUnit*>::const_iterator gameUnitItems = GameUnitRepository::GetInstance()->GetFirstIterator();
	while (gameUnitItems != GameUnitRepository::GetInstance()->GetLastIterator())
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

//==============================================================================
bool SerializeXML::SaveUnitItem(QXmlStreamWriter& xmlWriter, const GameUnit* gameUnitItem)
{
	xmlWriter.writeStartElement(SerializeXMLItems::UNITS_UNIT);
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_ID, QString::number(gameUnitItem->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_UNITTYPEID, QString::number(gameUnitItem->GetModelUnitTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_GAMEMAPITEMID, QString::number(gameUnitItem->GetGameTileId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_NAME, gameUnitItem->GetName());
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_OWNERTYPEID, QString::number(gameUnitItem->GetModelOwnerTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_STRENGTH, QString::number(gameUnitItem->GetCurrentStrength()));
		xmlWriter.writeTextElement(SerializeXMLItems::UNITS_MOVEMENTPOINTS, QString::number(gameUnitItem->GetCurrentMovementPoints()));
		xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::SaveCityData(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement(SerializeXMLItems::CITIES);

	QMap<int, GameCity*>::const_iterator gameCityItems = GameCityRepository::GetInstance()->GetFirstIterator();
	while (gameCityItems != GameCityRepository::GetInstance()->GetLastIterator())
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

//==============================================================================
bool SerializeXML::SaveCitytItem(QXmlStreamWriter& xmlWriter, const GameCity* gameCityItem)
{
	xmlWriter.writeStartElement(SerializeXMLItems::CITIES_CITY);
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_ID, QString::number(gameCityItem->GetId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_MODELCITYTYPEID, QString::number(gameCityItem->GetModelCityTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_OWNERTYPEID, QString::number(gameCityItem->GetGameOwnerId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_GAMEMAPITEMID, QString::number(gameCityItem->GetGameMapTileId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_NAME, gameCityItem->GetName());
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_EFFICIENCY, QString::number(gameCityItem->GetCurrentEfficiency()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_SPEZIALIZEDUNITTYPEID, QString::number(gameCityItem->GetSpezializedUnitTypeId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_STRENGTH, QString::number(gameCityItem->GetCurrentStrength()));
		WriteCityProduction(xmlWriter, gameCityItem);
	xmlWriter.writeEndElement();
	return true;
}

//==============================================================================
bool SerializeXML::WriteCityProduction(QXmlStreamWriter& xmlWriter, const GameCity* gameCityItem)
{
	xmlWriter.writeStartElement(SerializeXMLItems::CITIES_UNITPRODUCTION);
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_UNITPRODUCTIONID, QString::number(gameCityItem->GetUnitProduction()->GetGameUnitId()));
		xmlWriter.writeTextElement(SerializeXMLItems::CITIES_UNITPRODUCTIONPROGRESS, QString::number(gameCityItem->GetUnitProduction()->GetProductionProgress()));
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

	return UpdateGameConfig();
}

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

	GameDataFactory factory;
	return factory.CreateGameDataFromSaveGame(domNode);
}

//==============================================================================
bool SerializeXML::LoadPlayerData( const QDomNode& domNode )
{
	if (true == domNode.isNull())
	{
		return false;
	}

	GameOwnerFactory factory;
	bool successful = factory.Create(domNode);
	if (false == successful)
	{
		return false;
	}

	const GameOwner* human = GameOwnerRepository::GetInstance()->GetHuman();
	if (nullptr == human)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("No human player defined in save game!"));
		return false;
	}
	GameConfig::Player = const_cast<GameOwner*>(human);
	return true;
}

//==============================================================================
bool SerializeXML::LoadMapData( const QDomNode& domNode )
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameMapTileFactory gameMapItemFactory;
	return gameMapItemFactory.Create(domNode);
}

//==============================================================================
bool SerializeXML::LoadUnitData(const QDomNode& domNode)
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameUnitFactory gameUnitItemFactory;
	return gameUnitItemFactory.Create(domNode);
}

//==============================================================================
bool SerializeXML::LoadCityData(const QDomNode& domNode)
{
	if (true == domNode.isNull())
	{
		return false;
	}
	GameCityFactory factory;
	return factory.Create(domNode);
}

//==============================================================================
bool SerializeXML::UpdateGameConfig()
{
	GameConfig::Player = const_cast<GameOwner*>(GameOwnerRepository::GetInstance()->GetById(GameConfig::PlayerId));
	return GameConfig::Player != nullptr;
}
