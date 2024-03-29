#ifndef GAMEUNITTRANSPORTCONTROLLER_H
#define GAMEUNITTRANSPORTCONTROLLER_H

class GameUnit;
class MapHexItem;
class MapView;

class GameUnitTransportController
{
public:
	/** */
	GameUnitTransportController(GameUnit* playerUnit);
	/** true == Unit gets embarked, false == unable to embark unit */
	bool EmbarkUnit(const MapHexItem* destination);
	/** */
	bool DisembarkUnit(const MapHexItem* destination);
private:
	/** */
	GameUnit* GetOwnUnitOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool CanBeTransported(const MapHexItem* destination) const;
	/** */
	int GetFreeTransportCapacity(GameUnit* gameUnit) const;
	/** */
	bool EmbarkUnit();
	//TODO: CanUnitEmbark, CanUnitDisembark
private:
	GameUnit*			UnitToTransport;
	mutable GameUnit*	TransporterUnit;
	MapView*			MapViewObject;
};

#endif // GAMEUNITTRANSPORTCONTROLLER_H