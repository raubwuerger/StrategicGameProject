#include "stdafx.h"
#include "LogInterface.h"
#include "LogLevel.h"
#include "LogFactory.h"
#include "LogManager.h"
#include "LogMessage.h"
#include "LogManagerThread.h"
#include <QTime>

namespace jha
{

QString LogCategoryDefault::CATEGORY = QCoreApplication::applicationName();

LogInterface* LogInterface::log = nullptr;


LogInterface* GetLog()
{
	return LogInterface::log;
}

const LogLevel LogInterface::LOGLEVEL_NONE("None","n",Qt::cyan,LOGLEVEL::LL_NONE);
const LogLevel LogInterface::LOGLEVEL_FATAL("Fatal","f",Qt::magenta,LOGLEVEL::LL_FATAL);
const LogLevel LogInterface::LOGLEVEL_ERROR("Error","e",Qt::red,LOGLEVEL::LL_ERROR);
const LogLevel LogInterface::LOGLEVEL_WARNING("Warning","w",QColor(255,150,40),LOGLEVEL::LL_WARNING);
const LogLevel LogInterface::LOGLEVEL_MESSAGE("Message","m",Qt::darkGreen,LOGLEVEL::LL_MESSAGE);
const LogLevel LogInterface::LOGLEVEL_INFO("Info","i",Qt::blue,LOGLEVEL::LL_INFO);
const LogLevel LogInterface::LOGLEVEL_TRACE("Trace","t",Qt::black,LOGLEVEL::LL_TRACE);
const LogLevel LogInterface::LOGLEVEL_DEBUG("Debug","d",Qt::darkGray,LOGLEVEL::LL_DEBUG);

LogLevel logLevelArray[8] = { LogInterface::LOGLEVEL_NONE, 
								LogInterface::LOGLEVEL_FATAL,
								LogInterface::LOGLEVEL_ERROR,
								LogInterface::LOGLEVEL_WARNING,
								LogInterface::LOGLEVEL_MESSAGE,
								LogInterface::LOGLEVEL_INFO,
								LogInterface::LOGLEVEL_TRACE,
								LogInterface::LOGLEVEL_DEBUG};

LogCategoryVisitor* jha::LogInterface::LogInterfaceVisitor = nullptr;

LogInterface::LogInterface()
{
}

void LogInterface::Log( const QString& message, LOGLEVEL logLevel, const QString& category )
{
	LogFactory().GetLogManager()->AddLogMessage( new LogMessage( LogFactory().GetLogManager()->CreateLogMessageIndex(), QTime::currentTime(), GetLogLevel(logLevel), message, category ) );
}

void LogInterface::Log( const QString& message, LOGLEVEL logLevel, const LogCategoryInterface& logCategory )
{
	QString category = "-";
	if( LogInterfaceVisitor != nullptr )
	{
		category = LogInterfaceVisitor->GetCategory( &logCategory );
	}
	LogFactory().GetLogManager()->AddLogMessage( new LogMessage( LogFactory().GetLogManager()->CreateLogMessageIndex(), QTime::currentTime(), GetLogLevel(logLevel), message, category ) );
}

bool LogInterface::RegisterLogger( Logger* logger )
{
	return LogFactory().GetLogManager()->RegisterLogger(logger);
}

bool LogInterface::Init()
{
	try
	{
		if( log == nullptr )
		{
			log = new LogInterface;
		}
		if( LogInterfaceVisitor == nullptr )
		{
			LogInterfaceVisitor = new LogCategoryVisitor;
			LogCategoryDefault().SetCategory( QCoreApplication::applicationName() );
		}
		LogFactory().Init();
		connect( this, SIGNAL(PostLogMessage(jha::LogMessage *)), LogFactory().GetLogManager(), SLOT(AddLogMessage( jha::LogMessage *)) );
		QString message("Starting ");
		message += QCoreApplication::applicationName();
		message += ", version=";
		message += 	QCoreApplication::applicationVersion();
		Log( message, jha::LOGLEVEL::LL_MESSAGE);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool LogInterface::CleanUp()
{
	delete LogInterfaceVisitor;
	LogInterfaceVisitor = nullptr;

	delete log;
	log = nullptr;

	LogFactory().CleanUp();
	return true;
}

void LogInterface::Start()
{
	if( LogFactory::LogManagerThread == nullptr )
	{
		return;
	}
	LogFactory::LogManagerThread->Start();
}

const QString& LogInterface::GetLogLevelString( LOGLEVEL logLevel ) const
{
	return logLevelArray[static_cast<int>(logLevel)].GetName();
}

const LogLevel& LogInterface::GetLogLevel( LOGLEVEL logLevel ) const
{
	return logLevelArray[static_cast<int>(logLevel)];
}

void LogInterface::SetLogInterfaceVisitor( LogCategoryVisitor * obj )
{
	delete LogInterfaceVisitor;
	LogInterfaceVisitor = obj;
}

}