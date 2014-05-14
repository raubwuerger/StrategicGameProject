#pragma once
#include <string>
#include "LogInterface.h"
#include "DateTime.h"
#include "LogLevel.h"

namespace jha
{

class LogMessage
{
public:
/** Constructor */
	LogMessage( const unsigned long index, const Time& time, const LogLevel& logLevel, const std::string& message, const std::string& category );
/** Copy Constructor */
	LogMessage( const LogMessage& rhs );
/** Move Constructor */
	LogMessage( LogMessage&& rhs );
/** Copy operator */
	LogMessage& operator=( const LogMessage& rhs );
/** Move operator */
	LogMessage& operator=( LogMessage&& rhs );
/** Equals operator */
	int operator==( const LogMessage& rhs ) const;
/** Lesser than operator */
	int operator<( const LogMessage& rhs ) const;
/** Liefert INDEX */
	unsigned long GetIndex() const;
/** Liefert Meldung */
	const std::string& GetMessage() const;
/** Liefert Kategorie */
	const std::string& GetCategory() const;
/** Liefert LogLevel */
	const LogLevel& GetLogLevel() const;
/** Liefert Zeitpunkt */
	const Time& GetLogTime() const;
private:
/** Default constructor restricted */
	LogMessage();
private:
	unsigned long 		m_Index;
	Time				m_Time;
	const LogLevel		*m_LogLevel;
	std::string			m_Message;
	std::string			m_Category;
};

}