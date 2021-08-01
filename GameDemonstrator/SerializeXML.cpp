#include "stdafx.h"
#include "SerializeXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "game/GameMainCounter.h"
#include "model/ModelMapRepository.h"
#include "model/ModelMapItem.h"
#include "model/ModelTerrainType.h"

SerializeXML::SerializeXML()
{
}

SerializeXML::~SerializeXML()
{
}

bool SerializeXML::SaveGame()
{
	if( false == CreateFramework() )
	{
		return false;
	}
	return false;
}

bool SerializeXML::LoadGame()
{
	return false;
}

bool SerializeXML::CreateFramework()
{
	QString saveGamePath(".\\savegames\\");
	QString saveGameFile(saveGamePath);
	saveGameFile += "PlayerName_";
	saveGameFile += GameMainCounter::GetInstance()->GetCurrentDate().toString( "yyyy_MM" );
	saveGameFile += ".xml";

	QDir().mkpath(".\\savegames\\");

	QFile file(saveGameFile);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		jha::GetLog()->Log_ERROR( QObject::tr("Unable to create savegame file: %1 ").arg(saveGameFile) );
		return false;
	}

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement("Savegame");

	if( false == SaveGame(xmlWriter) )
	{
		file.close();
		return false;
	}

	xmlWriter.writeEndElement();

	file.close();
	jha::GetLog()->Log_INFO( QObject::tr("Succesfull create savegame: %1").arg(saveGameFile) );

	return true;
}


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

bool SerializeXML::SaveGameData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Game");
		xmlWriter.writeTextElement("Version", "0.9" );
		xmlWriter.writeTextElement("Playercount", "2");
		xmlWriter.writeTextElement("Game Turn", GameMainCounter::GetInstance()->GetCurrentDate().toString("yyyy-MM"));
	xmlWriter.writeEndElement();
	return true;
}

bool SerializeXML::SavePlayerData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Players");
		xmlWriter.writeTextElement("Player", "Spieler 1" );
		xmlWriter.writeTextElement("Player", "Spieler 2" );
	xmlWriter.writeEndElement();
	return true;
}

bool SerializeXML::SaveMapData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Map");
	if( false == CreateMapItems(xmlWriter) )
	{
		xmlWriter.writeEndElement();
		return false;
	}
	xmlWriter.writeEndElement();
	return true;
}

bool SerializeXML::CreateMapItems(QXmlStreamWriter& xmlWriter)
{
	xmlWriter.writeStartElement("MapItems");

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
			if( false == CreateMapItem( xmlWriter, row.at(currentCol) ) )
			{
				return false;
			}
		}
	}

	xmlWriter.writeEndElement();
	return true;
}

bool SerializeXML::CreateMapItem(QXmlStreamWriter& xmlWriter, const ModelMapItem* modelMapItem)
{
	xmlWriter.writeStartElement("MapItem");
		xmlWriter.writeTextElement("ID",QString::number(modelMapItem->GetId()));
		xmlWriter.writeTextElement("Row",QString::number(modelMapItem->GetRow()));
		xmlWriter.writeTextElement("Col",QString::number(modelMapItem->GetCol()));
		xmlWriter.writeTextElement("TerrainType",QString::number(modelMapItem->GetTerrainType()->GetId()));
	xmlWriter.writeEndElement();
	return true;
}
