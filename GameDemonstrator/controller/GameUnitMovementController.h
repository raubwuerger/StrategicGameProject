#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;
class ModelTerrainType;
class ModelOwnerType;
class GameCityItem;

class GameUnitMovementController
{
public:
	GameUnitMovementController(const GameUnitItem *activeGameUnitItem);
	/** */
	bool CanUnitMoveToDestination(int sourceGameUnitItemId, const MapHexItem* destination ) const;
private:
	/** */
	const ModelTerrainType* GetModelTerrainType(const MapUnitItem* mapUnitItem) const;
	/** */
	const GameUnitItem* GetGameUnitItem(const MapUnitItem* mapUnitItem) const;
	/** */
	bool IsOwnUnitOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool IsEnemyOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool IsEnemyCityOnDestinationMapTile(int gameMapItemId) const;
	/** */
	const GameUnitItem* GetEnemyGameUnit(int gameMapItemId) const;
	/** */
	bool IsStackLimitSufficient(int gameMapItemId) const;
	/** */
	const ModelOwnerType* GetCurrentMapTileOwner();
	/** */
	bool AttackCity(const GameUnitItem* gameUnitItem, const GameCityItem* gameCityItem) const;
private:
	const GameUnitItem*		ActiveGameUnitItem;
	const ModelOwnerType*	CurrentMapTileOwner;
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H