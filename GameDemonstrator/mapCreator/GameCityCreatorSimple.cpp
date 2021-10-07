#include "stdafx.h"
#include "GameCityCreatorSimple.h"
#include "LogInterface.h"
#include "Game\GameMapTileRepository.h"
#include "Game\GameMapTile.h"
#include "Game\GameCityFactory.h"
#include "Game\GameCityRepository.h"
#include "Game\GameConfig.h"
#include "Model\ModelTerrainTypeRepository.h"

GameCityCreatorSimple::GameCityCreatorSimple()
	: TemporaryGameCityParameterObject(nullptr)
{
	TemporaryGameCityParameterObject = new GameCityParameterObject();
}

bool GameCityCreatorSimple::Create()
{
	if (true == ValidTerrainTypesProcent.empty())
	{
		jha::GetLog()->Log_INFO("Member <ValidTerrainTypesProcent> is empty!");
		return false;
	}

	if (false == CreateTerrainTypeTiles())
	{
		return false;
	}

	if (false == PlaceCities())
	{
		return false;
	}

	if (false == SetCityOwners())
	{
		return false;
	}
	return true;
}

bool GameCityCreatorSimple::AddValidTerrainTypeProcent(std::pair<int, double> validTerrainTypeProcent)
{
	if (0 != ValidTerrainTypesProcent.count(validTerrainTypeProcent.first))
	{
		jha::GetLog()->Log_INFO(QObject::tr("ValidTerrainTypesProcent pair already registered! [ModelMapTileId|Percentage]: %1|%2").arg(QString::number(validTerrainTypeProcent.first)).arg(QString::number(validTerrainTypeProcent.second)));
		return false;
	}
	ValidTerrainTypesProcent.insert(validTerrainTypeProcent);
	return true;
}

bool GameCityCreatorSimple::CreateTerrainTypeTiles() const
{
	const QVector< QVector<GameMapTile*> >* gameMapTiles = GameMapTileRepository::GetInstance()->GetMapTiles();
	if (true == gameMapTiles->isEmpty())
	{
		jha::GetLog()->Log_INFO(QObject::tr("GameMapTileRepository is empty!"));
		return false;
	}

	//TODO: Is this really more performant??
	int rows = gameMapTiles->count();
	int cols = gameMapTiles->at(0).count();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int colIndex = 0; colIndex < cols; colIndex++)
		{
			const GameMapTile* gameMapTile = gameMapTiles->at(rowIndex)[colIndex];
			int terrainTypeId = gameMapTile->GetModelTerrainTypeId();
			int gameMapId = gameMapTile->GetId();
			TerrainTypeTiles.insert(std::pair<int, int>(terrainTypeId, gameMapId));
		}
	}

	int terrainTypeCount = ModelTerrainTypeRepository::GetInstance()->GetCount();
	return TerrainTypeTiles.size() > 0;
}

bool GameCityCreatorSimple::PlaceCities()
{
	//TODO: Mininmale Anzahl der Städte sollte sich nach der Anzahl der Spieler richten!
	//TODO: Was ist zu tun wenn die minimale Anzahl der Städt größer als die zur Verfügung stehenden Felder ist -> Minimale Kartengröße erzwingen???
	std::vector<int> concreteMapTileIds = CreateConcreteMapTileIds();
	if (true == concreteMapTileIds.empty())
	{
		Q_ASSERT(false);
		return false;
	}

	GameCityFactory gameCityFactory;
	for (int concreteMapTileIdIndex = 0; concreteMapTileIdIndex < concreteMapTileIds.size();concreteMapTileIdIndex++)
	{
		GameCityParameterObject* cityParameterObject = CreateGameCityObject(concreteMapTileIds[concreteMapTileIdIndex]);
		GameCity* gameCity = gameCityFactory.Create(*cityParameterObject);
		if (nullptr == gameCity)
		{
//			return false;
		}
	}

	return true;
}

std::vector<int> GameCityCreatorSimple::CreateConcreteMapTileIds()
{
	const int MAP_CITY_FACTOR = 20; //TODO: Sollte über den Dialog "Neuse Spiel" eingestellt werden können
	const int PLAYER_COUNT = 4;		//TODO: Sollte über den Dialog "Neuse Spiel" eingestellt werden können
	std::vector<int> validMapTileIds = GetValidMapTileIds();
	if (PLAYER_COUNT > validMapTileIds.size())
	{
		return std::vector<int>();
	}

	int validMapTileCount = validMapTileIds.size();
	int cityCount = validMapTileCount / MAP_CITY_FACTOR;
	int cityCountTemp = cityCount / PLAYER_COUNT;
	cityCount = cityCountTemp * PLAYER_COUNT;
	if (PLAYER_COUNT > cityCount)
	{
		cityCount = PLAYER_COUNT;
	}

	std::vector<int> concreteMapTileIds;
	for (int cityIndex = 0; cityIndex < validMapTileCount; cityIndex += MAP_CITY_FACTOR)
	{
		concreteMapTileIds.push_back(validMapTileIds[cityIndex]);
	}
	return concreteMapTileIds;
}

