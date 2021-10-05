#ifndef GAMEUNITTRANSPORTCONTROLLER_H
#define GAMEUNITTRANSPORTCONTROLLER_H

class GameUnit;
class MapHexItem;

class GameUnitTransportController
{
public:
	/** */
	GameUnitTransportController(GameUnit* playerUnit);
	/** true == Unit is transported, false == unable to transport unit */
	bool TransportUnit(const MapHexItem* destination);
private:
	/** */
	GameUnit* GetOwnUnitOnDestinationMapTile(int gameMapItemId) const;
	/** */
	bool CanBeTransported(const MapHexItem* destination) const;
	/** */
	int GetFreeTransportCapacity(GameUnit* gameUnit) const;
	/** */
	void EmbarkUnit();
	//TODO: CanUnitEmbark, CanUnitDisembark
private:
	GameUnit*			UnitToTransport;
	mutable GameUnit*	TransporterUnit;
};

#endif // GAMEUNITTRANSPORTCONTROLLER_H