#include "stdafx.h"
#include "ModelTerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelTerrainType.h"
#include "ModelTerrainXMLItems.h"
#include "ModelTerrainTypeRepository.h"
#include "DomValueExtractor.h"
#include "io/ConfigFileLoader.h"

ModelTerrainTypeFactory::ModelTerrainTypeFactory()
{
}

ModelTerrainTypeFactory::~ModelTerrainTypeFactory()
{
}

bool ModelTerrainTypeFactory::Create()
{
	ModelTerrainXMLItems config;

	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(config.CONFIG_FILE_NAME, config.ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for( int i=0; i <terrainTypeNodes.count(); i++ )
	{
		ModelTerrainTypeRepository::GetInstance()->RegisterTerrainType( CreateFromXML( terrainTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("ModelTerrainTypes registered: " +QString::number(ModelTerrainTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelTerrainType* ModelTerrainTypeFactory::CreateFromXML( const QDomNode& node )
{
	ModelTerrainXMLItems config;
	int terrainTypeId = 0;

	DomValueExtractor extractor(node);
	if( false == extractor.ExtractValue(config.SUBELEMENT_ID,terrainTypeId) )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("ModelTerrainType has not element of name: %1").arg(config.SUBELEMENT_ID) );
		return nullptr;
	}

	ModelTerrainType *newTerrainType = new ModelTerrainType( terrainTypeId );

	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_NAME,newTerrainType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_PICTURENAME,newTerrainType->PictureName);
		allElementsExtracted &= AttacheImage( newTerrainType );
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_INFRASTRUCTURE,newTerrainType->Infrastructure);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_OIL,newTerrainType->Oil);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_TIMBER,newTerrainType->Timber);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_STONE,newTerrainType->Stone);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_MOVEMENT_MODIFIER,newTerrainType->MovementModifier);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_DEFENSE_MODIFIER,newTerrainType->DefenseModifier);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_ATTACK_MODIFIER,newTerrainType->AttackModifier);
	}

	if( false == allElementsExtracted )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to register %1 with id %2").arg(config.SUBELEMENT_ID).arg(QString::number(terrainTypeId)) );
		delete newTerrainType;
		return nullptr;
	}
	return newTerrainType;
}

bool ModelTerrainTypeFactory::AttacheImage( ModelTerrainType* modelTerrainType )
{
	QString terrainPictureName(modelTerrainType->GetPictureName());
	const QImage *terrainTypeImage = LoadTerrainTypeImage( terrainPictureName );

	if( terrainTypeImage == nullptr )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Unable to load terrain image: %1").arg(terrainPictureName));
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
