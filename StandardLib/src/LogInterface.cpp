#include "stdafx.h"
#include "LogInterface.h"
#include "LogLevel.h"
#include "LogFactory.h"
#include "LogManager.h"
#include "LogMessage.h"
#include "DateTime.h"

namespace jha
{

LogInterface* GetLog()
{
	return log;
}

const LogLevel LogInterface::L_NONE("None","n",1,1);
const LogLevel LogInterface::L_FATAL("Fatal","f",1,1);
const LogLevel LogInterface::L_ERROR("Error","e",1,1);;
const LogLevel LogInterface::L_WARNING("Warning","w",1,1);
const LogLevel LogInterface::L_MESSAGE("Message","m",1,1);
const LogLevel LogInterface::L_INFO("Info","i",1,1);
const LogLevel LogInterface::L_TRACE("Trace","t",1,1);
const LogLevel LogInterface::L_DEBUG("Debug","d",1,1);

LogInterface::LogInterface()
{
	int created = 0;
}

void LogInterface::Log( const std::string& message, LOGLEVEL logLevel, const std::string& category )
{
	//TODO: richtiges Loglevel bestimmen!
	LogFactory().GetLogManager()->AddLogMessage( new LogMessage( LogFactory().GetLogManager()->CreateLogMessageIndex(), Time(), LogInterface::L_NONE, message, category ) );
}

bool LogInterface::RegisterLogger( Logger* logger )
{
	return LogFactory().GetLogManager()->RegisterLogger(logger);
}

bool LogInterface::Init()
{
	try
	{
		if( log == nullptr )
		{
			log = new LogInterface;
		}
		LogFactory().Init();
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool LogInterface::CleanUp()
{
	delete log;
	log = nullptr;

	LogFactory().CleanUp();
	return true;
}

}