#include "stdafx.h"
#include "GameUnitVectorHelper.h"
#include "game\GameUnit.h"

GameUnitVectorHelper::GameUnitVectorHelper(QVector<GameUnit*>& gameUnitVector)
	: GameUnitVector(gameUnitVector)
{

}

GameUnit* GameUnitVectorHelper::FindGameUnit(const GameUnit* gameUnit) const
{
	Q_ASSERT(gameUnit);
	QVectorIterator<GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		GameUnit* currentGameUnit = iterator.next();
		if (*currentGameUnit == *gameUnit)
		{
			return currentGameUnit;
		}
	}
	return nullptr;
}

int GameUnitVectorHelper::GetIndex(const GameUnit* gameUnit) const
{
	Q_ASSERT(gameUnit);
	int index = 0;
	QVectorIterator<GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		GameUnit* currentGameUnit = iterator.next();
		if (*currentGameUnit == *gameUnit)
		{
			return index;
		}
		index++;
	}
	return NOT_INITIALIZED_INT;
}

GameUnit* GameUnitVectorHelper::Remove(const GameUnit* gameUnit)
{
	Q_ASSERT(gameUnit);
	int index = 0;
	QVectorIterator<GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		GameUnit* currentGameUnit = iterator.next();
		if (*currentGameUnit == *gameUnit)
		{
			return GameUnitVector.takeAt(index);
		}
		index++;
	}
	return nullptr;
}
