#include "stdafx.h"
#include "GameMainCounter.h"
//#include "XMLTools.h"

GameMainCounter* GameMainCounter::Instance = nullptr;

GameMainCounter* GameMainCounter::GetInstance()
{
	if( nullptr != Instance )
	{
		return Instance;
	}

	Instance = new GameMainCounter;
	return Instance;
}

GameMainCounter::GameMainCounter()
	: MonthIncrement(1)
{
	//ToDo: SetStartDate from Config
	StartDate.setDate( 1900,1,1);
	CurrentDate.setDate( 1900,1,1);
}

GameMainCounter::~GameMainCounter()
{

}

void GameMainCounter::Increment()
{
	CurrentDate = CurrentDate.addMonths(MonthIncrement);
}

const QDate& GameMainCounter::GetCurrentDate() const
{
	return CurrentDate;
}
