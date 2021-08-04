#include "stdafx.h"
#include "ModelTerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelTerrainType.h"
#include "ModelTerrainXMLItems.h"
#include "ModelTerrainTypeRepository.h"
#include "DomValueExtractor.h"

ModelTerrainTypeFactory*	ModelTerrainTypeFactory::Instance = nullptr;

ModelTerrainTypeFactory* ModelTerrainTypeFactory::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new ModelTerrainTypeFactory;
	return Instance;
}

ModelTerrainTypeFactory::ModelTerrainTypeFactory()
{
}

ModelTerrainTypeFactory::~ModelTerrainTypeFactory()
{
}

void ModelTerrainTypeFactory::Release()
{
	delete Instance;
	Instance = nullptr;
}

bool ModelTerrainTypeFactory::Create()
{
	ModelTerrainXMLItems config;
	jha::GetLog()->Log_MESSAGE( QObject::tr("Loading %1 from file: %2").arg(config.RootName).arg(config.ConfigFilePath));
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

	QDomNodeList terrainTypeNodes = root.childNodes();
	for( int i=0; i <terrainTypeNodes.count(); i++ )
	{
		ModelTerrainTypeRepository::GetInstance()->RegisterTerrainType( CreateFromXML( terrainTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("TerrainTypes registered: " +QString::number(ModelTerrainTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

bool ModelTerrainTypeFactory::OpenFile( QFile* file )
{
	if( file->open(QFile::ReadOnly | QFile::Text) == false )
	{
		jha::GetLog()->Log( QObject::tr("Cannot read file %1:\n%2.").arg(file->fileName()).arg(file->errorString()), jha::LOGLEVEL::LL_WARNING );
		return false;
	}
	return true;
}

ModelTerrainType* ModelTerrainTypeFactory::CreateFromXML( const QDomNode& node )
{
	ModelTerrainXMLItems config;
	int terrainTypeId = 0;

	DomValueExtractor extractor(node);
	if( false == extractor.ExtractValue(config.SubelementId,terrainTypeId) )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("ModelTerrainType has not element of name: %1").arg(config.SubelementId) );
		return nullptr;
	}

	ModelTerrainType *newTerrainType = new ModelTerrainType( terrainTypeId );

	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementName,newTerrainType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementPicturePath,newTerrainType->PicturePath);
		allElementsExtracted &= AttacheImage( newTerrainType );
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementInfrastructure,newTerrainType->Infrastructure);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementOil,newTerrainType->Oil);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementTimber,newTerrainType->Timber);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementStone,newTerrainType->Stone);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementMovementModifier,newTerrainType->MovementModifier);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementDefenseModifier,newTerrainType->DefenseModifier);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SubelementAttackModifier,newTerrainType->AttackModifier);
	}

	if( false == allElementsExtracted )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to register %1 with id %2").arg(config.SubelementId).arg(QString::number(terrainTypeId)) );
		delete newTerrainType;
		return nullptr;
	}
	return newTerrainType;
}

bool ModelTerrainTypeFactory::AttacheImage( ModelTerrainType* modelTerrainType )
{
	QString terrainPicturePath(modelTerrainType->GetPicturePath());
	const QImage *terrainTypeImage = LoadTerrainTypeImage( terrainPicturePath );

	if( terrainTypeImage == nullptr )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Unable to load terrain image: %1").arg(terrainPicturePath));
		return false;
	}
	
	modelTerrainType->SetImage( terrainTypeImage );
	return true;
}

const QImage* ModelTerrainTypeFactory::LoadTerrainTypeImage( const QString& path )
{
	QImage* newImage = new QImage;
	try
	{
		if( newImage->load( path ) == false )
		{
			delete newImage;
			return nullptr;
		}
		return newImage;
	}
	catch( ... )
	{
		delete newImage;
		return nullptr;
	}
	return newImage;
}
