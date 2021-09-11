#ifndef TERRAINACCESSTESTER_H
#define TERRAINACCESSTESTER_H

class ModelUnitType;
class GameUnit;
class GameMapTile;
class MapHexItem;
class ModelTerrainType;
class ModelCityType;

class TerrainAccessTester
{
public:
	/** */
	static bool Accessable(const ModelUnitType* modelUnitType, const int gameMapItemId);
	/** */
	static bool Accessable(const GameUnit* gameUnitItem, const MapHexItem* mapHexItem);
	/** */
	static bool Accessable(const GameUnit* gameUnitItem, const GameMapTile* gameMapItem);
	/** */
	static bool Accessable(const GameUnit* gameUnitItem, const ModelTerrainType* modelTerrainType);
	/** */
	static bool Accessable(const ModelCityType* modelCityType, const int gameMapItemId);
	/** */
	static bool Accessable(const int modelCityTypeId, const int gameMapItemId);
};

#endif // TERRAINACCESSTESTER_H