#include "stdafx.h"
#include "ModelProgramFactory.h"
#include "ModelGameXMLItems.h"
#include "LogInterface.h"
#include <QDomNode>
#include "DomValueExtractor.h"

ModelProgramFactory* ModelProgramFactory::Instance = nullptr;

ModelProgramFactory* ModelProgramFactory::GetInstance()
{
	if( nullptr != Instance ) 
	{
		return Instance;
	}

	Instance = new ModelProgramFactory;
	return Instance;
}

bool ModelProgramFactory::Create()
{
	jha::GetLog()->Log_MESSAGE("Loading GameDemonstratorConfig from file: " +GameDemonstratorConfigName);
	QFile file(GameDemonstratorConfigName);
	if( false == OpenFile(&file) )
	{
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument DomDocument;

	if( DomDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr) );
		return false;
	}

	QDomElement root = DomDocument.documentElement();
	if( root.tagName() != ModelGameXMLItems::RootName ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("The file is not an %1 file.").arg(ModelGameXMLItems::RootName) );
		return false;
	}

	GameDemonstratorConfigInstance = new ModelGameXMLItems();

	QDomNodeList ownerTypeNodes = root.childNodes();
	for( int i=0; i <ownerTypeNodes.count(); i++ )
	{
		if( ownerTypeNodes.at(i).nodeName() == ModelGameXMLItems::NodeLogging )
		{
			DomValueExtractor extractor(ownerTypeNodes.at(i));
			extractor.ExtractValue(ModelGameXMLItems::NodeLoggingGlobalLogLevel,ModelGameXMLItems::GlobalLogLevel);
		}
	}

	return true;
}

ModelGameXMLItems* ModelProgramFactory::GetConfig()
{
	return GameDemonstratorConfigInstance;
}

ModelProgramFactory::ModelProgramFactory()
	: GameDemonstratorConfigName(".\\conf\\GameDemonstrator.xml"),
	GameDemonstratorConfigInstance(nullptr)
{
}

ModelProgramFactory::~ModelProgramFactory()
{
	delete GameDemonstratorConfigInstance;
	GameDemonstratorConfigInstance = nullptr;
}

bool ModelProgramFactory::OpenFile( QFile* file )
{
	if( file->open(QFile::ReadOnly | QFile::Text) == false )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()) );
		return false;
	}
	return true;
}

void ModelProgramFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

