#include "stdafx.h"
#include "ModelMapTypeCreatorFactoryAbstract.h"
#include "DomValueExtractor.h"
#include "DomNodeFinder.h"
#include "io/ConfigFileLoader.h"
#include <QtXml>
#include "LogInterface.h"
#include "ModelMapTypeXMLItems.h"
#include "ModelMapTypeRepository.h"
#include "ModelMapType.h"

bool ModelMapTypeCreatorFactoryAbstract::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelMapTypeXMLItems::CONFIG_FILE_NAME, ModelMapTypeXMLItems::ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelMapTypeRepository::GetInstance()->Register(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelUnitTypes registered: " + QString::number(ModelMapTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelMapType* ModelMapTypeCreatorFactoryAbstract::CreateFromXML(const QDomNode& node)
{
	int mapTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelMapTypeXMLItems::SUBELEMENT_ID, mapTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelTerrainType has not element of name: %1").arg(ModelMapTypeXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelMapType *newType = new ModelMapType(mapTypeId);

	bool allElementsExtracted = true;
	if (false == extractor.ExtractValue(ModelMapTypeXMLItems::SUBELEMENT_NAME, newType->Name))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelMapTypeXMLItems::SUBELEMENT_ID).arg(QString::number(mapTypeId)));
		delete newType;
		return nullptr;
	}
	return newType;
}
