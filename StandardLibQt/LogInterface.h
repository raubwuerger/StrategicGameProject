#pragma once
#include <QString>

namespace jha
{

class LogLevel;
class Logger;
class LogMessage;

class LogCategoryInterface
{
public:
/** */
	LogCategoryInterface(){}
/** */
	virtual QString GetCategory() const = 0;
};

class LogCategoryByName : public LogCategoryInterface
{
public:
/** */
	LogCategoryByName( const QString& name )
		: Name(name)
	{

	}
/** */
	virtual QString GetCategory() const
	{
		return Name;
	}
private:
	QString Name;
};

class LogCategoryDefault : public LogCategoryInterface
{
public:
/** */
	LogCategoryDefault(){}
/** */
	virtual QString GetCategory() const
	{
		return CATEGORY;
	}
/** */
	void SetCategory( const QString& category )
	{
		CATEGORY = category;
	}
private:
	static QString CATEGORY;
};

class LogCategoryVisitor
{
public:
	/** */
	LogCategoryVisitor() {}
	/** */
	QString GetCategory( const LogCategoryInterface *category ) 
	{
		return category->GetCategory();
	}
};

enum class LOGLEVEL
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

class LogInterface : public QObject
{
	Q_OBJECT
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
	void Log( const QString& message, LOGLEVEL logLevel, const QString& category );
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, LOGLEVEL logLevel, const LogCategoryInterface& logCategory = LogCategoryDefault() );
/** Registriert einen speziellen Logger */
	bool RegisterLogger( Logger* logger );
/** */
	const QString& GetLogLevelString( LOGLEVEL logLevel ) const;
/** */
	const LogLevel& GetLogLevel( LOGLEVEL logLevel ) const;
/** */
	void SetLogInterfaceVisitor( LogCategoryVisitor * obj );
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
	static const LogLevel LOGLEVEL_NONE;
	static const LogLevel LOGLEVEL_FATAL;
	static const LogLevel LOGLEVEL_ERROR;
	static const LogLevel LOGLEVEL_WARNING;
	static const LogLevel LOGLEVEL_MESSAGE;
	static const LogLevel LOGLEVEL_INFO;
	static const LogLevel LOGLEVEL_TRACE;
	static const LogLevel LOGLEVEL_DEBUG;
	static LogInterface *log;
	static LogCategoryVisitor	*LogInterfaceVisitor;
};

LogInterface* GetLog();

}

typedef jha::LOGLEVEL LEVEL;