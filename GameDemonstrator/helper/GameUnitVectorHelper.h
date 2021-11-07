#ifndef GAMEUNITVECTORHELPER_H
#define GAMEUNITVECTORHELPER_H

class GameUnit;

class GameUnitVectorHelper
{
public:
	/** */
	GameUnitVectorHelper(QVector<const GameUnit*>& gameUnitVector);
	/** */
	const GameUnit* FindGameUnit(const GameUnit* gameUnit) const;
	/** */
	int GetIndex(const GameUnit* gameUnit) const;
	/** */
	const GameUnit* Remove(const GameUnit* gameUnit);
private:
	QVector<const GameUnit*>&		GameUnitVector;
};

#endif // GAMEUNITVECTORHELPER_H