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

LogInterface* LogInterface::log = nullptr;


LogInterface* GetLog()
{
	return LogInterface::log;
}

const LogLevel LogInterface::L_NONE("None","n",Qt::cyan);
const LogLevel LogInterface::L_FATAL("Fatal","f",Qt::magenta);
const LogLevel LogInterface::L_ERROR("Error","e",Qt::red);;
const LogLevel LogInterface::L_WARNING("Warning","w",QColor(255,150,40));
const LogLevel LogInterface::L_MESSAGE("Message","m",Qt::darkGreen);
const LogLevel LogInterface::L_INFO("Info","i",Qt::blue);
const LogLevel LogInterface::L_TRACE("Trace","t",Qt::black);
const LogLevel LogInterface::L_DEBUG("Debug","d",Qt::darkGray);

LogLevel logLevelArray[8] = { LogInterface::L_NONE, 
								LogInterface::L_FATAL,
								LogInterface::L_ERROR,
								LogInterface::L_WARNING,
								LogInterface::L_MESSAGE,
								LogInterface::L_INFO,
								LogInterface::L_TRACE,
								LogInterface::L_DEBUG};

LogInterface::LogInterface()
{
}

void LogInterface::Log( const QString& message, LOGLEVEL logLevel, const QString& category )
{
	LogFactory().GetLogManager()->AddLogMessage( new LogMessage( LogFactory().GetLogManager()->CreateLogMessageIndex(), QTime::currentTime(), GetLogLevel(logLevel), message, category ) );
//	emit PostLogMessage( new LogMessage( LogFactory().GetLogManager()->CreateLogMessageIndex(), QTime::currentTime(), GetLogLevel(logLevel), message, category ) );
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
		LogFactory().Init();
		connect( this, SIGNAL(PostLogMessage(jha::LogMessage *)), LogFactory().GetLogManager(), SLOT(AddLogMessage( jha::LogMessage *)) );
		QString message("Starting ");
		message += QCoreApplication::applicationName();
		message += ", version=";
		message += 	QCoreApplication::applicationVersion();
		Log( message, jha::LogInterface::LL_MESSAGE);
		//connect(m_View->m_Scene, SIGNAL(SignalProvinceEntered(const ProvinceItem*)),this, SLOT(UpdateProvinceDetail(const ProvinceItem*)));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool LogInterface::CleanUp()
{
	delete log;
	log = nullptr;

	LogFactory().CleanUp();
	return true;
}

void LogInterface::Start()
{
	if( LogFactory::m_LogManagerThread == nullptr )
	{
		return;
	}
	LogFactory::m_LogManagerThread->Start();
}

const QString& LogInterface::GetLogLevelString( LOGLEVEL logLevel ) const
{
	return logLevelArray[logLevel].GetName();
}

const LogLevel& LogInterface::GetLogLevel( LOGLEVEL logLevel ) const
{
	return logLevelArray[logLevel];
}

}