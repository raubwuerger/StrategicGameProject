#ifndef COMMANDPLACEGAMEUNITONMAP_H
#define COMMANDPLACEGAMEUNITONMAP_H

class GameUnitItem;
class MapView;
class GameMapItem;

class CommandPlaceGameUnitOnMap
{
public:
	/** */
	static bool PlaceGameUnit(const GameUnitItem* gameUnitItem, const GameMapItem* gameMapItem);
	/** */
	static bool PlaceGameUnit(const GameUnitItem* gameUnitItem, int gameMapItemId);
private:
	friend class GameFactory;
	static MapView*	MapViewObject;
};

#endif // COMMANDPLACEGAMEUNITONMAP_H