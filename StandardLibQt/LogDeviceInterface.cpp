#include "stdafx.h"
#include "LogDeviceInterface.h"
#include "LogInterface.h"
#include "LogMessage.h"

LogDeviceInterface::LogDeviceInterface(const QString& name)
	: Name(name),
	DEFAULT_TIME_FORMAT("hh:mm:ss.zzz"),
	DEFAULT_DATE_FORMAT("yyyy-MM-dd"),
	SEPARATOR("\t"),
	LogLevelInstance(jha::LogInterface::LOGLEVEL_NONE)
{

}

bool LogDeviceInterface::LogThisLogLevel(jha::LogMessage *message) const
{
	Q_ASSERT(message);
	return message->GetLogLevel() <= LogLevelInstance;
}

bool LogDeviceInterface::LogMessage(const jha::LogMessage* logMessage)
{
	return DoLogMessage(logMessage);
}

QString LogDeviceInterface::GetName() const
{
	return Name;
}

QString LogDeviceInterface::CreateLogString(const jha::LogMessage *message) const
{
	Q_ASSERT(message);
	return QString(message->GetLogTime().toString(DEFAULT_TIME_FORMAT)) + SEPARATOR + QString(message->GetLogLevel().GetName()) + SEPARATOR + SEPARATOR + QString(message->GetCategory()) + SEPARATOR + SEPARATOR + QString(message->GetMessage());
}
