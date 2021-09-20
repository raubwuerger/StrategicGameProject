#ifndef GAMEUNITTRANSPORTCONTROLLER_H
#define GAMEUNITTRANSPORTCONTROLLER_H

class GameUnit;
class MapHexItem;

class GameUnitTransportController
{
public:
	/** */
	GameUnitTransportController(GameUnit* playerUnit);
	/** */
	bool TransportUnit(const MapHexItem* destination) const;
private:
	/** */
	GameUnit* GetOwnUnitOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool CanBeTransported(const MapHexItem* destination) const;
	/** */
	int GetFreeTransportCapacity(GameUnit* gameUnit) const;
	/** */
	//TODO: CanUnitEmbark, CanUnitDisembark
private:
	GameUnit* GameUnitObject;
};

#endif // GAMEUNITTRANSPORTCONTROLLER_H