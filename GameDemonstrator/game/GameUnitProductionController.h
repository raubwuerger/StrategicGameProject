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
	bool UpdateGameUnitProduction(const GameUnitProduction& gameUnitProduction);
	/** */
	const GameUnitProduction* CreateDefaultGameUnitProduction(int cityId);
	/** */
	void RemoveGameUnitProduction(int cityId);
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
	bool IsGameUnitOnMapTile(int gameMapId) const;
	/** */
	bool IsCityNeutral(const GameUnitProduction* gameUnitProduction) const;
private:
	QMap<int, const GameUnitProduction*>	CityProductions;
	static GameUnitProductionController*	Instance;
};

#endif // GAMECITYPRODUCTIONREPOSITORY_H