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
	LogFactory::LogFactory()
	{
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
		if( false == Instance->Init() )
		{
			std::cout << "Error initializing LogFactory!" << endl;
		}
		return Instance;
	}

	//==============================================================================
	bool LogFactory::Init(bool startLogging)
	{
		if( LoggingThreadObject != nullptr )
		{
			return true;
		}

		LoggingWorkerObject = new jha::LoggingWorker;
		LoggingThreadObject = new LoggingThread(LoggingWorkerObject);
		if( false == LoggingThreadObject->Init() )
		{
			std::cout << "Error initializing LogManagerThread!" << endl;
			return false;
		}
		LoggingWorkerObject->RegisterLogger( new LoggerCout );

		LogInterface* logInterface = LogInterface().GetInstance();
		logInterface->LoggingWorkerObject = LoggingWorkerObject;
		if( false == logInterface->Init() )
		{
			std::cout << "Error initializing LogInterface!" << endl;
			return false;
		}

		if (true == startLogging)
		{
			LoggingThreadObject->Start();
		}

		return true;
	}

	//==============================================================================
	void LogFactory::Release()
	{
		if( LoggingThreadObject != nullptr )
		{
			LoggingThreadObject->Stop();
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

	//==============================================================================
	void LogFactory::Enable()
	{
		LoggingThreadObject->Start();
	}

	//==============================================================================
	void LogFactory::Disable()
	{
		LoggingThreadObject->Stop();
	}

	//==============================================================================
	bool LogFactory::GetEnabled() const
	{
		return LoggingThreadObject->GetIsRunning();
	}

}