#include "stdafx.h"
#include "GameUnitFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "model\ModelUnitType.h"
#include "model\ModelUnitTypeRepository.h"
#include "game\GameOwnerRepository.h"
#include "game\GameOwner.h"
#include "GameMapTileRepository.h"
#include "GameUnitRepository.h"
#include "GameUnit.h"
#include "GameMapTile.h"
#include "GameUnitRuntimeData.h"
#include "mapCreator/GameUnitCreatorSimple.h"
#include "GameUnitTransportContainerFactory.h"
#include "GameUnitHelper.h"

GameUnitFactory::GameUnitFactory()
{
}

GameUnitFactory::~GameUnitFactory()
{
}

bool GameUnitFactory::Create()
{
	GameUnitRepository::GetInstance()->Init();
	GameUnitCreatorSimple gameUnitCreatorSimple;
	return gameUnitCreatorSimple.Create();
}

GameUnit* GameUnitFactory::Create(const GameUnitParameterObject obj)
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

	const GameMapTile* gameMapTile = GetGameMapTile(obj);
	if (nullptr == gameMapTile)
	{
		return nullptr;
	}

	const GameOwner* gameOwner = GetGameOwner(obj);
	if (nullptr == gameOwner)
	{
		return nullptr;
	}

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameOwner->GetId())
	{
		return nullptr;
	}

	GameUnit *newGameUnit = new GameUnit(CreateId(obj));

	newGameUnit->UnitType = unitType;
	newGameUnit->UnitTypeId = unitType->GetId();

	newGameUnit->GameOwnerObject = gameOwner;
	newGameUnit->GameOwnerId = gameOwner->GetId();

	newGameUnit->GameMapTileObject = gameMapTile;
	newGameUnit->MapTileId = gameMapTile->GetId();

	newGameUnit->SetName(CreateName(unitType));
	Q_ASSERT(newGameUnit->InitRuntimeData());

	if (false == SetTransportCapacity(newGameUnit))
	{
		delete unitType;
		return nullptr;
	}

	if (false == GameUnitRepository::GetInstance()->Register(newGameUnit))
	{
		delete unitType;
		return nullptr;
	}

	return newGameUnit;
}

bool GameUnitFactory::SetTransportCapacity(GameUnit* gameUnit)
{
	if (false == GameUnitHelper::IsTransporter(gameUnit))
	{
		return true;
	}

	GameUnitTransportContainerFactory factory;
	if (false == gameUnit->SetGameUnitTransportContainer(factory.Create(gameUnit)))
	{
		return false;
	}
	return true;
}

GameUnit* GameUnitFactory::Update(const GameUnitParameterObject obj)
{
	if (nullptr == obj.GameUnitObject)
	{
		return nullptr;
	}
	
	GameUnit* gameUnit = GameUnitRepository::GetInstance()->GetById(obj.GameUnitObject->GetId());
	if (nullptr == gameUnit)
	{
		return nullptr;
	}

	const ModelUnitType* unitType = GetModelUnitType(obj);
	if (nullptr == unitType)
	{
		return nullptr;
	}

	const GameMapTile* gameMapTile = GetGameMapTile(obj);
	if (nullptr == gameMapTile)
	{
		return nullptr;
	}

	const GameOwner* gameOwner = GetGameOwner(obj);
	if (nullptr == gameOwner)
	{
		return nullptr;
	}

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameOwner->GetId())
	{
		return nullptr;
	}

	gameUnit->UnitType = unitType;
	gameUnit->UnitTypeId = unitType->GetId();

	gameUnit->GameOwnerObject = gameOwner;
	gameUnit->GameOwnerId = gameOwner->GetId();

	gameUnit->GameMapTileObject = gameMapTile;
	gameUnit->MapTileId = gameMapTile->GetId();

	return gameUnit;
}

GameUnit* GameUnitFactory::Update(const GameUnitParameterObject* obj)
{
	Q_ASSERT(obj);
	if (nullptr == obj->GameUnitObject)
	{
		return nullptr;
	}

	GameUnit* gameUnit = GameUnitRepository::GetInstance()->GetById(obj->GameUnitObject->GetId());
	if (nullptr == gameUnit)
	{
		return nullptr;
	}

	const ModelUnitType* unitType = GetModelUnitType(*obj);
	if (nullptr == unitType)
	{
		return nullptr;
	}

	const GameMapTile* gameMapTile = GetGameMapTile(*obj);
	if (nullptr == gameMapTile)
	{
		return nullptr;
	}

	const GameOwner* gameOwner = GetGameOwner(*obj);
	if (nullptr == gameOwner)
	{
		return nullptr;
	}

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameOwner->GetId())
	{
		return nullptr;
	}

	gameUnit->UnitType = unitType;
	gameUnit->UnitTypeId = unitType->GetId();

	gameUnit->GameOwnerObject = gameOwner;
	gameUnit->GameOwnerId = gameOwner->GetId();

	gameUnit->GameMapTileObject = gameMapTile;
	gameUnit->MapTileId = gameMapTile->GetId();

	return gameUnit;
}

