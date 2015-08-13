#include "stdafx.h"
#include "GameMainCounter.h"

GameMainCounter::GameMainCounter(QObject *parent)
	: QObject(parent),
	MonthIncrement(1)
{
	GameDate.setDate(1900,1,1);
}

GameMainCounter::~GameMainCounter()
{

}

void GameMainCounter::Increment()
{
	GameDate = GameDate.addMonths(MonthIncrement);
}
