#include "stdafx.h"
#include "LoggingThread.h"
#include "LoggingWorker.h"

namespace jha
{

	//==============================================================================
	LoggingThread::LoggingThread( jha::LoggingWorker *logManager )
		: LogManagerObject(logManager)
	{
		Timer = new QTimer(this);
		Timer->setInterval(50);
		Timer->setTimerType(Qt::PreciseTimer);
	}

	//==============================================================================
	LoggingThread::~LoggingThread()
	{
		Timer->stop();
		delete Timer;
		WorkerThread.quit();
		WorkerThread.wait();
	}

	//==============================================================================
	bool LoggingThread::Init()
	{
		LogManagerObject->moveToThread(&WorkerThread);
		connect(&WorkerThread, &QThread::finished, LogManagerObject, &QObject::deleteLater);
		connect(LogManagerObject, &LoggingWorker::Finished, this, &LoggingThread::HasFinished);
		WorkerThread.start(); //WorkerThread darf nicht gestartet werden ...
		connect(Timer, &QTimer::timeout, this, &LoggingThread::RequestStartFromTimer);
		connect(this, &LoggingThread::StartLogManager, LogManagerObject, &LoggingWorker::WorkMessages);
		return true;
	}

	//==============================================================================
	void LoggingThread::RequestStartFromTimer()
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
	void LoggingThread::HasFinished()
	{
		LogManagerRunning = false;
	}

	//==============================================================================
	void LoggingThread::Stop()
	{
		Timer->stop();
	}

	bool LoggingThread::GetIsRunning() const
	{
		return Timer->isActive();
	}

	//==============================================================================
	void LoggingThread::Start()
	{
		Timer->start();
	}

}