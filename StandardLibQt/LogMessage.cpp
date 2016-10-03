#include "stdafx.h"
#include "LogMessage.h"
#include "LogLevel.h"

namespace jha
{

LogMessage::LogMessage( const unsigned long index, const QTime& time, const jha::LogLevel& logLevel, const QString& message, const QString& category )
 :	Index(index),
	Time(time),
	LogLevel(&logLevel),
	Message(message),
	Category(category)
{
}

LogMessage::LogMessage( const LogMessage& rhs )
 :	Index(rhs.Index),
	Time(rhs.Time),
	LogLevel(rhs.LogLevel),
	Message(rhs.Message),
	Category(rhs.Category)
{
}

LogMessage::LogMessage( LogMessage&& rhs )
 :	Index(rhs.Index),
	Time(rhs.Time),
	LogLevel(rhs.LogLevel),
	Message(rhs.Message),
	Category(rhs.Category)
{
}

LogMessage& LogMessage::operator=( const LogMessage& rhs )
{
	Index		= rhs.Index;
	Time		= rhs.Time;
	LogLevel	= rhs.LogLevel;
	Message	= rhs.Message;
	Category	= rhs.Category;
	return *this;
}

LogMessage& LogMessage::operator=( LogMessage&& rhs )
{
	Index		= rhs.Index;
	Time		= rhs.Time;
	LogLevel	= rhs.LogLevel;
	Message	= rhs.Message;
	Category	= rhs.Category;
	return *this;
}

int LogMessage::operator==( const LogMessage& rhs ) const
{
	return Index == rhs.Index;
}

int LogMessage::operator<( const LogMessage& rhs ) const
{
	return Index < rhs.Index;
}

unsigned long LogMessage::GetIndex() const
{
	return Index;
}

const QString& LogMessage::GetMessage() const
{
	return Message;
}

const QString& LogMessage::GetCategory() const
{
	return Category;
}

const LogLevel& LogMessage::GetLogLevel() const
{
	return *LogLevel;
}

const QTime& LogMessage::GetLogTime() const
{
	return Time;
}

}