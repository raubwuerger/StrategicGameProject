#include "stdafx.h"
#include "SaveToXML.h"
#include "LogInterface.h"
#include <QtXML>

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
		jha::GetLog()->Log( "Unable to create Savegame framework!", jha::LOGLEVEL::LL_ERROR );
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
	QString saveGameFileName("E:\\Projects\\StrategicGameProject\\GameDemonstrator\\save\\Testsavegame.xml");
	QFile file(saveGameFileName);

	if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		jha::GetLog()->Log( "Unable to create savegame file: " +saveGameFileName, jha::LOGLEVEL::LL_ERROR );
		return false;
	}

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();

	xmlWriter.writeStartElement("Savegame");

		xmlWriter.writeStartElement("Game");
			xmlWriter.writeTextElement("Version", "0.9" );
			xmlWriter.writeTextElement("Playercount", "2");
		xmlWriter.writeEndElement();
	
		xmlWriter.writeStartElement("Players");
			xmlWriter.writeTextElement("Player", "Spieler 1" );
			xmlWriter.writeTextElement("Player", "Spieler 2" );
		xmlWriter.writeEndElement();

		xmlWriter.writeStartElement("Map");
		xmlWriter.writeEndElement();

		xmlWriter.writeEndElement();

	file.close();
	jha::GetLog()->Log( "Succesfull create savegame: " +saveGameFileName, jha::LOGLEVEL::LL_INFO );

	return true;
}
