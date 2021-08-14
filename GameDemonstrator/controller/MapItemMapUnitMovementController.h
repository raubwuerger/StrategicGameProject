#ifndef MAPITEMMAPUNITMOVEMENTCONTROLLER_H
#define MAPITEMMAPUNITMOVEMENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;
class GameUnitItem;
class ModelUnitType;

class MapItemMapUnitMovementController
{
public:
	/** */
	bool CanUnitMove(const MapUnitItem* mapUnitItem);
	/** */
	bool CanUnitMove(const MapHexItem* mapHexItem, const GameUnitItem* gameUnitItem );
	/** */
	bool CanUnitMove(const ModelUnitType* modelUnitType, const int gameMapItemId);
};

#endif // MAPITEMMAPUNITMOVEMENTCONTROLLER_H