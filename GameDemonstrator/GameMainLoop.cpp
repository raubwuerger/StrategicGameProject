#include "stdafx.h"
#include "GameMainLoop.h"
#include "GameMainCounter.h"

static int counter = 0;
GameMainLoop::GameMainLoop(QObject *parent)
	: QObject(parent),
	m_RunLoop(false)
{
	GameCounter = new GameMainCounter(parent);
}

GameMainLoop::~GameMainLoop()
{
	delete GameCounter;
}

void GameMainLoop::Start()
{
	m_RunLoop = true;
	Run();
}

void GameMainLoop::Pause()
{
	m_RunLoop = false;
}

void GameMainLoop::Stop()
{
	m_RunLoop = false;
//	moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
}

void GameMainLoop::Run()
{
	if( m_RunLoop == false )
	{
		return;
	}
	GameCounter->Increment();
	emit TurnFinished( GameCounter->GetGameDate() );
}

