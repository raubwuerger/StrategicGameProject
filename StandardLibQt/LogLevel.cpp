#include "stdafx.h"
#include "LogLevel.h"

namespace jha
{

LogLevel::LogLevel( const LogLevel& rhs )
	: 	m_Name(rhs.m_Name),
		m_LogFilePrefix(rhs.m_LogFilePrefix),
		m_Value(rhs.m_Value),
		m_Color(rhs.m_Color)
{
}

LogLevel::LogLevel( const QString& name, const QString& prefix, const QColor& color, LOGLEVEL value )
	: 	m_Name(name),
		m_LogFilePrefix(prefix),
		m_Value(value),
		m_Color(color)
{
}

LogLevel::~LogLevel()
{
}

LogLevel& LogLevel::operator=( const LogLevel& rhs )
{
	m_Name				= rhs.m_Name;
	m_LogFilePrefix		= rhs.m_LogFilePrefix;
	m_Value	= rhs.m_Value;
	m_Color				= rhs.m_Color;
	return *this;
}

LogLevel& LogLevel::operator=( LogLevel&& rhs )
{
	m_Name				= rhs.m_Name;
	m_LogFilePrefix		= rhs.m_LogFilePrefix;
	m_Value				= rhs.m_Value;
	m_Color				= rhs.m_Color;
	return *this;
}

int LogLevel::operator==( const LogLevel& rhs ) const
{
	return m_Value == rhs.m_Value;
}

int LogLevel::operator<( const LogLevel& rhs ) const
{
	return m_Value < rhs.m_Value;
}

const QString& LogLevel::GetName() const
{
	return m_Name;
}

const QString& LogLevel::GetLogFilePrefix() const
{
	return m_LogFilePrefix;
}

const QColor& LogLevel::GetColor() const
{
	return m_Color;
}

}