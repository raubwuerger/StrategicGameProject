#ifndef GAMECITYPRODUCTIONREPOSITORY_H
#define GAMECITYPRODUCTIONREPOSITORY_H

#include "BaseRepository.h"

class GameUnitProduction;

class GameUnitProductionRepository : public BaseRepository
{
public:
	/** */
	static GameUnitProductionRepository* GetInstance();
	/** */
	bool RegisterGameUnitProduction(GameUnitProduction* gameUnitProduction);
	/** */
	bool Init() override;
	/** */
	void Release() override;
private:
	/** */
	GameUnitProductionRepository();
private:
	QMap<int, GameUnitProduction*>	CityProductions;
	static GameUnitProductionRepository* Instance;
};

#endif // GAMECITYPRODUCTIONREPOSITORY_H