int GameUnitFactory::CreateId(const GameUnitParameterObject obj)
{
	if (-1 != obj.Id)
	{
		return obj.Id;  //Belongs to savegame
	}
	return GameUnitRepository::GetInstance()->CreateNewId();
}

QString GameUnitFactory::CreateName(const ModelUnitType* modelUnitType) const
{
	return modelUnitType->GetName();
}

bool GameUnitFactory::Create(const QDomNode node)
{
	GameUnitRepository::GetInstance()->Init();
	return CreateUnits(node);
}

bool GameUnitFactory::Validate(const GameUnitParameterObject& obj) const
{
	if (-1 == obj.ModelUnitTypeId && nullptr == obj.ModelUnitTypeObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelUnitTypeId or ModelUnitTypeObject are invalid!"));
		return false;
	}
	
	if (-1 == obj.GameOwnerId && nullptr == obj.GameOwnerObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelOwnerTypeId or ModelOwnerTypeObject are invalid!"));
		return false;
	}

	if (-1 == obj.GameMapTileId && nullptr == obj.GameMapTileObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("GameMapId or GameMapObject are invalid!"));
		return false;
	}
	return true;
}

const ModelUnitType* GameUnitFactory::GetModelUnitType(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.ModelUnitTypeObject)
	{
		return obj.ModelUnitTypeObject;
	}
	return ModelUnitTypeRepository::GetInstance()->GetById(obj.ModelUnitTypeId);
}

const GameMapTile* GameUnitFactory::GetGameMapTile(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.GameMapTileObject)
	{
		return obj.GameMapTileObject;
	}
	return GameMapTileRepository::GetInstance()->GetById(obj.GameMapTileId);
}

const GameOwner* GameUnitFactory::GetGameOwner(const GameUnitParameterObject& obj) const
{
	if (nullptr != obj.GameOwnerObject)
	{
		return obj.GameOwnerObject;
	}
	return GameOwnerRepository::GetInstance()->GetById(obj.GameOwnerId);
}

bool GameUnitFactory::CreateUnits(const QDomNode& units)
{
	QDomNodeList nodes = units.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(units.nodeName()));
		return true;
	}

	for (int nodeIndex = 0; nodeIndex < nodes.count(); nodeIndex++)
	{
		GameUnit* created = CreateUnitFromXML(nodes.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameUnit from savegame line number: %1").arg(QString::number(nodes.at(nodeIndex).columnNumber())));
			continue;
		}
	}

	return true;
}

#include "Model/ModelOwnerType.h"
GameUnit* GameUnitFactory::CreateUnitFromXML(const QDomNode& unitNode)
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

	const ModelUnitType* modelUnitType = ModelUnitTypeRepository::GetInstance()->GetById(unitTypeId);
	if (nullptr == modelUnitType)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnit with id=%1: ModelUnitType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(unitTypeId)));
		return nullptr;
	}

	int gameMapTileId = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_GAMEMAPITEMID, gameMapTileId);
	const GameMapTile* gameMapTile = GameMapTileRepository::GetInstance()->GetById(gameMapTileId);
	if (nullptr == gameMapTile)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnit with id=%1: GameMap with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(gameMapTileId)));
		return nullptr;
	}

	int gameOwnerId = -1;
	allElementsExtracted &= domNodeListValueExtractor.ExtractValue(SerializeXMLItems::UNITS_OWNERTYPEID, gameOwnerId);

	const int NOT_ALLOWED_OWNER_TYPE = 1;
	if (NOT_ALLOWED_OWNER_TYPE == gameOwnerId)
	{
		return nullptr;
	}
	const GameOwner* gameOwner = GameOwnerRepository::GetInstance()->GetById(gameOwnerId);
	if (nullptr == gameOwner)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameUnit with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(gameOwnerId)));
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
	obj.GameMapTileObject = gameMapTile;
	obj.GameOwnerObject = gameOwner;
	obj.ModelUnitTypeObject = modelUnitType;
	obj.Id = id;

	GameUnit* created = Create(obj);
	if (nullptr == created)
	{
		return nullptr;
	}

	created->SetName(unitName);
	created->GetRuntimeData()->CurrentStrength = currentStrength.toInt();
	created->GetRuntimeData()->CurrentMovementPoints = currentMovementPoints.toInt();
//	created->GetRuntimeData()->TransportCapacity = 
	return created;
}

