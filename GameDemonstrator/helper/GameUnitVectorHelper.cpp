#include "stdafx.h"
#include "GameUnitVectorHelper.h"
#include "game\GameUnit.h"

GameUnitVectorHelper::GameUnitVectorHelper(QVector<const GameUnit*>& gameUnitVector)
	: GameUnitVector(gameUnitVector)
{

}

const GameUnit* GameUnitVectorHelper::FindGameUnit(const GameUnit* gameUnit) const
{
	Q_ASSERT(gameUnit);
	QVectorIterator<const GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		const GameUnit* currentGameUnit = iterator.next();
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
	QVectorIterator<const GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		const GameUnit* currentGameUnit = iterator.next();
		if (*currentGameUnit == *gameUnit)
		{
			return index;
		}
		index++;
	}
	return NOT_INITIALIZED_INT;
}

const GameUnit* GameUnitVectorHelper::Remove(const GameUnit* gameUnit)
{
	Q_ASSERT(gameUnit);
	int index = 0;
	QVectorIterator<const GameUnit*> iterator(GameUnitVector);
	while (iterator.hasNext())
	{
		const GameUnit* currentGameUnit = iterator.next();
		if (*currentGameUnit == *gameUnit)
		{
			return GameUnitVector.takeAt(index);
		}
		index++;
	}
	return nullptr;
}
