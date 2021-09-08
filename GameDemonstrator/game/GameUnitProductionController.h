#ifndef GAMECITYPRODUCTIONREPOSITORY_H
#define GAMECITYPRODUCTIONREPOSITORY_H

#include "BaseRepository.h"

class GameUnitProduction;

class GameUnitProductionController : public BaseRepository
{
public:
	/** */
	static GameUnitProductionController* GetInstance();
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
	GameUnitProductionController();
	/** */
	void CreateGameUnit(const GameUnitProduction* gameUnitProduction);
	/** */
	bool IsGameUnitOnMapItem(int gameMapId) const;
private:
	QMap<int, const GameUnitProduction*>	CityProductions;
	static GameUnitProductionController* Instance;
};

#endif // GAMECITYPRODUCTIONREPOSITORY_H