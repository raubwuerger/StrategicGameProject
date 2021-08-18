#ifndef TERRAINACCESSTESTER_H
#define TERRAINACCESSTESTER_H

class ModelUnitType;
class GameUnitItem;
class MapHexItem;

class TerrainAccessTester
{
public:
	/** */
	static bool Accessable(const ModelUnitType* modelUnitType, const int gameMapItemId);
	/** */
	static bool Accessable(const GameUnitItem* gameUnitItem, const MapHexItem* mapHexItem);
};

#endif // TERRAINACCESSTESTER_H