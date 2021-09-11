#ifndef COMMANDPLACEGAMEUNITONMAP_H
#define COMMANDPLACEGAMEUNITONMAP_H

class GameUnit;
class MapView;
class GameMapTile;

class CommandPlaceGameUnitOnMap
{
public:
	/** */
	static bool PlaceGameUnit(const GameUnit* gameUnitItem, const GameMapTile* gameMapItem);
	/** */
	static bool PlaceGameUnit(const GameUnit* gameUnitItem, int gameMapItemId);
private:
	friend class GameFactory;
	static MapView*	MapViewObject;
};

#endif // COMMANDPLACEGAMEUNITONMAP_H