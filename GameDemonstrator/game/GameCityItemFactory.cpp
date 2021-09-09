#include "stdafx.h"
#include "GameCityItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "GameOwnerItemRepository.h"
#include "GameOwnerItem.h"
#include "model\ModelCityTypeRepository.h"
#include "GameMapItemRepository.h"
#include "GameMapItem.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"
#include "GameCityItemRuntimeData.h"
#include "model/ModelCityType.h"
#include "gameController/GameObjectController.h"
#include "DomNodeFinder.h"
#include "GameUnitProduction.h"
#include "GameUnitProductionController.h"

GameCityItemFactory::GameCityItemFactory()
	: DefaultCityName("City")
{
}

GameCityItemFactory::~GameCityItemFactory()
{
}

int GameCityItemFactory::CreateId(const GameCityParameterObject obj)
{
	if (-1 != obj.Id)
	{
		return obj.Id; //Belongs to savegame
	}
	return GameCityItemRepository::GetInstance()->CreateNewId();
}

const ModelCityType* GameCityItemFactory::GetModelCityType(const GameCityParameterObject obj) const
{
	if (nullptr != obj.ModelCityTypeObject)
	{
		return obj.ModelCityTypeObject;
	}
	return ModelCityTypeRepository::GetInstance()->GetTypeById(obj.ModelCityTypeId);
}

const GameOwnerItem* GameCityItemFactory::GetGameOwnerItem(const GameCityParameterObject obj) const
{
	if (nullptr != obj.GameOwnerItemObject)
	{
		return obj.GameOwnerItemObject;
	}
	return GameOwnerItemRepository::GetInstance()->GetItemById(obj.GameOwnerItemId);
}

const GameMapItem* GameCityItemFactory::GetGameMapItem(const GameCityParameterObject obj) const
{
	if (nullptr != obj.GameMapItemObject)
	{
		return obj.GameMapItemObject;
	}
	return GameMapItemRepository::GetInstance()->GetGameMapItemById(obj.GameMapItemId);
}

QString GameCityItemFactory::CreateCityName(int cityId) const
{
	return DefaultCityName + " " + QString::number(cityId);
}

int GameCityItemFactory::GetBaseEfficency(int cityId) const
{
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(cityId);
	Q_ASSERT(modelCityType);
	return modelCityType->GetEfficiency();
}

int GameCityItemFactory::GetBaseStrength(int cityId) const
{
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(cityId);
	Q_ASSERT(modelCityType);
	return modelCityType->GetDefenceValue();
}

bool GameCityItemFactory::Create(const QDomNode city)
{
	return CreateItems(city);
}

GameCityItem* GameCityItemFactory::Create(const GameCityParameterObject obj)
{
	if (false == Validate(obj))
	{
		return nullptr;
	}

	const ModelCityType* cityItem = GetModelCityType(obj);
	if (nullptr == cityItem)
	{
		return nullptr;
	}

	const GameMapItem* mapItem = GetGameMapItem(obj);
	if (nullptr == mapItem)
	{
		return nullptr;
	}

	const GameOwnerItem* ownerItem = GetGameOwnerItem(obj);
	if (nullptr == ownerItem)
	{
		return nullptr;
	}

	GameCityItem *newItem = new GameCityItem(CreateId(obj));

	newItem->CityTypeId = cityItem->GetId();
	newItem->CityType = cityItem;

	newItem->OwnerItemId = ownerItem->GetId();
	newItem->OwnerItem = ownerItem;

	newItem->MapItemId = mapItem->GetId();
	newItem->MapItem = mapItem;

	newItem->Name = CreateCityName(newItem->GetId());
	newItem->InitRuntimeData();

	if (false == GameCityItemRepository::GetInstance()->RegisterItem(newItem))
	{
		Q_ASSERT(newItem);
		delete newItem;
		return nullptr;
	}

	return newItem;
}

bool GameCityItemFactory::Validate(const GameCityParameterObject obj)
{
	if (-1 == obj.ModelCityTypeId && nullptr == obj.ModelCityTypeObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelCityTypeId or ModelCityTypeObject are invalid!"));
		return false;
	}

	if (-1 == obj.GameOwnerItemId && nullptr == obj.GameOwnerItemObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelOwnerTypeId or ModelOwnerTypeObject are invalid!"));
		return false;
	}

	if (-1 == obj.GameMapItemId && nullptr == obj.GameMapItemObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("GameMapItemId or GameMapItemObject are invalid!"));
		return false;
	}
	return true;
}

