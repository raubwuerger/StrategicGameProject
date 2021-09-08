#ifndef GAMEUNITPRODUCTION_H
#define GAMEUNITPRODUCTION_H

class GameUnitProduction
{
public:
	/** */
	GameUnitProduction( int gameCityItemId );
	/** */
	int GetGameCityId() const;
	/** */
	void SetGameUnitId(int gameUnitId);
	/** */
	void CancelGameUnitProduction();
	/** */
	int GetGameUnitId() const;
	/** */
	void UpdateProductionProgress(int updateValue);
	/** */
	void ClearProductionProgress();
	/** */
	int GetProductionProgress() const;
	/** */
	void SetProductionProgress(int progress);
	/** */
	bool IsGameUnitInProduction() const;
private:
	int GameCityId;
	int GameUnitId;
	int	ProductionProgress;
};

#endif // GAMEUNITPRODUCTION_H 