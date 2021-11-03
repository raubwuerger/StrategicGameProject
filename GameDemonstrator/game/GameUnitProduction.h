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
	void SetModelTypeId(int modelTypeId) const;
	/** */
	int GetModelTypeId() const;
	/** */
	void UpdateProductionProgress(int updateValue) const;
	/** */
	void ClearProductionProgress() const;
	/** */
	double GetProductionProgress() const;
	/** */
	void SetProductionProgress(double progress) const;
	/** */
	bool IsGameUnitInProduction() const;
	/** */
	QString toString() const;
private:
	int			GameCityId;
	mutable int	ModelUnitTypeId;			//TODO: 9999 == Efficiency
	mutable double	ProductionProgress;
};

#endif // GAMEUNITPRODUCTION_H 