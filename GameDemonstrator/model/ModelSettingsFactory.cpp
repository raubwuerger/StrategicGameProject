#include "stdafx.h"
#include "ModelSettingsFactory.h"
#include "ModelSettings.h"
#include "LogInterface.h"

ModelSettingsFactory* ModelSettingsFactory::Instance = nullptr;

ModelSettingsFactory* ModelSettingsFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelSettingsFactory;
	return Instance;
}

void ModelSettingsFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

ModelSettingsFactory::ModelSettingsFactory()
{
	TheGameSettings = new ModelSettings();
}

ModelSettingsFactory::~ModelSettingsFactory()
{
	delete TheGameSettings;
}

ModelSettings* ModelSettingsFactory::Create()
{
/*	ModelSettings config;
	jha::GetLog()->Log_MESSAGE( QObject::tr("Loading %1 from file: %2").arg(config.RootName).arg(config.ModelSettingsFileName));
	QFile file(config.ConfigFilePath);
	if( false == OpenFile(&file) )
	{
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;

	if( domDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr) );
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if( root.tagName() != config.RootName) 
	{
		jha::GetLog()->Log( QObject::tr("The file is not an %1 file.").arg(config.RootName), jha::LOGLEVEL::LL_WARNING );
		return false;
	}

	if (root.hasAttribute(config.Version) && root.attribute(config.Version) != config.VersionNumber ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("The file is not an %1 file.").arg(config.RootName) );
		return false;
	}
	*/
	//TODO: Should be read from dialogs
	TheGameSettings->SaveGamePath = "";
	TheGameSettings->DifficultyLevel = "1";
	TheGameSettings->Players.push_back( "Player 1" );
	TheGameSettings->Players.push_back( "Player 2" );
	TheGameSettings->PlayerCount = TheGameSettings->Players.count();
	TheGameSettings->CurrentSaveGameFileName = "PlayerName_1900_01.xml"; //TODO: Sollte aus Dialog entnommen werden! -> Resume last game ...
	return TheGameSettings;
}

bool ModelSettingsFactory::OpenFile(QFile* file)
{
	if( file->open(QFile::ReadOnly | QFile::Text) == false )
	{
		jha::GetLog()->Log( QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()), jha::LOGLEVEL::LL_WARNING );
		return false;
	}
	return true;
}

