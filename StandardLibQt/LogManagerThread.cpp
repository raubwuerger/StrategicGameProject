#include "stdafx.h"
#include "LogManagerThread.h"
#include "LogManager.h"
#include "LogFactory.h"
#include "LogInterface.h"

namespace jha
{

LogManagerThreadContainer::LogManagerThreadContainer( LogManager *logManager )
	: m_LogManager(logManager)
{
	m_Timer = new QTimer(this);
	m_Timer->setInterval(50);
	m_Timer->setTimerType(Qt::PreciseTimer);
}

LogManagerThreadContainer::~LogManagerThreadContainer()
{
	m_Timer->stop();
	delete m_Timer;
	m_WorkerThread.quit();
	m_WorkerThread.wait();
}

bool LogManagerThreadContainer::Init()
{
	m_LogManager->moveToThread(&m_WorkerThread);
	connect(&m_WorkerThread, &QThread::finished, m_LogManager, &QObject::deleteLater);
	connect(m_LogManager, &LogManager::Finished, this, &LogManagerThreadContainer::HasFinished);
	m_WorkerThread.start();
	connect(m_Timer, &QTimer::timeout, this, &LogManagerThreadContainer::RequestStartFromTimer);
	connect(this,&LogManagerThreadContainer::StartLogManager, m_LogManager, &LogManager::WorkMessages);
	return true;
}

void LogManagerThreadContainer::RequestStartFromTimer()
{
	if( m_LogManagerRunning == true )
	{
		//TODO: Ist wohl noch nicht fertig. Dann warte ich lieber auf das nächste Interval
		return;
	}
	m_LogManagerRunning = true;
	emit StartLogManager();
}

void LogManagerThreadContainer::HasFinished()
{
	m_LogManagerRunning = false;
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