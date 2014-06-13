#pragma once

#include <QString>
#include <QColor>

//TODO: enums in eigene HEader auslagern, dann kann das hier entfallen
#include "LogInterface.h"

namespace jha
{

class LogLevel
{
public:
/** Konstruktor */
	LogLevel( const LogLevel& rhs );
/** Copy operator */
	LogLevel& operator=( const LogLevel& rhs );
/** Move operator */
	LogLevel& operator=( LogLevel&& rhs );
/** Destructor */
	~LogLevel();
/** Equals operator */
	int operator==( const LogLevel& rhs ) const;
/** Lesser than operator */
	int operator<( const LogLevel& rhs ) const;
/** Liefert Namen */
	const QString& GetName() const;
/** Liefert LogFilePrefix */
	const QString& GetLogFilePrefix() const;
/** Liefert MessageBoxType */
//	UINT GetMessageBoxType() const;
/** Liefert Farbe */
	const QColor& GetColor() const;
/** */
	LOGLEVEL GetValue() const { return m_Value; }
private:
	friend class LogInterface;
/** Default constructor restricted */
	LogLevel();
/** Move Konstruktor restricted */
	LogLevel( LogLevel&& rhs );
/** */
	LogLevel( const QString& name, const QString& prefix, /*UINT messageBoxType,*/ const QColor& color, LOGLEVEL value );
private:
	QString		m_Name;
	QString		m_LogFilePrefix;
	QColor		m_Color;
	LOGLEVEL	m_Value;
};

}