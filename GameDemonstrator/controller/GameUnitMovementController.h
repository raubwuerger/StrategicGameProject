#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;
class ModelTerrainType;

class GameUnitMovementController
{
public:
	GameUnitMovementController(const MapHexItem *mapHexItem);
	/** */
	bool IsTerrainTypeAccessible(const int gameMapItemId, const ModelUnitType* modelUnitType ) const;
	/** */
	bool CanUnitMove(int gameUnitItemId, const MapHexItem* mapHexItem ) const;
private:
	/** */
	bool IsTerrainTypeAccessible(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem) const;
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