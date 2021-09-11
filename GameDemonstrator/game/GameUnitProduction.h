#ifndef GAMEUNITPRODUCTION_H
#define GAMEUNITPRODUCTION_H

class GameUnitProduction
{
public:
	/** */
	GameUnitProduction( int gameCityId );
	/** */
	GameUnitProduction(const GameUnitProduction& rhs);
	/** */
	int GetGameCityId() const;
	/** */
	void SetGameUnitId(int gameUnitId) const;
	/** */
	int GetGameUnitId() const;
	/** */
	void UpdateProductionProgress(int updateValue) const;
	/** */
	void ClearProductionProgress() const;
	/** */
	int GetProductionProgress() const;
	/** */
	void SetProductionProgress(int progress) const;
	/** */
	bool IsGameUnitInProduction() const;
	/** */
	QString toString() const;
private:
	int			GameCityId;
	mutable int	GameUnitId;			//TODO: 9999 == Efficiency
	mutable int	ProductionProgress;
};

#endif // GAMEUNITPRODUCTION_H 