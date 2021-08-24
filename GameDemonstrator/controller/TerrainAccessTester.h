#ifndef TERRAINACCESSTESTER_H
#define TERRAINACCESSTESTER_H

class ModelUnitType;
class GameUnitItem;
class MapHexItem;
class ModelTerrainType;
class ModelCityType;

class TerrainAccessTester
{
public:
	/** */
	static bool Accessable(const ModelUnitType* modelUnitType, const int gameMapItemId);
	/** */
	static bool Accessable(const GameUnitItem* gameUnitItem, const MapHexItem* mapHexItem);
	/** */
	static bool Accessable(const GameUnitItem* gameUnitItem, const ModelTerrainType* modelTerrainType);
	/** */
	static bool Accessable(const ModelCityType* modelCityType, const int gameMapItemId);
};

#endif // TERRAINACCESSTESTER_H