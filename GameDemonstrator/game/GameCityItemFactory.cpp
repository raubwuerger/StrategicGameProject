#include "stdafx.h"
#include "GameCityItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelOwnerTypeRepository.h"
#include "model\ModelOwnerType.h"
#include "GameMapItemRepository.h"
#include "GameMapItem.h"
#include "GameCityItemRepository.h"
#include "GameCityItem.h"

GameCityItemFactory::GameCityItemFactory()
{
}

GameCityItemFactory::~GameCityItemFactory()
{
}

int GameCityItemFactory::CreateId()
{
	return GameCityItemRepository::GetInstance()->GetLastIndex();
}

bool GameCityItemFactory::Create(const QDomNode city)
{
	return CreateItems(city);
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
	const GameMapItem* mapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapItemId);
	if (nullptr == mapItem)
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
	const ModelOwnerType* ownerType = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);
	if (nullptr == ownerType)
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

	GameCityItem *newItem = new GameCityItem(id);

	newItem->CityType = modelCityType;
	newItem->CityTypeId = cityTypeId;
	
	newItem->OwnerType = ownerType;
	newItem->OwnerTypeId = ownerTypeId;

	newItem->MapItem = mapItem;
	newItem->MapItemId = mapItemId;

	newItem->Name = name;

	newItem->Efficiency = efficiency;
	newItem->SpezializedUnitTypeId = spezializedUnitTypeId;

	return newItem;
}
