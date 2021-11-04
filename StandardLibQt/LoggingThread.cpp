#include "stdafx.h"
#include "LoggingThread.h"
#include "LoggingWorker.h"

namespace jha
{

	//==============================================================================
		LoggingThread::LoggingThread()
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
		quit();
		wait();
	}

	//==============================================================================
	bool LoggingThread::Init()
	{
		start();
		return true;
	}

}