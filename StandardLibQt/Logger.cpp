#include "stdafx.h"
#include "Logger.h"
#include "LogMessage.h"
#include "LogInterface.h"

namespace jha
{

const QString Logger::DEFAULT_TIME_FORMAT = "hh:mm:ss.zzz";
const QString Logger::DEFAULT_DATE_FORMAT = "yyyy-MM-dd";

Logger::Logger( const QString& name )
	: Name(name),
	Enabled(true),
	LogLevel(LogInterface::LOGLEVEL_DEBUG)
{
}

const QString& Logger::GetName() const
{
	return Name;
}

bool Logger::GetEnabled() const
{
	return Enabled;
}

void Logger::SetEnabled( bool enable )
{
	Enabled = enable;
}

bool Logger::LogMessage( const QVector<jha::LogMessage*>& logMessage )
{
	if( Enabled == false )
	{
		return false;
	}
	return DoLogMessage(logMessage);
}

QString Logger::CreateDefaultLogString( jha::LogMessage *message ) const
{
	if( message == nullptr )
	{
		return QString();
	}
	return QString(message->GetLogTime().toString(jha::Logger::DEFAULT_TIME_FORMAT)) +QString("\t") +QString(message->GetLogLevel().GetName()) +QString("\t\t") +QString(message->GetCategory())  +QString("\t\t") +QString(message->GetMessage());
}

bool Logger::LogThisLogLevel( jha::LogMessage *message ) const
{
	if( message == nullptr )
	{
		return false;
	}
	return message->GetLogLevel() < LogLevel;
}


}