#include "stdafx.h"
#include "GameMainThread.h"
#include "GameMainLoop.h"

GameMainThread::GameMainThread()
	: m_TurnFinished(true)
{
	m_TriggerGameMainLoop = new QTimer(this);
}

GameMainThread::~GameMainThread()
{
	m_TriggerGameMainLoop->stop();
	delete m_TriggerGameMainLoop;
}

void GameMainThread::run()
{
	exec();
}

void GameMainThread::Init( GameMainLoop *gameMainLoop )
{
	connect(m_TriggerGameMainLoop, SIGNAL(timeout()), this, SLOT(CheckTriggerGameMainLoop()));
	connect(gameMainLoop, SIGNAL(TurnFinished(QDate)), this, SLOT(TurnFinished()));
	connect(this, SIGNAL(TriggerGameMainLoop()), gameMainLoop, SLOT(Run()));
	m_TriggerGameMainLoop->start(100);
}

void GameMainThread::CheckTriggerGameMainLoop()
{
	if( m_TurnFinished == false )
	{
		return;
	}
	m_TurnFinished = false;
	emit TriggerGameMainLoop();
}

void GameMainThread::TurnFinished()
{
	m_TurnFinished = true;
}

