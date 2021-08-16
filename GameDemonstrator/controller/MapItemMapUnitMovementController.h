#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;
class ModelTerrainType;

class MapItemMapUnitMovementController
{
public:
	/** */
	bool IsTerrainTypeAccessible(const MapUnitItem* mapUnitItem, const GameUnitItem* gameUnitItem);
	/** */
	bool IsTerrainTypeAccessible(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem);
	/** */
	bool IsTerrainTypeAccessible(const ModelUnitType* modelUnitType, const int gameMapItemId);
	/** */
	bool CanUnitMove(const MapUnitItem* mapUnitItem);
	/** */
	bool CanUnitMove(const MapHexItem* mapHexItem, int gameUnitItemId);
	/** */
	bool CanUnitMove(const ModelUnitType* modelUnitType, const int gameMapItemId);
private:
	/** */
	const ModelTerrainType* GetModelTerrainType(const MapUnitItem* mapUnitItem);
	/** */
	const GameUnitItem* GetGameUnitItem(const MapUnitItem* mapUnitItem);
	/** */
	bool IsStackLimitSufficient(const GameUnitItem* gameUnitItem);
	/** */
	bool IsStackLimitSufficient(int gameMapItemId);
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H