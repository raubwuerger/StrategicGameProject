#include "stdafx.h"
#include "GameUnitItemFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "game\GameOwnerItemRepository.h"
#include "game\GameOwnerItem.h"
#include "GameMapItemRepository.h"
#include "GameUnitItemRepository.h"
#include "GameUnitItem.h"
#include "GameMapItem.h"
#include "GameUnitItemRuntimeData.h"

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

	const GameOwnerItem* ownerItem = GetGameOwnerItem(obj);
	if (nullptr == ownerItem)
	{
		return nullptr;
	}

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == ownerItem->GetId())
	{
		return nullptr;
	}

	GameUnitItem *newUnitItem = new GameUnitItem(CreateId(obj));

	newUnitItem->UnitType = unitType;
	newUnitItem->UnitTypeId = unitType->GetId();

	newUnitItem->OwnerItem = ownerItem;
	newUnitItem->OwnerItemId = ownerItem->GetId();

	newUnitItem->MapItem = mapItem;
	newUnitItem->MapItemId = mapItem->GetId();

	newUnitItem->SetName(CreateName(unitType));
	Q_ASSERT(newUnitItem->InitRuntimeData());

	if (false == GameUnitItemRepository::GetInstance()->RegisterItem(newUnitItem))
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

	const GameOwnerItem* gameItem = GetGameOwnerItem(obj);
	if (nullptr == gameItem)
	{
		return nullptr;
	}

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameItem->GetId())
	{
		return nullptr;
	}

	gameUnitItem->UnitType = unitType;
	gameUnitItem->UnitTypeId = unitType->GetId();

	gameUnitItem->OwnerItem = gameItem;
	gameUnitItem->OwnerItemId = gameItem->GetId();

	gameUnitItem->MapItem = mapItem;
	gameUnitItem->MapItemId = mapItem->GetId();

	return gameUnitItem;
}

int GameUnitItemFactory::CreateId(const GameUnitParameterObject obj)
{
	if (-1 != obj.Id)
	{
		return obj.Id;  //Belongs to savegame
	}
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

const GameOwnerItem* GameUnitItemFactory::GetGameOwnerItem(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.GameOwnerItemObject)
	{
		return obj.GameOwnerItemObject;
	}
	return GameOwnerItemRepository::GetInstance()->GetItemById(obj.GameOwnerItemId);
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
	}

	return true;
}

#include "Model/ModelOwnerType.h"
GameUnitItem* GameUnitItemFactory::CreateUnitItemFromXML(const QDomNode& unitNode)
{
	QDomNodeList mapNodes = unitNode.childNodes();
	if (true == mapNodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("QDomNode has no child elements!"));
		return nullptr;
	}

	bool allElementsExtracted = true;

	int id = -1;
	
	DomValueExtractor domNodeListValueExtractor(unitNode);
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_ID, id);

	int unitTypeId = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_UNITTYPEID, unitTypeId);

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->GetModelUnitTypeById(unitTypeId);
	if (nullptr == modelUnitType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: ModelUnitType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(unitTypeId)));
		return nullptr;
	}

	int mapItemId = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_GAMEMAPITEMID, mapItemId);
	const GameMapItem* mapItem = GameMapItemRepository::GetInstance()->GetGameMapItemById(mapItemId);
	if (nullptr == mapItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: GameMapItem with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(mapItemId)));
		return nullptr;
	}

	int gameItemId = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_OWNERTYPEID, gameItemId);

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameItemId)
	{
		return nullptr;
	}
	const GameOwnerItem* ownerItem = GameOwnerItemRepository::GetInstance()->GetItemById(gameItemId);
	if (nullptr == ownerItem)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnitItem with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(gameItemId)));
		return nullptr;
	}

	QString unitName;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_NAME, unitName);

	QString currentStrength;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_STRENGTH, currentStrength);

	QString currentMovementPoints;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_MOVEMENTPOINTS, currentMovementPoints);

	if (false == allElementsExtracted)
	{
		Q_ASSERT(allElementsExtracted);
		return false;
	}

	GameUnitParameterObject obj;
	obj.GameMapItemObject = mapItem;
	obj.GameOwnerItemObject = ownerItem;
	obj.ModelUnitTypeObject = modelUnitType;
	obj.Id = id;

	GameUnitItem* created = CreateGameUnitItem(obj);
	if (nullptr == created)
	{
		return nullptr;
	}

	created->SetName(unitName);
	created->GetRuntimeData()->CurrentStrength = currentStrength.toInt();
	created->GetRuntimeData()->CurrentMovementPoints = currentMovementPoints.toInt();
	return created;
}

