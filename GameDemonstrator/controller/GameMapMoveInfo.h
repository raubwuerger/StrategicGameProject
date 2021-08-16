#ifndef GAMEMAPMOVEINFO_H
#define GAMEMAPMOVEINFO_H

class MapHexItem;
class MapUnitItem;

class GameMapMoveInfo
{
public:
	/** */
	GameMapMoveInfo(const MapUnitItem* source);
	/** */
	const MapHexItem* GetDestinationInfo(int movementDirection) const;
	/** */
	static void CreateMovementTypes();
private:
	/** */
	QSize GetCorrectOffset(int movementDirection, const MapHexItem* mapHexItem) const;
private:
	const MapUnitItem*		SourceMapUnitItem;
	mutable const MapHexItem*		SourceMapHexItem;
	static QMap<int, QSize> MovementTypeColumEven;
	static QMap<int, QSize> MovementTypeColumOdd;
};

#endif // GAMEMAPMOVEINFO_H