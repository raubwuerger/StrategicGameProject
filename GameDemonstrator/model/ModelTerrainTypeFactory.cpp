#include "stdafx.h"
#include "ModelTerrainTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelTerrainType.h"
#include "ModelTerrainXMLItems.h"
#include "ModelTerrainTypeRepository.h"
#include "DomValueExtractor.h"
#include "io/ConfigFileLoader.h"
#include "ImageLoader.h"

ModelTerrainTypeFactory::ModelTerrainTypeFactory()
{
}

ModelTerrainTypeFactory::~ModelTerrainTypeFactory()
{
}

bool ModelTerrainTypeFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelTerrainXMLItems::CONFIG_FILE_NAME, ModelTerrainXMLItems::ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for( int i=0; i <terrainTypeNodes.count(); i++ )
	{
		ModelTerrainTypeRepository::GetInstance()->Register( CreateFromXML( terrainTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("ModelTerrainTypes registered: " +QString::number(ModelTerrainTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelTerrainType* ModelTerrainTypeFactory::CreateFromXML( const QDomNode& node )
{
	int terrainTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_ID, terrainTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelTerrainType has not element of name: %1").arg(ModelTerrainXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelTerrainType *newType = new ModelTerrainType( terrainTypeId );

	bool allElementsExtracted = true;
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_NAME, newType->Name);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_PICTURENAME, newType->PictureName);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_INFRASTRUCTURE, newType->Infrastructure);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_OIL, newType->Oil);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_TIMBER, newType->Timber);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_STONE, newType->Stone);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_MOVEMENT_MODIFIER, newType->MovementModifier);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_DEFENSE_MODIFIER, newType->DefenseModifier);
	allElementsExtracted &= extractor.ExtractValue(ModelTerrainXMLItems::SUBELEMENT_ATTACK_MODIFIER, newType->AttackModifier);

	if( false == allElementsExtracted )
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelTerrainXMLItems::SUBELEMENT_ID).arg(QString::number(terrainTypeId)));
		delete newType;
		return nullptr;
	}

	allElementsExtracted &= AttacheImage(newType);
	return newType;
}

bool ModelTerrainTypeFactory::AttacheImage( ModelTerrainType* type )
{
	const QImage *terrainTypeImage = ImageLoader::LoadImage(type->GetPictureName());

	if( terrainTypeImage == nullptr )
	{
		return false;
	}
	
	type->SetImage(terrainTypeImage);
	return true;
}
