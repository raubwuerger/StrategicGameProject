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
	MapItemMapUnitMovementController(const MapHexItem *mapHexItem);
	/** */
	bool IsTerrainTypeAccessible(const MapUnitItem* mapUnitItem, const GameUnitItem* gameUnitItem) const;
	/** */
	bool IsTerrainTypeAccessible(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem) const;
	/** */
	bool IsTerrainTypeAccessible(const ModelUnitType* modelUnitType, const int gameMapItemId) const;
	/** */
	bool CanUnitMove(const MapUnitItem* mapUnitItem) const;
	/** */
	bool CanUnitMove(const MapHexItem* mapHexItem, int gameUnitItemId) const;
	/** */
	bool CanUnitMove(const ModelUnitType* modelUnitType, const int gameMapItemId) const;
private:
	/** */
	const ModelTerrainType* GetModelTerrainType(const MapUnitItem* mapUnitItem) const;
	/** */
	const GameUnitItem* GetGameUnitItem(const MapUnitItem* mapUnitItem) const;
	/** */
	bool IsStackLimitSufficient(int gameMapItemId) const;
private:
	const MapHexItem*	Destination;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H