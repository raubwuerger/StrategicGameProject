#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnit;
class ModelUnitType;
class ModelTerrainType;
class GameOwner;
class GameCity;
#include "game\GameUnitFactory.h"

class GameUnitMovementController
{
public:
	GameUnitMovementController( GameUnit *activeGameUnitItem);
	/** */
	bool Move(const MapHexItem* destination );
private:
	/** */
	bool CanUnitMove(int sourceGameUnitItemId, const MapHexItem* destination);
	/** */
	GameUnitParameterObject CreateUpdateGameUnit(const MapHexItem* destMapHexItem);
	/** */
	bool IsEnemyCityOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool AttackCity(const GameUnit* gameUnitItem, const GameCity* gameCityItem) const;
	/** */
	bool EmitMapUnitItemMoved(const GameUnit* gameUnitItem) const;
private:
	GameUnit*		ActiveGameUnitItem;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H