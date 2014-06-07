#pragma once
#include <QString>

namespace jha
{

class LogLevel;
class Logger;
class LogMessage;

class LogInterface : public QObject
{
	Q_OBJECT
public:
	enum LOGLEVEL
	{
		LL_NONE = 0,
		LL_FATAL = 1,
		LL_ERROR = 2,
		LL_WARNING = 3,
		LL_MESSAGE = 4,
		LL_INFO = 5,
		LL_TRACE = 6,
		LL_DEBUG = 7
	};
public:
/** Constructor */
	LogInterface();
/** Initialisiert LogInterface */
	bool Init();
/** */
	bool CleanUp();
/** */
	void Start();
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, LOGLEVEL logLevel, const QString& category = "" );
/** Registriert einen speziellen Logger */
	bool RegisterLogger( Logger* logger );
/** */
	const QString& GetLogLevelString( LOGLEVEL logLevel ) const;
/** */
	const LogLevel& GetLogLevel( LOGLEVEL logLevel ) const;
private:
/** Copy constructor restricted */
	LogInterface( const LogInterface& rhs );
/** Move constructor restricted */
	LogInterface( LogInterface&& rhs );
/** Copy operator restricted */
	LogInterface& operator=( const LogInterface& rhs );
/** Move operator restricted */
	LogInterface& operator==( LogInterface&& rhs );
/** */
signals:
	void PostLogMessage( jha::LogMessage *logMessage );
public:
	static const LogLevel L_NONE;
	static const LogLevel L_FATAL;
	static const LogLevel L_ERROR;
	static const LogLevel L_WARNING;
	static const LogLevel L_MESSAGE;
	static const LogLevel L_INFO;
	static const LogLevel L_TRACE;
	static const LogLevel L_DEBUG;
	static LogInterface *log;
};

LogInterface* GetLog();

}