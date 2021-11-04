#include "stdafx.h"
#include "LogFactory.h"
#include "LoggingWorker.h"
#include "LogManagerThread.h"
#include "LoggerCout.h"
#include "LogInterface.h"
#include <iostream>

namespace jha
{

	LogFactory* LogFactory::Instance = nullptr;
	LoggingWorker* LogFactory::LoggingWorkerObject = nullptr;
	LogManagerThreadContainer* LogFactory::LogManagerThread = nullptr;

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
		if( LogManagerThread != nullptr )
		{
			return true;
		}

		LoggingWorkerObject = new jha::LoggingWorker;
		LogManagerThread = new LogManagerThreadContainer(LoggingWorkerObject);
		if( false == LogManagerThread->Init() )
		{
			std::cout << "Error initializing LogManagerThread!" << endl;
			return false;
		}
		LoggingWorkerObject->RegisterLogger( new LoggerCout );

		LogInterface* logInterface = LogInterface().GetInstance();
		logInterface->LogManagerInstance = LoggingWorkerObject;
		if( false == logInterface->Init() )
		{
			std::cout << "Error initializing LogInterface!" << endl;
			return false;
		}

		if (true == startLogging)
		{
			LogManagerThread->Start();
		}

		return true;
	}

	//==============================================================================
	void LogFactory::Release()
	{
		if( LogManagerThread != nullptr )
		{
			LogManagerThread->Stop();
		}
		delete LogManagerThread;
		LogManagerThread = nullptr;
	
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
		LogManagerThread->Start();
	}

	//==============================================================================
	void LogFactory::Disable()
	{
		LogManagerThread->Stop();
	}

	//==============================================================================
	bool LogFactory::GetEnabled() const
	{
		return LogManagerThread->GetIsRunning();
	}

}