std::vector<int> GameCityCreatorSimple::GetValidMapTileIds()
{
	//TODO: Aktuelle wird nur eine Geländeart unterschtützt!!!
	std::map<int, double>::iterator validTerrainTypeIterator = ValidTerrainTypesProcent.begin();
	int terrainTypeId = validTerrainTypeIterator->first;
	double terrainTypeIdProcent = validTerrainTypeIterator->second;

	int terrainTypeIdCount = TerrainTypeTiles.count(terrainTypeId);
	auto equalRange = TerrainTypeTiles.equal_range(terrainTypeId);
	auto first = equalRange.first;
	auto last = equalRange.second;

	std::vector<int> validMapTileIds;

	for (auto it = first; it != last; it++)
	{
		validMapTileIds.push_back(it->second);
	}
	return validMapTileIds;
}

GameCityParameterObject* GameCityCreatorSimple::CreateGameCityObject( int gameMapId )
{
	const int CITY_EFFICIENCY_LOWER_BOUND = 80;		//TODO: Sollte über den Dialog "Neuse Spiel" eingestellt werden können
	const int CITY_EFFICIENCY_UPPER_BOUND = 120;	//TODO: Sollte über den Dialog "Neuse Spiel" eingestellt werden können

	static int CITY_ID = 0;
	static const int DEFAULT_OWNER_TYPE_ID = 1;
	static const int DEFAULT_CITY_TYPE_ID = 1;
	TemporaryGameCityParameterObject->Id = ++CITY_ID;
	TemporaryGameCityParameterObject->GameOwnerId = DEFAULT_OWNER_TYPE_ID;
	TemporaryGameCityParameterObject->GameMapTileId = gameMapId;
	TemporaryGameCityParameterObject->ModelCityTypeId = DEFAULT_CITY_TYPE_ID;
	return TemporaryGameCityParameterObject;
}

bool GameCityCreatorSimple::SetCityOwners()
{
	QMap<int, GameCity*>::const_iterator firstCity = GameCityRepository::GetInstance()->GetFirstIterator();
	return false;
}


std::map<int, MapRect> GameCityCreatorSimple::CreateMapQuarters()
{
	static const int HALF = 2;
	static const int OFFSET_ZERO = 1;

	int colLeft = 0;
	int colMiddle = GameConfig::MapCols / HALF - OFFSET_ZERO;
	int colRight = GameConfig::MapCols - OFFSET_ZERO;

	int rowTop = 0;
	int rowMiddle = GameConfig::MapRows / HALF - OFFSET_ZERO;
	int rowBottom = GameConfig::MapRows - OFFSET_ZERO;

	MapPoint colLeft_rowTop(colLeft, rowTop);
	MapPoint colMiddle_rowTop(colMiddle, rowTop);
	MapPoint colRight_rowTop(colRight, rowTop);

	MapPoint colLeft_rowMiddle(colLeft, rowMiddle);
	MapPoint colMiddle_rowMiddle(colMiddle, rowMiddle);
	MapPoint colRight_rowMiddle(colRight, rowMiddle);

	MapPoint colLeft_rowBottom(colLeft, rowBottom);
	MapPoint colMiddle_rowBottom(colMiddle, rowBottom);
	MapPoint colRight_rowBottom(colRight, rowBottom);

	GameConfig::MapCols;
	std::map<int, MapRect> mapQuarters;

	mapQuarters.insert( std::pair<int,MapRect>(0, MapRect(colLeft_rowTop, colLeft_rowTop, colLeft_rowMiddle, colMiddle_rowMiddle) ) );

//	mapQuarters.insert( std::pair<int, MapRect>(1, MapRect(colLeft_rowTop, colLeft_rowTop, colLeft_rowMiddle, colMiddle_rowMiddle)) );
//	mapQuarters.insert( std::pair<int, MapRect>(2, MapRect(colLeft_rowTop, colLeft_rowTop, colLeft_rowMiddle, colMiddle_rowMiddle)) );
//	mapQuarters.insert( std::pair<int, MapRect>(3, MapRect(colLeft_rowTop, colLeft_rowTop, colLeft_rowMiddle, colMiddle_rowMiddle)) );

	return mapQuarters;
}
