#ifndef GAMECITYCREATOR_H
#define GAMECITYCREATOR_H

#include "GameCityCreatorInterface.h"

class GameCityParameterObject;

/** Plaziert die Städte nur auf einem Terraintypen */
class GameCityCreatorSimple : public GameCityCreatorInterface
{
public:
	/** */
	GameCityCreatorSimple();
	/** */
	bool Create() override;
private:
	/** */
	bool AddValidTerrainTypeProcent(std::pair<int, double>	validTerrainTypeProcent);
	/** */
	bool CreateTerrainTypeTiles() const;
	/** */
	bool PlaceCities();
	/** */
	std::vector<int>	GetValidMapTileIds();
	/** */
	GameCityParameterObject* CreateGameCityObject();
private:
	friend class GameCityFactory;
	std::map<int,double>			ValidTerrainTypesProcent; //<ModelMapTileId,Percentage>
	mutable std::multimap<int, int>	TerrainTypeTiles;	//<ModelMapTileId,GameMapId>
	mutable GameCityParameterObject*	TemporaryGameCityParameterObject;
};

#endif // GAMECITYCREATOR_H