#include "stdafx.h"
#include "GameMainLoop.h"
#include "GameMainCounter.h"

static int counter = 0;
GameMainLoop::GameMainLoop(QObject *parent)
	: QObject(parent),
	RunLoop(false)
{
	GameCounter = new GameMainCounter(parent);
}

GameMainLoop::~GameMainLoop()
{
	delete GameCounter;
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
	GameCounter->Increment();
	emit TurnFinished( GameCounter->GetGameDate() );
}

