#include "stdafx.h"
#include "LogManagerThread.h"
#include "LogManager.h"
#include "LogFactory.h"
#include "LogInterface.h"

namespace jha
{

LogManagerThreadContainer::LogManagerThreadContainer( jha::LogManager *logManager )
	: LogManager(logManager)
{
	m_Timer = new QTimer(this);
	m_Timer->setInterval(50);
	m_Timer->setTimerType(Qt::PreciseTimer);
}

LogManagerThreadContainer::~LogManagerThreadContainer()
{
	m_Timer->stop();
	delete m_Timer;
	WorkerThread.quit();
	WorkerThread.wait();
}

bool LogManagerThreadContainer::Init()
{
	LogManager->moveToThread(&WorkerThread);
	connect(&WorkerThread, &QThread::finished, LogManager, &QObject::deleteLater);
	connect(LogManager, &LogManager::Finished, this, &LogManagerThreadContainer::HasFinished);
	WorkerThread.start();
	connect(m_Timer, &QTimer::timeout, this, &LogManagerThreadContainer::RequestStartFromTimer);
	connect(this,&LogManagerThreadContainer::StartLogManager, LogManager, &LogManager::WorkMessages);
	return true;
}

void LogManagerThreadContainer::RequestStartFromTimer()
{
	if( LogManagerRunning == true )
	{
		//TODO: Ist wohl noch nicht fertig. Dann warte ich lieber auf das nächste Interval
		return;
	}
	LogManagerRunning = true;
	emit StartLogManager();
}

void LogManagerThreadContainer::HasFinished()
{
	LogManagerRunning = false;
}

void LogManagerThreadContainer::Stop()
{
	m_Timer->stop();
}

void LogManagerThreadContainer::Start()
{
	m_Timer->start();
}

}