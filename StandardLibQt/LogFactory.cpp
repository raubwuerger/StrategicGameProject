#include "stdafx.h"
#include "LogFactory.h"
#include "LogManager.h"
#include "LogManagerThread.h"
#include "LoggerCout.h"
#include "LogInterface.h"
#include <iostream>

namespace jha
{

LogFactory* LogFactory::Instance = nullptr;
LogManager* LogFactory::LogManager = nullptr;
LogManagerThreadContainer* LogFactory::LogManagerThread = nullptr;

LogFactory::LogFactory()
{

}

LogFactory::LogFactory(const LogFactory&)
{

}

LogFactory* LogFactory::GetInstance()
{
	//TODO: Diese Funktion k�nnte gleichzeitig aufgerufen werden! Durch Semaphore absichern!
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

bool LogFactory::Init()
{
	if( LogManagerThread != nullptr )
	{
		return true;
	}

	LogManager = new jha::LogManager;
	LogManagerThread = new LogManagerThreadContainer(LogManager);
	if( false == LogManagerThread->Init() )
	{
		std::cout << "Error initializing LogManagerThread!" << endl;
		return false;
	}
	LogManager->RegisterLogger( new LoggerCout );

	LogInterface* logInterface = LogInterface().GetInstance();
	logInterface->LogManagerInstance = LogManager;
	if( false == logInterface->Init() )
	{
		std::cout << "Error initializing LogInterface!" << endl;
		return false;
	}
	return true;
}

void LogFactory::Release()
{
	if( LogManagerThread != nullptr )
	{
		LogManagerThread->Stop();
	}
	delete LogManagerThread;
	LogManagerThread = nullptr;
	
	delete LogManager;
	LogManager = nullptr;

	LogInterface().GetInstance()->Release();
}

bool LogFactory::RegisterLogger(jha::Logger* logger)
{
	if( nullptr == LogManager )
	{
		std::cout << "LogManager is null! Call LogFactory::Init()!" << endl;
		return false;
	}
	return LogManager->RegisterLogger(logger);
}

}