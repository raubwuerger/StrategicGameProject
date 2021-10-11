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
	bool IsEnemyCityOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool AttackCity(const GameUnit* gameUnitItem, const GameCity* gameCityItem) const;
	/** */
	bool EmitMapUnitItemMoved(const GameUnit* gameUnitItem) const;
private:
	const GameUnit*		ActiveGameUnitItem;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H