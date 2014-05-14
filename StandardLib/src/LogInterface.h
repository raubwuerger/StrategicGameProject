#pragma once
#include <string>

namespace jha
{

class LogLevel;
class Logger;

class LogInterface
{
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
/** Nimmt eine Logmeldung auf */
	void Log( const std::string& message, LOGLEVEL logLevel, const std::string& category );
/** Registriert einen speziellen Logger */
	bool RegisterLogger( Logger* logger );
private:
/** Copy constructor restricted */
	LogInterface( const LogInterface& rhs );
/** Move constructor restricted */
	LogInterface( LogInterface&& rhs );
/** Copy operator restricted */
	LogInterface& operator=( const LogInterface& rhs );
/** Move operator restricted */
	LogInterface& operator==( LogInterface&& rhs );
public:
	static const LogLevel L_NONE;
	static const LogLevel L_FATAL;
	static const LogLevel L_ERROR;
	static const LogLevel L_WARNING;
	static const LogLevel L_MESSAGE;
	static const LogLevel L_INFO;
	static const LogLevel L_TRACE;
	static const LogLevel L_DEBUG;
};

namespace
{
	LogInterface *log;
	LogInterface* GetLog();
}


}