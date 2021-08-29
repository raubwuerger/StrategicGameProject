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

void GameMainLoop::SlotStep()
{
	GameMainCounter::GetInstance()->Increment();
	emit SignalTurnFinished(GameMainCounter::GetInstance()->GetCurrentDate());
}

