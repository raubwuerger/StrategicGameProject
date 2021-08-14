#ifndef KEYEVENTCONTROLLER_H
#define KEYEVENTCONTROLLER_H

class MapUnitItem;

class KeyEventController
{
public:
	/** */
	void HandleKeyPressEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent);
	/** */
	void HandleKeyReleaseEvent(MapUnitItem* mapUnitItem, QKeyEvent* keyEvent);
};

#endif // KEYEVENTCONTROLLER_H