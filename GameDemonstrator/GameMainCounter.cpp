#include "stdafx.h"
#include "GameMainCounter.h"
//#include "XMLTools.h"

GameMainCounter::GameMainCounter()
	: MonthIncrement(1)
{
	//ToDo: SetStartDate from Config
//	QString fileName(".\\conf\\Globals.xml");
//	CDomElementFinder( QString() ).TryFindElement("",1200);
	GameDate.setDate( 1900,1,1);
}

GameMainCounter::~GameMainCounter()
{

}

void GameMainCounter::Increment()
{
	GameDate = GameDate.addMonths(MonthIncrement);
}

const QDate& GameMainCounter::GetGameDate() const
{
	return GameDate;
}
