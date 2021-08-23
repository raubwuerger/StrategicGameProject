#include "stdafx.h"
#include "GameUnitItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "model\ModelOwnerTypeRepository.h"
#include "model\ModelOwnerType.h"
#include "GameMapItemRepository.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"
#include "GameMapItem.h"

GameUnitItemFactory::GameUnitItemFactory()
{
}

GameUnitItemFactory::~GameUnitItemFactory()
{
}

GameUnitItem* GameUnitItemFactory::CreateGameUnitItem(const GameUnitParameterObject obj)
{
	if (false == Validate(obj))
	{
		return nullptr;
	}

	const ModelUnitType* unitType = GetModelUnitType(obj);
	if (nullptr == unitType)
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

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == ownerType->GetId())
	{
		return nullptr;
	}

	GameUnitItem *newUnitItem = new GameUnitItem(CreateId());

	newUnitItem->UnitType = unitType;
	newUnitItem->UnitTypeId = unitType->GetId();

	newUnitItem->OwnerType = ownerType;
	newUnitItem->OwnerTypeId = ownerType->GetId();

	newUnitItem->MapItem = mapItem;
	newUnitItem->MapItemId = mapItem->GetId();

	newUnitItem->SetName(CreateName(unitType));

	if (false == GameUnitItemRepository::GetInstance()->RegisterGameUnitItem(newUnitItem))
	{
		delete unitType;
		return nullptr;
	}

	return newUnitItem;
}

GameUnitItem* GameUnitItemFactory::UpdateGameUnitItem(const GameUnitParameterObject obj)
{
	if (nullptr == obj.GameUnitItemObject)
	{
		return nullptr;
	}
	
	GameUnitItem* gameUnitItem = GameUnitItemRepository::GetInstance()->GetGameUnitItemById(obj.GameUnitItemObject->GetId());
	if (nullptr == gameUnitItem)
	{
		return nullptr;
	}

	const ModelUnitType* unitType = GetModelUnitType(obj);
	if (nullptr == unitType)
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

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == ownerType->GetId())
	{
		return nullptr;
	}

	gameUnitItem->UnitType = unitType;
	gameUnitItem->UnitTypeId = unitType->GetId();

	gameUnitItem->OwnerType = ownerType;
	gameUnitItem->OwnerTypeId = ownerType->GetId();

	gameUnitItem->MapItem = mapItem;
	gameUnitItem->MapItemId = mapItem->GetId();

	return gameUnitItem;
}

int GameUnitItemFactory::CreateId()
{
	return GameUnitItemRepository::GetInstance()->CreateNewId();
}

QString GameUnitItemFactory::CreateName(const ModelUnitType* modelUnitType) const
{
	return modelUnitType->GetName();
}

bool GameUnitItemFactory::CreateGameUnitItemsFromSaveGame(const QDomNode unitItemElements)
{
	return CreateUnitItems(unitItemElements);
}

bool GameUnitItemFactory::Validate(const GameUnitParameterObject& obj) const
{
	if (-1 == obj.ModelUnitTypeId && nullptr == obj.ModelUnitTypeObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelUnitTypeId or ModelUnitTypeObject are invalid!"));
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

const ModelUnitType* GameUnitItemFactory::GetModelUnitType(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.ModelUnitTypeObject)
	{
		return obj.ModelUnitTypeObject;
	}
	return ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(obj.ModelUnitTypeId);
}

const GameMapItem* GameUnitItemFactory::GetGameMapItem(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.GameMapItemObject)
	{
		return obj.GameMapItemObject;
	}
	return GameMapItemRepository::GetInstance()->GetGameMapItemById(obj.GameMapItemId);
}

const ModelOwnerType* GameUnitItemFactory::GetModelOwnerType(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.ModelOwnerTypeObject)
	{
		return obj.ModelOwnerTypeObject;
	}
	return ModelOwnerTypeRepository::GetInstance()->GetOwnerTypeById(obj.ModelOwnerTypeId);
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

//TODO: Sollte ein GameUnitParameterObject erstellen!
#include "Model/ModelOwnerType.h"
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

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(unitTypeId);
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
	const GameMapItem* mapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapItemId);
	if (nullptr == mapItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: GameMapItem with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(mapItemId)));
		return nullptr;
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
	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == ownerTypeId)
	{
		return nullptr;
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
	newUnitItem->UnitTypeId = modelUnitType->GetId();

	newUnitItem->OwnerType = ownerType;
	newUnitItem->OwnerTypeId = ownerType->GetId();

	newUnitItem->MapItem = mapItem;
	newUnitItem->MapItemId = mapItem->GetId();

	newUnitItem->Name = unitName;
	return newUnitItem;
}

