#ifndef GAMECITYCREATOR_H
#define GAMECITYCREATOR_H

#include "GameCityCreatorInterface.h"

/** Plaziert die Städte nur auf einem Terraintypen */
class GameCityCreatorSimple : public GameCityCreatorInterface
{
public:
	/** */
	bool Create() override;
private:
	/** */
	bool AddValidTerrainTypeProcent(std::pair<int, double>	validTerrainTypeProcent);
	/** */
	bool CreateTerrainTypeTiles() const;
	/** */
	bool PlaceCities();
private:
	friend class GameCityFactory;
	std::map<int,double>			ValidTerrainTypesProcent; //<ModelMapTileId,Percentage>
	mutable std::multimap<int, int>	TerrainTypeTiles;	//<ModelMapTileId,GameMapId>
};

#endif // GAMECITYCREATOR_H