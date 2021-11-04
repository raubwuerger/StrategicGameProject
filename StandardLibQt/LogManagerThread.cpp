#include "stdafx.h"
#include "LogManagerThread.h"
#include "LoggingWorker.h"

namespace jha
{

	//==============================================================================
	LogManagerThreadContainer::LogManagerThreadContainer( jha::LoggingWorker *logManager )
		: LogManagerObject(logManager)
	{
		Timer = new QTimer(this);
		Timer->setInterval(50);
		Timer->setTimerType(Qt::PreciseTimer);
	}

	//==============================================================================
	LogManagerThreadContainer::~LogManagerThreadContainer()
	{
		Timer->stop();
		delete Timer;
		WorkerThread.quit();
		WorkerThread.wait();
	}

	//==============================================================================
	bool LogManagerThreadContainer::Init()
	{
		LogManagerObject->moveToThread(&WorkerThread);
		connect(&WorkerThread, &QThread::finished, LogManagerObject, &QObject::deleteLater);
		connect(LogManagerObject, &LoggingWorker::Finished, this, &LogManagerThreadContainer::HasFinished);
		WorkerThread.start(); //WorkerThread darf nicht gestartet werden ...
		connect(Timer, &QTimer::timeout, this, &LogManagerThreadContainer::RequestStartFromTimer);
		connect(this, &LogManagerThreadContainer::StartLogManager, LogManagerObject, &LoggingWorker::WorkMessages);
		return true;
	}

	//==============================================================================
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

	//==============================================================================
	void LogManagerThreadContainer::HasFinished()
	{
		LogManagerRunning = false;
	}

	//==============================================================================
	void LogManagerThreadContainer::Stop()
	{
		Timer->stop();
	}

	bool LogManagerThreadContainer::GetIsRunning() const
	{
		return Timer->isActive();
	}

	//==============================================================================
	void LogManagerThreadContainer::Start()
	{
		Timer->start();
	}

}