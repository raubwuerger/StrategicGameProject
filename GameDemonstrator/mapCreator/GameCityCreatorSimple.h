#ifndef GAMECITYCREATOR_H
#define GAMECITYCREATOR_H

#include "GameCityCreatorInterface.h"

class GameCityParameterObject;
class GameCity;
class GameMapTile;

struct MapPoint
{
	MapPoint()
		: Col(NOT_INITIALIZED_INT),
		Row(NOT_INITIALIZED_INT)
	{

	}

	MapPoint(int  col, int row)
		: Col(col),
		Row(row)
	{

	}

	int Col;
	int Row;
};

struct MapRect
{
	MapRect()
		: TopLeft(NOT_INITIALIZED_INT, NOT_INITIALIZED_INT),
		TopRight(NOT_INITIALIZED_INT, NOT_INITIALIZED_INT),
		BottomLeft(NOT_INITIALIZED_INT, NOT_INITIALIZED_INT),
		BottomRight(NOT_INITIALIZED_INT, NOT_INITIALIZED_INT)
	{

	}

	MapRect(MapPoint topLeft, MapPoint topRight, MapPoint bottomLeft, MapPoint bottomRight)
		: TopLeft(topLeft),
		TopRight(topRight),
		BottomLeft(bottomLeft),
		BottomRight(bottomRight)
	{

	}

	MapPoint	TopLeft;
	MapPoint	TopRight;
	MapPoint	BottomLeft;
	MapPoint	BottomRight;
};

/** Plaziert die Städte nur auf einem Terraintypen */
class GameCityCreatorSimple : public GameCityCreatorInterface
{
public:
	/** */
	GameCityCreatorSimple();
	/** */
	~GameCityCreatorSimple();
	/** */
	bool Create() override;
private:
	/** */
	bool AddValidTerrainTypeProcent(std::pair<int, double>	validTerrainTypeProcent);
	/** */
	bool CreateTerrainTypeTiles() const;
	/** */
	bool PlaceCities();
	/** */
	std::vector<int> GetValidMapTileIds();
	/** */
	std::vector<int> CreateConcreteMapTileIds();
	/** */
	GameCityParameterObject* CreateGameCityObject( int gameMapId );
	/** */
	bool SetCityOwners();
	/** */
	std::map<int, MapRect> CreateMapQuarters();
	/** */
	bool CheckForFirstQuarter(const MapRect& quarter, const GameCity* gameCity);
	/** */
	const GameMapTile* GetGameMapTileByCityId(int cityId) const;
private:
	friend class GameCityFactory;
	std::map<int,double>			ValidTerrainTypesProcent; //<ModelMapTileId,Percentage>
	mutable std::multimap<int, int>	TerrainTypeTiles;	//<ModelMapTileId,GameMapId>
	mutable GameCityParameterObject*	TemporaryGameCityParameterObject;
};

#endif // GAMECITYCREATOR_H