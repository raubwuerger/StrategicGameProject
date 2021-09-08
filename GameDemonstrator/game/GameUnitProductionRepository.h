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
	bool RegisterGameUnitProduction(const GameUnitProduction* gameUnitProduction);
	/** */
	bool Init() override;
	/** */
	void Release() override;
	/** */
	void UpdateTurn();
private:
	/** */
	GameUnitProductionRepository();
	/** */
	void CreateGameUnit(const GameUnitProduction* gameUnitProduction);
private:
	QMap<int, const GameUnitProduction*>	CityProductions;
	static GameUnitProductionRepository* Instance;
};

#endif // GAMECITYPRODUCTIONREPOSITORY_H