#ifndef GAMEUNITVECTORHELPER_H
#define GAMEUNITVECTORHELPER_H

class GameUnit;

class GameUnitVectorHelper
{
public:
	/** */
	GameUnitVectorHelper(QVector<GameUnit*>& gameUnitVector);
	/** */
	GameUnit* FindGameUnit(const GameUnit* gameUnit) const;
	/** */
	int GetIndex(const GameUnit* gameUnit) const;
	/** */
	GameUnit* Remove(const GameUnit* gameUnit);
private:
	QVector<GameUnit*>&		GameUnitVector;
};

#endif // GAMEUNITVECTORHELPER_H