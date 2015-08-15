#pragma once
#include <QString>
#include <QTime>
#include "LogLevel.h"

namespace jha
{

class LogMessage
{
public:
/** Constructor */
	LogMessage( const unsigned long index, const QTime& time, const LogLevel& logLevel, const QString& message, const QString& category );
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
	const QString& GetMessage() const;
/** Liefert Kategorie */
	const QString& GetCategory() const;
/** Liefert LogLevel */
	const LogLevel& GetLogLevel() const;
/** Liefert Zeitpunkt */
	const QTime& GetLogTime() const;
private:
/** Default constructor restricted */
	LogMessage();
private:
	unsigned long 		m_Index;
	QTime				m_Time;
	const LogLevel		*m_LogLevel;
	QString			m_Message;
	QString			m_Category;
};

}