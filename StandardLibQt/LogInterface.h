#pragma once
#include <QString>

namespace jha
{

class LogLevel;
class Logger;
class LogMessage;
class LogManager;

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
	LL_INIT = -1,
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
	static const LogLevel LOGLEVEL_NONE;
	static const LogLevel LOGLEVEL_FATAL;
	static const LogLevel LOGLEVEL_ERROR;
	static const LogLevel LOGLEVEL_WARNING;
	static const LogLevel LOGLEVEL_MESSAGE;
	static const LogLevel LOGLEVEL_INFO;
	static const LogLevel LOGLEVEL_TRACE;
	static const LogLevel LOGLEVEL_DEBUG;
	static const LogLevel LOGLEVEL_INIT;
public:
/** */
	static LogInterface* GetInstance();
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, jha::LOGLEVEL logLevel, const QString& category );
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, jha::LOGLEVEL logLevel, const LogCategoryInterface& logCategory = LogCategoryDefault() );
/** Nimmt eine Logmeldung mit Loglevel NONE auf */
	void Log_NONE( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel FATAL auf */
	void Log_FATAL( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel ERROR auf */
	void Log_ERROR( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel WARNING auf */
	void Log_WARNING( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel MESSAGE auf */
	void Log_MESSAGE( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel INFO auf */
	void Log_INFO( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel TRACE auf */
	void Log_TRACE( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel DEBUG auf */
	void Log_DEBUG( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Nimmt eine Logmeldung mit Loglevel INIT auf */
	void Log_INIT( const QString& message, const LogCategoryInterface& logCategory = LogCategoryDefault() );
	/** Setzt Globales Loglevel */
	void SetGlobalLoglevel( LogLevel logLevel );
	/** Setzt Globales Loglevel */
	void SetGlobalLoglevel( const QString& logLevel );
private:
/** Initialisiert LogInterface */
	bool Init();
/** */
	void Release();
/** Constructor */
	LogInterface();
/** Copy constructor restricted */
	LogInterface( const LogInterface& rhs );
/** Move constructor restricted */
	LogInterface( LogInterface&& rhs );
/** Copy operator restricted */
	LogInterface& operator=( const LogInterface& rhs );
/** Move operator restricted */
	LogInterface& operator==( LogInterface&& rhs );
/** */
	LogLevel GetLogLevelFromName( const QString& logLevel ) const;
signals:
	void PostLogMessage( jha::LogMessage *logMessage );
private:
	friend class LogFactory;
	static LogInterface*		Instance;
	static LogManager*			LogManagerInstance;
	static LogCategoryVisitor*	LogInterfaceVisitor;
};

LogInterface* GetLog();

}

typedef jha::LOGLEVEL LEVEL;