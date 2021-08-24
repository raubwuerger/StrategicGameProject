#include "stdafx.h"
#include "GameCityItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelOwnerTypeRepository.h"
#include "model\ModelOwnerType.h"
#include "model\ModelCityTypeRepository.h"
#include "GameMapItemRepository.h"
#include "GameMapItem.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"
#include "model/ModelCityType.h"

GameCityItemFactory::GameCityItemFactory()
{
}

GameCityItemFactory::~GameCityItemFactory()
{
}

int GameCityItemFactory::CreateId()
{
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

const ModelOwnerType* GameCityItemFactory::GetModelOwnerType(const GameCityParameterObject obj) const
{
	if (nullptr != obj.ModelOwnerTypeObject)
	{
		return obj.ModelOwnerTypeObject;
	}
	return ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(obj.ModelOwnerTypeId);
}

const GameMapItem* GameCityItemFactory::GetGameMapItem(const GameCityParameterObject obj) const
{
	if (nullptr != obj.GameMapItemObject)
	{
		return obj.GameMapItemObject;
	}
	return GameMapItemRepository::GetInstance()->GetGameMapItemById(obj.GameMapItemId);
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

	const ModelOwnerType* ownerType = GetModelOwnerType(obj);
	if (nullptr == ownerType)
	{
		return nullptr;
	}

	GameCityItem *newItem = new GameCityItem( CreateId() );

	newItem->CityTypeId = cityItem->GetId();
	newItem->CityType = cityItem;

	newItem->OwnerTypeId = ownerType->GetId();
	newItem->OwnerType = ownerType;

	newItem->MapItemId = mapItem->GetId();
	newItem->MapItem = mapItem;

	if (false == GameCityItemRepository::GetInstance()->RegisterItem(newItem))
	{
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

	if (-1 == obj.ModelOwnerTypeId && nullptr == obj.ModelOwnerTypeObject)
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
		if (false == GameCityItemRepository::GetInstance()->RegisterItem(created))
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameCityItem from savegame line number: %1").arg(QString::number(itemNodeList.at(nodeIndex).columnNumber())));
			return false;
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

	int id = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_ID, id))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem: %1 not found!").arg(SerializeXMLItems::CITIES_ID));
			return nullptr;
		}
	}

	int cityTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_CITYTYPEID, cityTypeId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem: %1 not found!").arg(SerializeXMLItems::CITIES_ID));
			return nullptr;
		}
	}
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(cityTypeId);
	if (nullptr == modelCityType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: ModelCityType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(cityTypeId)));
		return nullptr;
	}

	int mapItemId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_GAMEMAPITEMID, mapItemId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::CITIES_GAMEMAPITEMID));
			return nullptr;
		}
	}
	const GameMapItem* gameMapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapItemId);
	if (nullptr == gameMapItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: GameMapItem with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(mapItemId)));
		return nullptr;
	}

	int ownerTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_OWNERTYPEID, ownerTypeId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::CITIES_OWNERTYPEID));
			return nullptr;
		}
	}
	const ModelOwnerType* modelOwnerType = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);
	if (nullptr == modelOwnerType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(ownerTypeId)));
		return nullptr;
	}

	QString name;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_NAME, name))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::CITIES_NAME));
			return nullptr;
		}
	}

	int efficiency = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_EFFICIENCY, efficiency))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::CITIES_EFFICIENCY));
			return nullptr;
		}
	}

	int spezializedUnitTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(node);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::CITIES_SPEZIALIZEDUNITTYPEID, spezializedUnitTypeId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCityItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::CITIES_SPEZIALIZEDUNITTYPEID));
			return nullptr;
		}
	}

	GameCityParameterObject obj;
	obj.ModelCityTypeObject = modelCityType;
	obj.ModelOwnerTypeObject = modelOwnerType;
	obj.GameMapItemObject = gameMapItem;

	return Create(obj);
}
