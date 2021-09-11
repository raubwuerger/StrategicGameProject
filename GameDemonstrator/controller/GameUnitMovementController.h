#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;
class ModelTerrainType;
class GameOwnerItem;
class GameCity;

class GameUnitMovementController
{
public:
	GameUnitMovementController(const GameUnitItem *activeGameUnitItem);
	/** */
	bool CanUnitMoveToDestination(int sourceGameUnitItemId, const MapHexItem* destination ) const;
private:
	/** */
	bool IsOwnUnitOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool IsEnemyOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool IsEnemyCityOnDestinationMapTile(int gameMapItemId) const;
	/** */
	const GameUnitItem* GetEnemyGameUnit(int gameMapItemId) const;
	/** */
	const GameOwnerItem* GetCurrentMapTileOwner();
	/** */
	bool AttackCity(const GameUnitItem* gameUnitItem, const GameCity* gameCityItem) const;
	/** */
	bool EmitMapUnitItemMoved(const GameUnitItem* gameUnitItem) const;
private:
	const GameUnitItem*		ActiveGameUnitItem;
	const GameOwnerItem*	CurrentMapTileOwner;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H