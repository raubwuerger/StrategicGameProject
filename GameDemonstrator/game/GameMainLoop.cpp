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

void GameMainLoop::Start()
{
	RunLoop = true;
	Run();
}

void GameMainLoop::Pause()
{
	RunLoop = false;
}

void GameMainLoop::Stop()
{
	RunLoop = false;
//	moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
}

void GameMainLoop::Run()
{
	if( RunLoop == false )
	{
		return;
	}
	GameMainCounter::GetInstance()->Increment();
	emit TurnFinished( GameMainCounter::GetInstance()->GetCurrentDate() );
}

void GameMainLoop::Step()
{
	GameMainCounter::GetInstance()->Increment();
	emit TurnFinished( GameMainCounter::GetInstance()->GetCurrentDate() );
}

