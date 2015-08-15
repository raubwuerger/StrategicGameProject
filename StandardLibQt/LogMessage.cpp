#include "stdafx.h"
#include "LogMessage.h"
#include "LogLevel.h"

namespace jha
{

LogMessage::LogMessage( const unsigned long index, const QTime& time, const LogLevel& logLevel, const QString& message, const QString& category )
 :	m_Index(index),
	m_Time(time),
	m_LogLevel(&logLevel),
	m_Message(message),
	m_Category(category)
{
}

LogMessage::LogMessage( const LogMessage& rhs )
 :	m_Index(rhs.m_Index),
	m_Time(rhs.m_Time),
	m_LogLevel(rhs.m_LogLevel),
	m_Message(rhs.m_Message),
	m_Category(rhs.m_Category)
{
}

LogMessage::LogMessage( LogMessage&& rhs )
 :	m_Index(rhs.m_Index),
	m_Time(rhs.m_Time),
	m_LogLevel(rhs.m_LogLevel),
	m_Message(rhs.m_Message),
	m_Category(rhs.m_Category)
{
}

LogMessage& LogMessage::operator=( const LogMessage& rhs )
{
	m_Index		= rhs.m_Index;
	m_Time		= rhs.m_Time;
	m_LogLevel	= rhs.m_LogLevel;
	m_Message	= rhs.m_Message;
	m_Category	= rhs.m_Category;
	return *this;
}

LogMessage& LogMessage::operator=( LogMessage&& rhs )
{
	m_Index		= rhs.m_Index;
	m_Time		= rhs.m_Time;
	m_LogLevel	= rhs.m_LogLevel;
	m_Message	= rhs.m_Message;
	m_Category	= rhs.m_Category;
	return *this;
}

int LogMessage::operator==( const LogMessage& rhs ) const
{
	return m_Index == rhs.m_Index;
}

int LogMessage::operator<( const LogMessage& rhs ) const
{
	return m_Index < rhs.m_Index;
}

unsigned long LogMessage::GetIndex() const
{
	return m_Index;
}

const QString& LogMessage::GetMessage() const
{
	return m_Message;
}

const QString& LogMessage::GetCategory() const
{
	return m_Category;
}

const LogLevel& LogMessage::GetLogLevel() const
{
	return *m_LogLevel;
}

const QTime& LogMessage::GetLogTime() const
{
	return m_Time;
}

}