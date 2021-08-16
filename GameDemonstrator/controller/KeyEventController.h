#ifndef KEYEVENTCONTROLLER_H
#define KEYEVENTCONTROLLER_H

class MapUnitItem;
class MapHexItem;

class KeyEventController
{
public:
	/** */
	KeyEventController();
	/** */
	void HandleKeyPressEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent);
	/** */
	void HandleKeyReleaseEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent);
private:
	/** */
	void CreateValidMovementPositions(MapHexItem* mapHexItem);
	/** */
	bool IsMovementDirectionValid(int movementDirection, MapUnitItem* mapUnitItem) const;
};

#endif // KEYEVENTCONTROLLER_H