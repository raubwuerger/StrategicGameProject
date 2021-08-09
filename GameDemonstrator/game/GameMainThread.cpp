#include "stdafx.h"
#include "GameMainThread.h"
#include "GameMainLoop.h"

GameMainThread::GameMainThread()
	: HasTurnFinished(true)
{
	TriggerGameMainLoop = new QTimer(this);
}

GameMainThread::~GameMainThread()
{
	TriggerGameMainLoop->stop();
	delete TriggerGameMainLoop;
}

void GameMainThread::run()
{
	exec();
}

void GameMainThread::Init( GameMainLoop *gameMainLoop )
{
	connect(TriggerGameMainLoop, &QTimer::timeout, this, &GameMainThread::SlotCheckTriggerGameMainLoop);
	connect(gameMainLoop, &GameMainLoop::SignalTurnFinished, this, &GameMainThread::SlotTurnFinished);
	connect(this, &GameMainThread::SignalTriggerGameMainLoop, gameMainLoop, &GameMainLoop::SlotRun);
	TriggerGameMainLoop->start(100);
}

void GameMainThread::SlotCheckTriggerGameMainLoop()
{
	if (HasTurnFinished == false)
	{
		return;
	}
	HasTurnFinished = false;
	emit SignalTriggerGameMainLoop();
}

void GameMainThread::SlotTurnFinished()
{
	HasTurnFinished = true;
}
