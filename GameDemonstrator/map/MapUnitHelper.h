#ifndef MAPUNITHELPER_H
#define MAPUNITHELPER_H

class GameUnit;
class MapHexItem;
class GameUnitParameterObject;
#include <memory>
#include <utility>

class MapUnitHelper
{
public:
	/** */
	MapUnitHelper(GameUnit* gameUnit);
	/** */
	bool Move(const MapHexItem* destMapHexItem);
private:
	/** */
	MapUnitHelper() {}
	/** */
	std::unique_ptr<GameUnitParameterObject> CreateUpdateGameUnit(const MapHexItem* destMapHexItem);
private:
	GameUnit*	GameUnitToMove;
};

#endif //MAPUNITHELPER_H