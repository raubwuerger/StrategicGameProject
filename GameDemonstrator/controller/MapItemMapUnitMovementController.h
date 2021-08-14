#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;

class MapItemMapUnitMovementController
{
public:
	/** */
	bool CanUnitMove(const MapUnitItem* mapUnitItem);
	/** */
	bool CanUnitMove(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem );
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H