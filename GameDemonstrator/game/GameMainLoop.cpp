#include "stdafx.h"
#include "GameMainLoop.h"
#include "GameMainCounter.h"

static int counter = 0;
GameMainLoop::GameMainLoop(QObject *parent)
	: QObject(parent),
	RunLoop(false)
{
}

GameMainLoop::~GameMainLoop()
{
}

void GameMainLoop::SlotStart()
{
	RunLoop = true;
	SlotRun();
}

void GameMainLoop::SlotPause()
{
	RunLoop = false;
}

void GameMainLoop::SlotStop()
{
	RunLoop = false;
//	moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
}

void GameMainLoop::SlotRun()
{
	if( RunLoop == false )
	{
		return;
	}
	GameMainCounter::GetInstance()->Increment();
	emit SignalTurnFinished( GameMainCounter::GetInstance()->GetCurrentDate() );
}

void GameMainLoop::SlotStep()
{
	GameMainCounter::GetInstance()->Increment();
	emit SignalTurnFinished(GameMainCounter::GetInstance()->GetCurrentDate());
}