bool GameCityItemFactory::CreateItems(const QDomNode& city)
{
	QDomNodeList itemNodeList = city.childNodes();
	if (true == itemNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(city.nodeName()));
		return false;
	}

	GameCityItemRepository::GetInstance()->Init();

	for (int nodeIndex = 0; nodeIndex < itemNodeList.count(); nodeIndex++)
	{
		GameCityItem* created = CreateItemFromXML(itemNodeList.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameCityItem from savegame line number: %1").arg(QString::number(itemNodeList.at(nodeIndex).columnNumber())));
			continue;
		}
	}

	return true;
}

#include "model/ModelCityTypeRepository.h"
GameCityItem* GameCityItemFactory::CreateItemFromXML(const QDomNode& node)
{
	QDomNodeList mapNodes = node.childNodes();
	if (true == mapNodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	bool allElementsExtracted = true;
	int id = -1;
	DomValueExtractor extractor(node);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_ID, id);

	int modelCityTypeId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_MODELCITYTYPEID, modelCityTypeId);

	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(modelCityTypeId);
	if (nullptr == modelCityType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: ModelCityType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(modelCityTypeId)));
		return nullptr;
	}

	int mapItemId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_GAMEMAPITEMID, mapItemId);

	const GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapItemId);
	if (nullptr == gameMapItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: GameMapItem with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(mapItemId)));
		return nullptr;
	}

	int ownerTypeId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_OWNERTYPEID, ownerTypeId);

	const GameOwnerItem* gameOwnerItem = GameOwnerItemRepository::GetInstance()->GetItemById(ownerTypeId);
	if (nullptr == gameOwnerItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(ownerTypeId)));
		return nullptr;
	}

	QString name;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_NAME, name);

	int efficiency = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_EFFICIENCY, efficiency);

	int spezializedUnitTypeId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_SPEZIALIZEDUNITTYPEID, spezializedUnitTypeId);

	int strength = 0;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_STRENGTH, strength);

	if (false == allElementsExtracted)
	{
		Q_ASSERT(allElementsExtracted);
		return nullptr;
	}

	GameCityParameterObject obj;
	obj.ModelCityTypeObject = modelCityType;
	obj.GameOwnerItemObject = gameOwnerItem;
	obj.GameMapItemObject = gameMapItem;
	obj.Id = id;

	GameCityItem *gameCityItem = Create(obj);
	if (nullptr == gameCityItem)
	{
		return nullptr;
	}

	DomNodeFinder find(node);
	GameUnitProduction* gameUnitProduction = CreateGameUnitProduction(find.FindDomeNodeByName(SerializeXMLItems::CITIES_UNITPRODUCTION), id);

	gameCityItem->GetRuntimeData()->CurrentEfficiency = efficiency;
	gameCityItem->GetRuntimeData()->BaseEfficiency = GetBaseEfficency(modelCityTypeId);
	gameCityItem->GetRuntimeData()->CurrentStrength = strength;
	gameCityItem->GetRuntimeData()->BaseStrength = GetBaseStrength(modelCityTypeId);
	gameCityItem->SetGameUnitProduction(gameUnitProduction);
	gameCityItem->Name = name;
	gameCityItem->SpezializedUnitTypeId = spezializedUnitTypeId;

	return gameCityItem;
}

GameUnitProduction* GameCityItemFactory::CreateGameUnitProduction(const QDomNode& domNode, int gameCityId)
{
	if (true == domNode.isNull())
	{
		return nullptr;
	}

	QDomNodeList childs = domNode.childNodes();
	if (true == childs.isEmpty())
	{
		return nullptr;
	}

	bool allElementsExtracted = true;
	int unitProductionId = NOT_INITIALIZED_INT;
	int unitProductionProgress = NOT_INITIALIZED_INT;

	DomValueExtractor extractor(domNode);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_UNITPRODUCTIONID, unitProductionId);
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_UNITPRODUCTIONPROGRESS, unitProductionProgress);

	if (false == allElementsExtracted)
	{
		return nullptr;
	}

	GameUnitProduction* gameUnitProduction = new GameUnitProduction(gameCityId);
	gameUnitProduction->SetGameUnitId(unitProductionId);
	gameUnitProduction->SetProductionProgress(unitProductionProgress);

	if (false == GameUnitProductionController::GetInstance()->RegisterGameUnitProduction(gameUnitProduction))
	{
		//TODO: Was soll hier geschehen???
	}
	return gameUnitProduction;
}
