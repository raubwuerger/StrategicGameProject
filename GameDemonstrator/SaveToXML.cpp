#include "stdafx.h"
#include "SaveToXML.h"
#include "LogInterface.h"
#include <QtXML>
#include "GameMainCounter.h"

SaveToXML::SaveToXML()
{
}

SaveToXML::~SaveToXML()
{
}

bool SaveToXML::SaveGame()
{
	if( false == CreateFramework() )
	{
		return false;
	}
	return false;
}

bool SaveToXML::LoadGame()
{
	return false;
}

bool SaveToXML::CreateFramework()
{
	QString saveGamePath(".\\savegames\\");
	QString saveGameFile(saveGamePath);
	saveGameFile += "PlayerName_";
	saveGameFile += GameMainCounter::GetInstance()->GetCurrentDate().toString( "yyyy_MM" );
	saveGameFile += ".xml";

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


bool SaveToXML::SaveGame( QXmlStreamWriter& xmlWriter )
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

bool SaveToXML::SaveGameData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Game");
		xmlWriter.writeTextElement("Version", "0.9" );
		xmlWriter.writeTextElement("Playercount", "2");
		xmlWriter.writeTextElement("Game Turn", GameMainCounter::GetInstance()->GetCurrentDate().toString("yyyy-MM"));
	xmlWriter.writeEndElement();
	return true;
}

bool SaveToXML::SavePlayerData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Players");
		xmlWriter.writeTextElement("Player", "Spieler 1" );
		xmlWriter.writeTextElement("Player", "Spieler 2" );
	xmlWriter.writeEndElement();
	return true;
}

bool SaveToXML::SaveMapData( QXmlStreamWriter& xmlWriter )
{
	xmlWriter.writeStartElement("Map");
	for(int i=0;i<100;i++)
	{
		xmlWriter.writeTextElement("Tile", QString::number(i) );
	}
	xmlWriter.writeEndElement();
	return true;
}
