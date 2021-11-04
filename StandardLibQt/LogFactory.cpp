#include "stdafx.h"
#include "LogFactory.h"
#include "LoggingWorker.h"
#include "LoggingThread.h"
#include "LoggerCout.h"
#include "LogInterface.h"
#include <iostream>

namespace jha
{

	LogFactory* LogFactory::Instance = nullptr;
	LoggingWorker* LogFactory::LoggingWorkerObject = nullptr;
	LoggingThread* LogFactory::LoggingThreadObject = nullptr;

	//==============================================================================
	LogFactory::LogFactory(QObject *parent)
		: QObject(parent)
	{
		LoggingWorkerObject = new jha::LoggingWorker;
		LoggingThreadObject = new LoggingThread();
	}

	//==============================================================================
	LogFactory::LogFactory(const LogFactory&)
	{
	}

	//==============================================================================
	LogFactory* LogFactory::GetInstance()
	{
		//TODO: Diese Funktion könnte gleichzeitig aufgerufen werden! Durch Semaphore absichern!
		if( Instance != nullptr )
		{
			return Instance;
		}
		Instance = new LogFactory;
		return Instance;
	}

	//==============================================================================
	bool LogFactory::Init(bool startLogging)
	{
		LoggingWorkerObject->moveToThread(LoggingThreadObject);

		if( false == LoggingThreadObject->Init() )
		{
			std::cout << "Error initializing LogManagerThread!" << endl;
			return false;
		}

		LogInterface* logInterface = LogInterface().GetInstance();
		logInterface->LoggingWorkerObject = LoggingWorkerObject;
		if( false == logInterface->Init() )
		{
			std::cout << "Error initializing LogInterface!" << endl;
			return false;
		}

		return true;
	}

	//==============================================================================
	void LogFactory::Release()
	{
		if( LoggingThreadObject != nullptr )
		{
			LoggingThreadObject->exit();
		}
		delete LoggingThreadObject;
		LoggingThreadObject = nullptr;
	
		delete LoggingWorkerObject;
		LoggingWorkerObject = nullptr;

		LogInterface().GetInstance()->Release();
	}

	//==============================================================================
	bool LogFactory::RegisterLogger(jha::Logger* logger)
	{
		if( nullptr == LoggingWorkerObject )
		{
			std::cout << "LogManager is null! Call LogFactory::Init()!" << endl;
			return false;
		}
		return LoggingWorkerObject->RegisterLogger(logger);
	}

}