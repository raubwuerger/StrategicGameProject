#include "stdafx.h"
#include "ModelCityTypeFactory.h"
#include <QDomNode>
#include "LogInterface.h"
#include "ModelCityType.h"
#include "DomElementFinder.h"
#include "DomValueExtractor.h"
#include "ModelCityTypeXMLItems.h"
#include "ModelCityTypeRepository.h"
#include "ModelConfigurationHeaderXMLItems.h"
#include "io\ConfigFileLoader.h"
#include "ImageLoader.h"
#include "DomNodeFinder.h"

ModelCityTypeFactory::ModelCityTypeFactory()
{
}

ModelCityTypeFactory::~ModelCityTypeFactory()
{
}

bool ModelCityTypeFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelCityTypeXMLItems::CONFIG_FILE_NAME, ModelCityTypeXMLItems::ROOT_NAME))
	{
		return false;
	}

	ModelCityTypeRepository::GetInstance()->Init();

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelCityTypeRepository::GetInstance()->RegisterType(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelCityTypes registered: " + QString::number(ModelCityTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelCityType* ModelCityTypeFactory::CreateFromXML( const QDomNode& node )
{
	int ownerTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_ID, ownerTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("CityType has not element of name: %1").arg(ModelCityTypeXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelCityType *newType = new ModelCityType( ownerTypeId );
	bool allElementsExtracted = true;
	allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_NAME, newType->Name);
	allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_PICTURENAME, newType->PictureName);
	allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_EFFICIENCY, newType->Efficiency);
	allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_SPECIALIZED, newType->SpezializedUnitType);
	allElementsExtracted &= extractor.ExtractValue(ModelCityTypeXMLItems::SUBELEMENT_DEFENSEVALUES, newType->DefenceValue);

	DomNodeFinder finder(node);
	allElementsExtracted &= ParsePlacableTerrainTypes(finder.FindDomeNodeByName(ModelCityTypeXMLItems::NODE_ACCESSIBLETERRAINTYPES), newType->PlacableTerrainTypes);

	if (false == allElementsExtracted)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelCityTypeXMLItems::SUBELEMENT_ID).arg(QString::number(ownerTypeId)));
		delete newType;
		return nullptr;
	}

	allElementsExtracted &= AttacheImage(newType);
	return newType;
}

bool ModelCityTypeFactory::AttacheImage(ModelCityType* type)
{
	const QImage *terrainTypeImage = ImageLoader::LoadImage(type->GetPictureName());

	if (terrainTypeImage == nullptr)
	{
		return false;
	}

	type->Image = terrainTypeImage;
	return true;

}

bool ModelCityTypeFactory::ParsePlacableTerrainTypes(const QDomNode& domNode, QVector<int>& terrainTypes)
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
		if (node.nodeName() != ModelCityTypeXMLItems::SUBELEMENT_TERRAINTYPEID)
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
