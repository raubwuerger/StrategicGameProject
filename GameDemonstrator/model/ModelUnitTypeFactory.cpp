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
#include "ImageLoader.h"

ModelUnitTypeFactory::ModelUnitTypeFactory()
{

}

ModelUnitTypeFactory::~ModelUnitTypeFactory()
{

}

bool ModelUnitTypeFactory::Create()
{
	ConfigFileLoader configFileLoader;
	if (false == configFileLoader.LoadConfig(ModelUnitTypeXMLItems::CONFIG_FILE_NAME, ModelUnitTypeXMLItems::ROOT_NAME))
	{
		return false;
	}

	QDomNodeList terrainTypeNodes = configFileLoader.GetQDomNodeList();
	for (int i = 0; i < terrainTypeNodes.count(); i++)
	{
		ModelUnitTypeRepository::GetInstance()->Register(CreateFromXML(terrainTypeNodes.at(i)));
	}
	jha::GetLog()->Log("ModelUnitTypes registered: " + QString::number(ModelUnitTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);

	return true;
}

ModelUnitType* ModelUnitTypeFactory::CreateFromXML(const QDomNode& node)
{
	int unitTypeId = 0;

	DomValueExtractor extractor(node);
	if (false == extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_ID, unitTypeId))
	{
		jha::GetLog()->Log_WARNING(QObject::tr("ModelTerrainType has not element of name: %1").arg(ModelUnitTypeXMLItems::SUBELEMENT_ID));
		return nullptr;
	}

	ModelUnitType *newType = new ModelUnitType(unitTypeId);

	bool allElementsExtracted = true;
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_NAME, newType->Name);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_PICTURENAME, newType->PictureName);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_STRENGTH, newType->Strength);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_MOVEMENTPOINTSPERTURN, newType->MovementPointsPerTurn);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_MOVEMENTPOINTSOVERALL, newType->MovementPointsOverall);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_ATTACKRANGE, newType->Range);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_CANOCCUPIECITY, newType->CanOccupieCity);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_GETCOUNTERATTACK, newType->ReceiveCounterattack);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_PRODUCTIONCOST, newType->ProductionCost);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_TERRAINDOMAIN, newType->TerrainDomain);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_CAN_UNIT_BE_TRANSPORTED, newType->CanUnitBeTransported);

	DomNodeFinder find(node);
	allElementsExtracted &= ParseAttackValues(find.FindDomeNodeByName(ModelUnitTypeXMLItems::SUBELEMENT_ATTACKVALUES), newType->AttackValues);
	allElementsExtracted &= ParseDefenseValues(find.FindDomeNodeByName(ModelUnitTypeXMLItems::SUBELEMENT_DEFENCEVALUES), newType->DefenseValues);
	allElementsExtracted &= ParseTerrainTypes(find.FindDomeNodeByName(ModelUnitTypeXMLItems::NODE_ACCESSIBLETERRAINTYPES), newType->AccessibleTerrainTypes);
	allElementsExtracted &= ParseAttackableUnitTypes(find.FindDomeNodeByName(ModelUnitTypeXMLItems::NODE_ATTACKABLE_UNITTYPES), newType->AttackableUnitTypes);
	allElementsExtracted &= ParseRecognisableUnitTypes(find.FindDomeNodeByName(ModelUnitTypeXMLItems::NODE_RECOGNISABLE_UNITTYPES), newType->RecognisableUnitTypes);
	allElementsExtracted &= ParseTransportCapacity(find.FindDomeNodeByName(ModelUnitTypeXMLItems::SUBELEMENT_TRANSPORTCAPACITY), newType->TransportCapacity);

	if (false == allElementsExtracted)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to register %1 with id %2").arg(ModelUnitTypeXMLItems::SUBELEMENT_ID).arg(QString::number(unitTypeId)));
		delete newType;
		return nullptr;
	}

	allElementsExtracted &= AttacheImage(newType);
	return newType;
}

bool ModelUnitTypeFactory::AttacheImage(ModelUnitType* type)
{
	QString imageName(type->GetPictureName());
	const QImage *image = ImageLoader::LoadImage(type->GetPictureName());

	if (image == nullptr)
	{
		jha::GetLog()->Log_WARNING(QObject::tr("Unable to load terrain image: %1").arg(imageName));
		return false;
	}

	type->Image = image;
	return true;
}

#include "ModelUnitTypeXMLItems.h"
#include "DomElementFinder.h"
bool ModelUnitTypeFactory::ParseTerrainTypes(const QDomNode& domNode, QVector<int>& terrainTypes)
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

bool ModelUnitTypeFactory::ParseAttackValues(const QDomNode& node, QVector<int>& attackValues)
{
	if (true == node.isNull())
	{
		return false;
	}

	attackValues.push_back(0);
	attackValues.push_back(0);
	attackValues.push_back(0);

	bool allElementsExtracted = true;
	DomValueExtractor extractor(node);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_LAND, attackValues[0]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_AIR, attackValues[1]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_SEA, attackValues[2]);

	return allElementsExtracted;
}

bool ModelUnitTypeFactory::ParseDefenseValues(const QDomNode& node, QVector<int>& defenseValues)
{
	if (true == node.isNull())
	{
		return false;
	}

	defenseValues.push_back(0);
	defenseValues.push_back(0);
	defenseValues.push_back(0);

	bool allElementsExtracted = true;
	DomValueExtractor extractor(node);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_LAND, defenseValues[0]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_AIR, defenseValues[1]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_SEA, defenseValues[2]);

	return allElementsExtracted;
}

bool ModelUnitTypeFactory::ParseAttackableUnitTypes(const QDomNode& domNode, QVector<int>& attackableUnitTypes)
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
		if (node.nodeName() != ModelUnitTypeXMLItems::SUBELEMENT_ATTACKABLE_UNITTYPE)
		{
			continue;
		}

		if (false == node.isElement())
		{
			continue;
		}

		QDomElement element = node.toElement();
		attackableUnitTypes.push_back(element.text().toInt());
	}
	return !attackableUnitTypes.isEmpty();
}

bool ModelUnitTypeFactory::ParseRecognisableUnitTypes(const QDomNode& domNode, QVector<int>& recognisableUnitTypes)
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
		if (node.nodeName() != ModelUnitTypeXMLItems::SUBELEMENT_RECOGNISABLE_UNITTYPE)
		{
			continue;
		}

		if (false == node.isElement())
		{
			continue;
		}

		QDomElement element = node.toElement();
		recognisableUnitTypes.push_back(element.text().toInt());
	}
	return !recognisableUnitTypes.isEmpty();
}

bool ModelUnitTypeFactory::ParseTransportCapacity(const QDomNode& node, QVector<int>& transportCapacity)
{
	if (true == node.isNull())
	{
		return false;
	}

	if (true == node.isNull())
	{
		return false;
	}

	transportCapacity.push_back(0);
	transportCapacity.push_back(0);
	transportCapacity.push_back(0);

	bool allElementsExtracted = true;
	DomValueExtractor extractor(node);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_LAND, transportCapacity[0]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_AIR, transportCapacity[1]);
	allElementsExtracted &= extractor.ExtractValue(ModelUnitTypeXMLItems::SUBELEMENT_DOMAIN_SEA, transportCapacity[2]);

	return allElementsExtracted;
}

