#include "stdafx.h"
#include "ModelMapTypeCreatorFactoryAbstract.h"
#include "DomValueExtractor.h"
#include "DomNodeFinder.h"
#include "io/ConfigFileLoader.h"
#include <QtXml>
#include "LogInterface.h"
#include "ModelMapTypeXMLItems.h"
#include "ModelMapTypeRepository.h"

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
	return nullptr;
}
