#include "stdafx.h"
#include "ModelOwnerTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelOwnerType.h"
#include "DomElementFinder.h"
#include "DomValueExtractor.h"
#include "ModelOwnerTypeXMLItems.h"
#include "ModelOwnerTypeRepository.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "io\ConfigFileLoader.h"

ModelOwnerTypeFactory::ModelOwnerTypeFactory()
{
}

ModelOwnerTypeFactory::~ModelOwnerTypeFactory()
{
}

bool ModelOwnerTypeFactory::Create()
{
	ModelOwnerTypeXMLItems config;

	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(config.CONFIG_FILE_NAME, config.ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelOwnerTypeRepository::GetInstance()->RegisterOwnerType(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("TerrainTypes registered: " + QString::number(ModelOwnerTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}
ModelOwnerType* ModelOwnerTypeFactory::CreateFromXML( const QDomNode& node )
{
	ModelOwnerTypeXMLItems config;
	int ownerTypeId = 0;

	DomValueExtractor extractor(node);
	if( false == extractor.ExtractValue(config.SUBELEMENT_ID,ownerTypeId) )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("OwnerType has not element of name: %1").arg(config.SUBELEMENT_ID) );
		return nullptr;
	}

	ModelOwnerType *newOwnerType = new ModelOwnerType( ownerTypeId );
	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_NAME,newOwnerType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_PICTURENAME,newOwnerType->PictureName);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_COLOR,newOwnerType->Color);
	}

	if( false == allElementsExtracted )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("Unable to register %1 with id %2").arg(config.SUBELEMENT_ID).arg(QString::number(ownerTypeId)) );
		delete newOwnerType;
		return nullptr;
	}

	return newOwnerType;
}
