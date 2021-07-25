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
	LogMessage( const QTime& time, const LogLevel& logLevel, const QString& message, const QString& category );
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
/** */
	void SetLogIndex( const unsigned long index );
private:
/** Default constructor restricted */
	LogMessage();
/** Constructor */
	LogMessage( const unsigned long index, const QTime& time, const LogLevel& logLevel, const QString& message, const QString& category );
private:
	unsigned long 		Index;
	QTime				Time;
	const LogLevel		*LogLevel;
	QString				Message;
	QString				Category;
};

}