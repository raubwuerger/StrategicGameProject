#pragma once
#include <QVector>
#include <QString>

#include "LogLevel.h"

namespace jha
{
class LogMessage;

class Logger
{
public:
	static const QString DEFAULT_TIME_FORMAT;
	static const QString DEFAULT_DATE_FORMAT;
public:
/** Konstruktor */
	Logger( const QString& name );
/** */
	virtual bool Init() = 0;
/** */
	bool LogMessage( const QVector<jha::LogMessage*>& logMessage );
/** */
	const QString& Name() const;
/** */
	bool GetEnabled() const;
	/** */
	void SetEnabled( bool enable );
protected:
/** */
	QString CreateDefaultLogString( jha::LogMessage *message ) const;
/** */
	bool LogThisLogLevel( jha::LogMessage *message ) const;
private:
	/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage ) = 0;
private:
	QString	m_Name;
	bool	m_Enabled;
	LogLevel m_LogLevel;
};

}