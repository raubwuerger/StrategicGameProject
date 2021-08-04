#include "stdafx.h"
#include "ModelProgramFactory.h"
#include "ModelProgramXMLItems.h"
#include "ModelProgramSettings.h"
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
	ModelProgramSettingsInstance = new ModelProgramSettings();

	jha::GetLog()->Log_MESSAGE("Loading GameDemonstratorConfig from file: " +ModelProgramSettings::FileName);
	QFile file(ModelProgramSettings::FileName);
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
	if( root.tagName() != ModelProgramXMLItems::ROOT_NAME ) 
	{
		jha::GetLog()->Log_WARNING( QObject::tr("File %1 is not an %2 file.").arg(ModelProgramSettings::FileName).arg(ModelProgramXMLItems::ROOT_NAME) );
		return false;
	}

	QDomNodeList ownerTypeNodes = root.childNodes();
	for( int i=0; i <ownerTypeNodes.count(); i++ )
	{
		QString currentNodeName = ownerTypeNodes.at(i).nodeName();
		if( currentNodeName == ModelProgramXMLItems::NODE_LOGGING )
		{
			DomValueExtractor extractor(ownerTypeNodes.at(i));
			if( false == extractor.ExtractValue(ModelProgramXMLItems::SUBELEMENT_GLOBAL_LOG_LEVEL,ModelProgramSettings::GlobalLogLevel) )
			{
				jha::GetLog()->Log_WARNING( QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettings::FileName).arg(ModelProgramXMLItems::SUBELEMENT_GLOBAL_LOG_LEVEL) );
				return false;
			}
		}

		if( currentNodeName == ModelProgramXMLItems::NODE_DEBUG_MAP_SETTINGS )
		{
			{
				DomValueExtractor extractor(ownerTypeNodes.at(i));
				if( false == extractor.ExtractValue(ModelProgramXMLItems::SUBELEMENT_DEBUG_ROWS,ModelProgramSettings::DebugRows) )
				{
					jha::GetLog()->Log_WARNING( QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettings::FileName).arg(ModelProgramXMLItems::SUBELEMENT_DEBUG_ROWS) );
					return false;
				}
			}

			{
				DomValueExtractor extractor(ownerTypeNodes.at(i));
				if( false == extractor.ExtractValue(ModelProgramXMLItems::SUBELEMENT_DEBUG_COLS,ModelProgramSettings::DebugCols) )
				{
					jha::GetLog()->Log_WARNING( QObject::tr("File %1 contains no node %2.").arg(ModelProgramSettings::FileName).arg(ModelProgramXMLItems::SUBELEMENT_DEBUG_COLS) );
					return false;
				}
			}
		}

	}

	return true;
}

ModelProgramSettings* ModelProgramFactory::GetConfig()
{
	return ModelProgramSettingsInstance;
}

ModelProgramFactory::ModelProgramFactory()
	: ModelProgramSettingsInstance(nullptr)
{
}

ModelProgramFactory::~ModelProgramFactory()
{
	delete ModelProgramSettingsInstance;
	ModelProgramSettingsInstance = nullptr;
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

