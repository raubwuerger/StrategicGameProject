#include "stdafx.h"
#include "GameUnitItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "model\ModelOwnerTypeRepository.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"

GameUnitItemFactory::GameUnitItemFactory()
{
}

GameUnitItemFactory::~GameUnitItemFactory()
{
}

GameUnitItem* GameUnitItemFactory::CreateGameUnitItemFromScratch(const ModelUnitType* modelUnitType, int gameMapItemId)
{
	if (nullptr == modelUnitType)
	{
		return nullptr;
	}

	GameUnitItem *newUnitItem = new GameUnitItem(CreateId());
	newUnitItem->UnitType = modelUnitType;
	newUnitItem->SetGameMapItemId(gameMapItemId);
	newUnitItem->SetName(CreateName(modelUnitType));

	if (false == GameUnitItemRepository::GetInstance()->RegisterGameUnitItem(newUnitItem))
	{
		return nullptr;
	}

	return newUnitItem;
}

int GameUnitItemFactory::CreateId()
{
	return GameUnitItemRepository::GetInstance()->GetLastIndex();
}

QString GameUnitItemFactory::CreateName(const ModelUnitType* modelUnitType) const
{
	return modelUnitType->GetName();
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
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(units.nodeName()));
		return false;
	}

	GameUnitItemRepository::GetInstance()->Init();

	for (int nodeIndex = 0; nodeIndex < unitItemNodeList.count(); nodeIndex++)
	{
		GameUnitItem* created = CreateUnitItemFromXML(unitItemNodeList.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameUnitItem from savegame line number: %1").arg(QString::number(unitItemNodeList.at(nodeIndex).columnNumber())));
			continue;
		}
		if (false == GameUnitItemRepository::GetInstance()->RegisterGameUnitItem(created))
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameUnitItem from savegame line number: %1").arg(QString::number(unitItemNodeList.at(nodeIndex).columnNumber())));
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
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem: %1 not found!").arg(SerializeXMLItems::UNITS_ID));
			return nullptr;
		}
	}

	int unitTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_UNITTYPEID, unitTypeId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::UNITS_UNITTYPEID));
			return nullptr;
		}
	}

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->FindModelUnitTypeById(unitTypeId);
	if (nullptr == modelUnitType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: ModelUnitType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(unitTypeId)));
		return nullptr;
	}

	int mapItemId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_GAMEMAPITEMID, mapItemId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::UNITS_GAMEMAPITEMID));
			return nullptr;
		}
	}

	int ownerTypeId = -1;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_OWNERTYPEID, ownerTypeId))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::UNITS_OWNERTYPEID));
			return nullptr;
		}
	}
	const ModelOwnerType* ownerType = ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(ownerTypeId);
	if (nullptr == ownerType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(ownerTypeId)));
		return nullptr;
	}

	QString unitName;
	{
		DomValueExtractor domNodeListValueExtractor(unitNode);
		if (false == domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_NAME, unitName))
		{
			jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: %2 not found!").arg(QString::number(id)).arg(SerializeXMLItems::UNITS_NAME));
			return nullptr;
		}
	}

	GameUnitItem *newUnitItem = new GameUnitItem(id);
	newUnitItem->UnitType = modelUnitType;
	newUnitItem->GameMapItemId = mapItemId;
	newUnitItem->Name = unitName;
	newUnitItem->OwnerType = ownerType;
	return newUnitItem;
}

