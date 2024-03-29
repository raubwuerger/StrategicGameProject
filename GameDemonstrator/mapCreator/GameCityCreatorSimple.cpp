#include "stdafx.h"
#include "GameCityCreatorSimple.h"
#include "LogInterface.h"
#include "Game\GameMapTileRepository.h"
#include "Game\GameMapTile.h"
#include "Game\GameCity.h"
#include "Game\GameCityFactory.h"
#include "Game\GameCityRepository.h"
#include "Game\GameConfig.h"
#include "Game\GameOwnerRepository.h"
#include "Model\ModelTerrainTypeRepository.h"

GameCityCreatorSimple::GameCityCreatorSimple()
	: TemporaryGameCityParameterObject(nullptr)
{
	TemporaryGameCityParameterObject = new GameCityParameterObject();
}

GameCityCreatorSimple::~GameCityCreatorSimple()
{
	delete TemporaryGameCityParameterObject;
	TemporaryGameCityParameterObject = nullptr;
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
	//TODO: Mininmale Anzahl der St�dte sollte sich nach der Anzahl der Spieler richten!
	//TODO: Was ist zu tun wenn die minimale Anzahl der St�dt gr��er als die zur Verf�gung stehenden Felder ist -> Minimale Kartengr��e erzwingen???
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
			Q_ASSERT(false);
			return false;
		}
	}

	return true;
}

std::vector<int> GameCityCreatorSimple::CreateConcreteMapTileIds()
{
	const int MAP_CITY_FACTOR = 20; //TODO: Sollte �ber den Dialog "Neuse Spiel" eingestellt werden k�nnen
	const int PLAYER_COUNT = 4;		//TODO: Sollte �ber den Dialog "Neuse Spiel" eingestellt werden k�nnen
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
	//TODO: Aktuelle wird nur eine Gel�ndeart unterscht�tzt!!!
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
	const int CITY_EFFICIENCY_LOWER_BOUND = 80;		//TODO: Sollte �ber den Dialog "Neuse Spiel" eingestellt werden k�nnen
	const int CITY_EFFICIENCY_UPPER_BOUND = 120;	//TODO: Sollte �ber den Dialog "Neuse Spiel" eingestellt werden k�nnen

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
	std::map<int, MapRect> mapQuarters = CreateMapQuarters();
		
	bool cityQuarter1 = false;
	bool cityQuarter2 = false;
	bool cityQuarter3 = false;
	bool cityQuarter4 = false;
	QMap<int, GameCity*>::const_iterator currentIterator = GameCityRepository::GetInstance()->GetFirstIterator();
	while (currentIterator != GameCityRepository::GetInstance()->GetLastIterator())
	{
		if (false == cityQuarter1)
		{
			cityQuarter1 = CheckForFirstQuarter(mapQuarters[0], *(currentIterator));
			if (true == cityQuarter1)
			{
				GameCityRepository::GetInstance()->ChangeOwner(*(currentIterator), GameOwnerRepository::GetInstance()->GetById(2));
				continue;
			}
		}

		if (false == cityQuarter2 )
		{
			cityQuarter2 = CheckForFirstQuarter(mapQuarters[1], *(currentIterator));
			if (true == cityQuarter2)
			{
				GameCityRepository::GetInstance()->ChangeOwner(*(currentIterator), GameOwnerRepository::GetInstance()->GetById(3));
				continue;
			}
		}

		if (false == cityQuarter3 )
		{
			cityQuarter3 = CheckForFirstQuarter(mapQuarters[2], *(currentIterator));
			if (true == cityQuarter3)
			{
				GameCityRepository::GetInstance()->ChangeOwner(*(currentIterator), GameOwnerRepository::GetInstance()->GetById(4));
				continue;
			}
		}

		if (false == cityQuarter4 ) 
		{
			cityQuarter4 = CheckForFirstQuarter(mapQuarters[3], *(currentIterator));
			if (true == cityQuarter4)
			{
				GameCityRepository::GetInstance()->ChangeOwner(*(currentIterator), GameOwnerRepository::GetInstance()->GetById(5));
				continue;
			}
		}
		currentIterator++;
	}
	return true;
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

	mapQuarters.insert( std::pair<int, MapRect>(0, MapRect(colLeft_rowTop, colMiddle_rowTop, colLeft_rowMiddle, colMiddle_rowMiddle) ) );
	mapQuarters.insert( std::pair<int, MapRect>(1, MapRect(colMiddle_rowTop, colRight_rowTop, colMiddle_rowMiddle, colRight_rowMiddle)) );
	mapQuarters.insert( std::pair<int, MapRect>(2, MapRect(colLeft_rowMiddle, colMiddle_rowMiddle, colLeft_rowBottom, colMiddle_rowBottom)) );
	mapQuarters.insert( std::pair<int, MapRect>(3, MapRect(colMiddle_rowMiddle, colRight_rowMiddle, colMiddle_rowBottom, colRight_rowBottom)) );

	return mapQuarters;
}

bool GameCityCreatorSimple::CheckForFirstQuarter(const MapRect& quarter, const GameCity* gameCity)
{
	const GameMapTile* gameMapTile = GetGameMapTileByCityId(gameCity->GetGameMapTileId());
	Q_ASSERT(gameMapTile);
	
	int gameCityCol = gameMapTile->GetCol();
	int gameCityRow = gameMapTile->GetRow();

	QRect rect(QPoint(quarter.TopLeft.Col, quarter.TopLeft.Row), QPoint(quarter.BottomRight.Col, quarter.BottomRight.Row));

	return rect.contains(QPoint(gameCityCol, gameCityRow));
}

const GameMapTile* GameCityCreatorSimple::GetGameMapTileByCityId(int cityId) const
{
	return GameMapTileRepository::GetInstance()->GetById(cityId);
}
