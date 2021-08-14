#include "stdafx.h"
#include "ModelUnitTypeFactory.h"
#include "ModelUnitType.h"
#include "ModelUnitTypeRepository.h"
#include "ModelUnitTypeXMLItems.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "DomValueExtractor.h"
#include "DomNodeFinder.h"
#include "io/ConfigFileLoader.h"
#include <QtXml>
#include "LogInterface.h"

ModelUnitTypeFactory::ModelUnitTypeFactory()
{

}

ModelUnitTypeFactory::~ModelUnitTypeFactory()
{

}

bool ModelUnitTypeFactory::Create()
{
	ModelUnitTypeXMLItems config;

	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(config.CONFIG_FILE_NAME, config.ROOT_NAME))
	{
		return false;
	}

	ModelUnitTypeRepository::GetInstance()->Init();

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelUnitTypeRepository::GetInstance()->RegisterModelUnitType(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelUnitTypes registered: " + QString::number(ModelUnitTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelUnitType* ModelUnitTypeFactory::CreateFromXML(const QDomNode& node)
{
	ModelUnitTypeXMLItems config;
	int unitTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(config.SUBELEMENT_ID, unitTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelTerrainType has not element of name: %1").arg(config.SUBELEMENT_ID));
		return nullptr;
	}

	ModelUnitType *newUnitType = new ModelUnitType(unitTypeId);

	bool allElementsExtracted = true;
	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_NAME, newUnitType->Name);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_PICTURENAME, newUnitType->PictureName);
		allElementsExtracted &= AttacheImage(newUnitType);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_STRENGTH, newUnitType->Strength);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_ATTACK, newUnitType->Attack);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_DEFENCE, newUnitType->Defense);
	}

	{
		DomValueExtractor extractor(node);
		allElementsExtracted &= extractor.ExtractValue(config.SUBELEMENT_RANGE, newUnitType->Range);
	}

	{
		DomNodeFinder find(node);
		allElementsExtracted &= ExtractTerrainTypes(find.FindDomeNodeByName(config.NODE_TERRAINTYPES), newUnitType->ValidTerrainTypes);
	}

	if (false == allElementsExtracted)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(config.SUBELEMENT_ID).arg(QString::number(unitTypeId)));
		delete newUnitType;
		return nullptr;
	}
	return newUnitType;
}

bool ModelUnitTypeFactory::AttacheImage(ModelUnitType* modelUnit)
{
	QString imageName(modelUnit->GetPictureName());
	const QImage *image = LoadImage(imageName);

	if (image == nullptr)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("Unable to load terrain image: %1").arg(imageName));
		return false;
	}

	modelUnit->SetImage(image);
	return true;
}

const QImage* ModelUnitTypeFactory::LoadImage(const QString& path)
{
	QImage* newImage = new QImage;
	try
	{
		if (newImage->load(path) == false)
		{
			delete newImage;
			return nullptr;
		}
		return newImage;
	}
	catch (...)
	{
		delete newImage;
		return nullptr;
	}
	return newImage;
}

#include "ModelUnitTypeXMLItems.h"
#include "DomElementFinder.h"
bool ModelUnitTypeFactory::ExtractTerrainTypes(QDomNode domNode, QVector<int>& terrainTypes)
{
	if (true == domNode.isNull())
	{
		return false;
	}

	QDomNodeList childs = domNode.childNodes();
	if (true == childs.isEmpty())
	{
		return false;
	}

	int childCount = childs.count();

	for (int index = 0; index < childs.count(); index++)
	{
		QDomNode node = childs.at(index);
		if (node.nodeName() != ModelUnitTypeXMLItems::SUBELEMENT_TERRAINTYPEID)
		{
			continue;
		}
		
		if (false == node.isElement())
		{
			continue;
		}

		QDomElement element = node.toElement();
		int terrainTypeId = element.text().toInt();
		terrainTypes.push_back(terrainTypeId);
	}
	return !terrainTypes.isEmpty();
}


