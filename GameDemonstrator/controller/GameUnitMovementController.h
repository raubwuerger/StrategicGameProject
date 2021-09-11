#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnit;
class ModelUnitType;
class ModelTerrainType;
class GameOwner;
class GameCity;

class GameUnitMovementController
{
public:
	GameUnitMovementController(const GameUnit *activeGameUnitItem);
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
	const GameUnit* GetEnemyGameUnit(int gameMapItemId) const;
	/** */
	const GameOwner* GetCurrentMapTileOwner();
	/** */
	bool AttackCity(const GameUnit* gameUnitItem, const GameCity* gameCityItem) const;
	/** */
	bool EmitMapUnitItemMoved(const GameUnit* gameUnitItem) const;
private:
	const GameUnit*		ActiveGameUnitItem;
	const GameOwner*	CurrentMapTileOwner;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H