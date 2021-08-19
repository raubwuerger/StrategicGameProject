#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;
class ModelTerrainType;
class ModelOwnerType;

class GameUnitMovementController
{
public:
	GameUnitMovementController(const GameUnitItem *activeGameUnitItem);
	/** */
	bool CanUnitMove(int gameUnitItemId, const MapHexItem* destination ) const;
private:
	/** */
	const ModelTerrainType* GetModelTerrainType(const MapUnitItem* mapUnitItem) const;
	/** */
	const GameUnitItem* GetGameUnitItem(const MapUnitItem* mapUnitItem) const;
	/** */
	bool IsEnemyOnDestinationMapTile(int gameMapItemId) const;
	/** */
	const GameUnitItem* GetEnemyGameUnit(int gameMapItemId) const;
	/** */
	bool IsStackLimitSufficient(int gameMapItemId) const;
	/** */
	const ModelOwnerType* GetCurrentMapTileOwner();
private:
	const GameUnitItem*		ActiveGameUnitItem;
	const ModelOwnerType*	CurrentMapTileOwner;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H