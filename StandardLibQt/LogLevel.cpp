#include "stdafx.h"
#include "LogLevel.h"

namespace jha
{

	//==============================================================================
	LogLevel::LogLevel( const LogLevel& rhs )
		: 	Name(rhs.Name),
			LogFilePrefix(rhs.LogFilePrefix),
			Value(rhs.Value),
			Color(rhs.Color)
	{
	}

	//==============================================================================
	LogLevel::LogLevel( const QString& name, const QString& prefix, const QColor& color, LOGLEVEL value )
		: 	Name(name),
			LogFilePrefix(prefix),
			Value(value),
			Color(color)
	{
	}

	//==============================================================================
	LogLevel::~LogLevel()
	{
	}

	//==============================================================================
	LogLevel& LogLevel::operator=( const LogLevel& rhs )
	{
		Name				= rhs.Name;
		LogFilePrefix		= rhs.LogFilePrefix;
		Value	= rhs.Value;
		Color				= rhs.Color;
		return *this;
	}

	//==============================================================================
	LogLevel& LogLevel::operator=( LogLevel&& rhs )
	{
		Name				= rhs.Name;
		LogFilePrefix		= rhs.LogFilePrefix;
		Value				= rhs.Value;
		Color				= rhs.Color;
		return *this;
	}

	//==============================================================================
	int LogLevel::operator==( const LogLevel& rhs ) const
	{
		return Value == rhs.Value;
	}

	//==============================================================================
	int LogLevel::operator<( const LogLevel& rhs ) const
	{
		return Value < rhs.Value;
	}

	//==============================================================================
	int LogLevel::operator<=( const LogLevel& rhs ) const
	{
		return Value <= rhs.Value;
	}

	//==============================================================================
	int LogLevel::operator>=( const LogLevel& rhs ) const
	{
		return Value >= rhs.Value;
	}

	//==============================================================================
	const QString& LogLevel::GetName() const
	{
		return Name;
	}

	//==============================================================================
	const QString& LogLevel::GetLogFilePrefix() const
	{
		return LogFilePrefix;
	}

	//==============================================================================
	const QColor& LogLevel::GetColor() const
	{
		return Color;
	}

}