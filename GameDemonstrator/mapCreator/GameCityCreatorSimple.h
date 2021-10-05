#ifndef GAMECITYCREATOR_H
#define GAMECITYCREATOR_H

#include "GameCityCreatorInterface.h"

class GameCityCreatorSimple : public GameCityCreatorInterface
{
public:
	/** */
	bool Create() override;
private:
	/** */
	bool AddValidTerrainTypeProcent(std::map<int, int>	validTerrainTypeProcent);
private:
	friend class GameCityFactory;
	std::map<int,int>	ValidTerrainTypesProcent; // 
};

#endif // GAMECITYCREATOR_H