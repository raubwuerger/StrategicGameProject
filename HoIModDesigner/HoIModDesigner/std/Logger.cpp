#include "stdafx.h"
#include "Logger.h"
#include "LogMessage.h"

namespace jha
{

const QString Logger::DEFAULT_TIME_FORMAT = "hh:mm:ss.zzz";
const QString Logger::DEFAULT_DATE_FORMAT = "yyyy-MM-dd";

Logger::Logger( const QString& name )
	: m_Name(name),
	m_Enabled(true)
{
}

const QString& Logger::Name() const
{
	return m_Name;
}

bool Logger::GetEnabled() const
{
	return m_Enabled;
}

void Logger::SetEnabled( bool enable )
{
	m_Enabled = enable;
}

bool Logger::LogMessage( const QVector<jha::LogMessage*>& logMessage )
{
	if( m_Enabled == false )
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


}