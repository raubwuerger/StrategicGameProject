#include "stdafx.h"
#include "LogLevel.h"

namespace jha
{

LogLevel::LogLevel( const LogLevel& rhs )
	: 	m_Name(rhs.m_Name),
		m_LogFilePrefix(rhs.m_LogFilePrefix),
		m_MessageBoxType(rhs.m_MessageBoxType),
		m_Color(rhs.m_Color)
{
}

LogLevel::LogLevel( const std::string& name, const std::string& prefix, UINT messageBoxType, COLORREF color )
	: 	m_Name(name),
		m_LogFilePrefix(prefix),
		m_MessageBoxType(messageBoxType),
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
	m_MessageBoxType	= rhs.m_MessageBoxType;
	m_Color				= rhs.m_Color;
	return *this;
}

LogLevel& LogLevel::operator=( LogLevel&& rhs )
{
	m_Name				= rhs.m_Name;
	m_LogFilePrefix		= rhs.m_LogFilePrefix;
	m_MessageBoxType	= rhs.m_MessageBoxType;
	m_Color				= rhs.m_Color;
	return *this;
}

int LogLevel::operator==( const LogLevel& rhs ) const
{
	return m_Name == rhs.m_Name;
}

int LogLevel::operator<( const LogLevel& rhs ) const
{
	return m_Name < rhs.m_Name;
}

const std::string& LogLevel::GetName() const
{
	return m_Name;
}

const std::string& LogLevel::GetLogFilePrefix() const
{
	return m_LogFilePrefix;
}

UINT LogLevel::GetMessageBoxType() const
{
	return m_MessageBoxType;
}

COLORREF LogLevel::GetColor() const
{
	return m_Color;
}


}
