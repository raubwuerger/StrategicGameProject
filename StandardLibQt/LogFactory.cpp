#include "stdafx.h"
#include "LogFactory.h"
#include "LogManager.h"
#include "LogManagerThread.h"
#include "LoggerCout.h"
#include "LogInterface.h"

namespace jha
{

LogManager* LogFactory::LogManager = nullptr;
LogManagerThreadContainer* LogFactory::LogManagerThread = nullptr;

bool LogFactory::Init()
{
	if( LogManagerThread != nullptr )
	{
		return true;
	}

	LogManager = new jha::LogManager;
	LogManager->RegisterLogger( new LoggerCout );
	LogManagerThread = new LogManagerThreadContainer(LogManager);
	LogManagerThread->Init();
	return true;
}

void LogFactory::CleanUp()
{
	if( LogManagerThread != nullptr )
	{
		LogManagerThread->Stop();
	}
	delete LogManagerThread;
	LogManagerThread = nullptr;
	
	delete LogManager;
	LogManager = nullptr;
}

LogManager* LogFactory::GetLogManager()
{
	return LogManager;
}

}