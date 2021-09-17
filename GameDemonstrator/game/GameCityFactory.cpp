#include "stdafx.h"
#include "GameCityFactory.h"
#include <QtXml>
#include "LogInterface.h"
#include "DomValueExtractor.h"
#include "io\SerializeXMLItems.h"
#include "GameOwnerRepository.h"
#include "GameOwner.h"
#include "model\ModelCityTypeRepository.h"
#include "GameMapTileRepository.h"
#include "GameMapTile.h"
#include "GameCityRepository.h"
#include "GameCity.h"
#include "GameCityRuntimeData.h"
#include "model/ModelCityType.h"
#include "DomNodeFinder.h"
#include "GameUnitProduction.h"
#include "GameUnitProductionController.h"

GameCityFactory::GameCityFactory()
	: DefaultCityName("City")
{
}

GameCityFactory::~GameCityFactory()
{
}

bool GameCityFactory::Create()
{
	return GameOwnerRepository::GetInstance()->Init();
}

GameCity* GameCityFactory::Create(const GameCityParameterObject obj)
{
	if (false == Validate(obj))
	{
		return nullptr;
	}

	const ModelCityType* cityType = GetModelCityType(obj);
	if (nullptr == cityType)
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

	GameCity *newGameCity = new GameCity(CreateId(obj));

	newGameCity->CityTypeId = cityType->GetId();
	newGameCity->CityType = cityType;

	newGameCity->GameOwnerId = gameOwner->GetId();
	newGameCity->GameOwnerObject = gameOwner;

	newGameCity->GameMapTileId = gameMapTile->GetId();
	newGameCity->GameMapTileObject = gameMapTile;

	newGameCity->Name = CreateCityName(newGameCity->GetId());
	newGameCity->InitRuntimeData();

	if (false == GameCityRepository::GetInstance()->Register(newGameCity))
	{
		Q_ASSERT(newGameCity);
		delete newGameCity;
		return nullptr;
	}

	return newGameCity;
}

bool GameCityFactory::Create(const QDomNode city)
{
	GameCityRepository::GetInstance()->Init();
	return CreateGameCities(city);
}

bool GameCityFactory::Validate(const GameCityParameterObject obj)
{
	if (-1 == obj.ModelCityTypeId && nullptr == obj.ModelCityTypeObject)
	{
		jha::GetLog()->Log_MESSAGE(QObject::tr("ModelCityTypeId or ModelCityTypeObject are invalid!"));
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

int GameCityFactory::CreateId(const GameCityParameterObject obj)
{
	if (-1 != obj.Id)
	{
		return obj.Id; //Belongs to savegame
	}
	return GameCityRepository::GetInstance()->CreateNewId();
}

const ModelCityType* GameCityFactory::GetModelCityType(const GameCityParameterObject obj) const
{
	if (nullptr != obj.ModelCityTypeObject)
	{
		return obj.ModelCityTypeObject;
	}
	return ModelCityTypeRepository::GetInstance()->GetTypeById(obj.ModelCityTypeId);
}

const GameOwner* GameCityFactory::GetGameOwner(const GameCityParameterObject obj) const
{
	if (nullptr != obj.GameOwnerObject)
	{
		return obj.GameOwnerObject;
	}
	return GameOwnerRepository::GetInstance()->GetById(obj.GameOwnerId);
}

const GameMapTile* GameCityFactory::GetGameMapTile(const GameCityParameterObject obj) const
{
	if (nullptr != obj.GameMapTileObject)
	{
		return obj.GameMapTileObject;
	}
	return GameMapTileRepository::GetInstance()->GetById(obj.GameMapTileId);
}

QString GameCityFactory::CreateCityName(int cityId) const
{
	return DefaultCityName + " " + QString::number(cityId);
}

int GameCityFactory::GetBaseEfficency(int cityId) const
{
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(cityId);
	Q_ASSERT(modelCityType);
	return modelCityType->GetEfficiency();
}

int GameCityFactory::GetBaseStrength(int cityId) const
{
	const ModelCityType* modelCityType = ModelCityTypeRepository::GetInstance()->GetTypeById(cityId);
	Q_ASSERT(modelCityType);
	return modelCityType->GetDefenceValue();
}

bool GameCityFactory::CreateGameCities(const QDomNode& city)
{
	QDomNodeList nodes = city.childNodes();
	if (true == nodes.isEmpty())
	{
		jha::GetLog()->Log_WARNING(QObject::tr("%1: QDomNodeList has no child elements").arg(city.nodeName()));
		return false;
	}

	for (int nodeIndex = 0; nodeIndex < nodes.count(); nodeIndex++)
	{
		GameCity* created = CreateGameCityFromXML(nodes.at(nodeIndex));
		if (nullptr == created)
		{
			jha::GetLog()->Log_WARNING(QObject::tr("Unable to create GameCity from savegame line number: %1").arg(QString::number(nodes.at(nodeIndex).columnNumber())));
			continue;
		}
	}

	return true;
}

#include "model/ModelCityTypeRepository.h"
GameCity* GameCityFactory::CreateGameCityFromXML(const QDomNode& node)
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
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCity with id=%1: ModelCityType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(modelCityTypeId)));
		return nullptr;
	}

	int mapTileId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_GAMEMAPITEMID, mapTileId);

	const GameMapTile* gameMapTile = GameMapTileRepository::GetInstance()->GetById(mapTileId);
	if (nullptr == gameMapTile)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCity with id=%1: GameMap with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(mapTileId)));
		return nullptr;
	}

	int ownerTypeId = -1;
	allElementsExtracted &= extractor.ExtractValue(SerializeXMLItems::CITIES_OWNERTYPEID, ownerTypeId);

	const GameOwner* gameOwner = GameOwnerRepository::GetInstance()->GetById(ownerTypeId);
	if (nullptr == gameOwner)
	{
		jha::GetLog()->Log_DEBUG(QObject::tr("Unable to create GameCity with id=%1: ModelOwnerType with id=%2 not registered!").arg(QString::number(id)).arg(QString::number(ownerTypeId)));
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
	obj.GameOwnerObject = gameOwner;
	obj.GameMapTileObject = gameMapTile;
	obj.Id = id;

	GameCity *gameCity = Create(obj);
	if (nullptr == gameCity)
	{
		return nullptr;
	}

	DomNodeFinder find(node);
	GameUnitProduction* gameUnitProduction = CreateGameUnitProduction(find.FindDomeNodeByName(SerializeXMLItems::CITIES_UNITPRODUCTION), id);

	gameCity->GetRuntimeData()->CurrentEfficiency = efficiency;
	gameCity->GetRuntimeData()->BaseEfficiency = GetBaseEfficency(modelCityTypeId);
	gameCity->GetRuntimeData()->CurrentStrength = strength;
	gameCity->GetRuntimeData()->BaseStrength = GetBaseStrength(modelCityTypeId);
	gameCity->SetGameUnitProduction(gameUnitProduction);
	gameCity->Name = name;
	gameCity->SpezializedUnitTypeId = spezializedUnitTypeId;

	return gameCity;
}

GameUnitProduction* GameCityFactory::CreateGameUnitProduction(const QDomNode& domNode, int gameCityId)
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
