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
public:
/** */
	static LogInterface* GetInstance();
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, jha::LOGLEVEL logLevel, const QString& category );
/** Nimmt eine Logmeldung auf */
	void Log( const QString& message, jha::LOGLEVEL logLevel, const LogCategoryInterface& logCategory = LogCategoryDefault() );
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