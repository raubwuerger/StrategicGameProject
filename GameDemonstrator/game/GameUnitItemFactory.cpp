#include "stdafx.h"
#include "GameUnitItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"

GameUnitItemFactory::GameUnitItemFactory()
{
}

GameUnitItemFactory::~GameUnitItemFactory()
{
}

bool GameUnitItemFactory::CreateGameUnitItemFromScratch()
{
	return false;
}

bool GameUnitItemFactory::CreateGameUnitItemsFromSaveGame(const QDomNode unitItemElements)
{
	return CreateUnitItems(unitItemElements);
}

bool GameUnitItemFactory::CreateUnitItems(const QDomNode& units)
{
	QDomNodeList unitItemNodeList = units.childNodes();
	if (true == unitItemNodeList.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNodeList has no child elements"));
		return false;
	}

	GameUnitItemRepository::GetInstance()->Init();

	for (int nodeIndex = 0; nodeIndex < unitItemNodeList.count(); nodeIndex++)
	{
		GameUnitItem* created = CreateUnitItemFromXML(unitItemNodeList.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(unitItemNodeList.at(nodeIndex).columnNumber())));
			return false;
		}
		if (false == GameUnitItemRepository::GetInstance()->RegisterGameUnitItem(created))
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create ModelMapItem from savegame line number: %1").arg(QString::number(unitItemNodeList.at(nodeIndex).columnNumber())));
			return false;
		}
	}

	return true;
}

GameUnitItem* GameUnitItemFactory::CreateUnitItemFromXML(const QDomNode& unitNode)
{
	QDomNodeList mapNodes = unitNode.childNodes();
	if (true == mapNodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	int id = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_ID, id))
		{
			return nullptr;
		}
	}

	int unitTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_UNITTYPEID, unitTypeId))
		{
			return nullptr;
		}
	}

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
	if (nullptr == modelUnitType)
	{
		return nullptr;
	}

	int mapItemId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_MAPITEMID, mapItemId))
		{
			return nullptr;
		}
	}

	QString unitName;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_NAME, unitName))
		{
			return nullptr;
		}
	}

	GameUnitItem *newUnitItem = new GameUnitItem(id);
	newUnitItem->SetModelUnitType(modelUnitType);
	newUnitItem->SetGameMapItemId(mapItemId);
	newUnitItem->SetName(unitName);
	return newUnitItem;
}
