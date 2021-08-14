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
	static void CreateMovementTypes();
	/** */
	bool IsMovementDirectionValid(int movementDirection, const MapHexItem* mapHexItem) const;
private:
	static QMap<int, QSize> MovementTypeColumEven;
	static QMap<int, QSize> MovementTypeColumOdd;
};

#endif // KEYEVENTCONTROLLER_H