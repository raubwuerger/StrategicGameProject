#include "stdafx.h"
#include "LogInterface.h"
#include "LogLevel.h"
#include "LogFactory.h"
#include "LoggingWorker.h"
#include "LogMessage.h"
#include "LogManagerThread.h"
#include <QTime>
#include <iostream>

namespace jha
{

	QString LogCategoryDefault::CATEGORY = QCoreApplication::applicationName();
	LogInterface* LogInterface::Instance = nullptr;
	LoggingWorker* LogInterface::LogManagerInstance = nullptr;
	LogCategoryVisitor* jha::LogInterface::LogInterfaceVisitor = nullptr;

	const LogLevel LogInterface::LOGLEVEL_NONE("None","n",Qt::cyan,LOGLEVEL::LL_NONE);
	const LogLevel LogInterface::LOGLEVEL_FATAL("Fatal","f",Qt::magenta,LOGLEVEL::LL_FATAL);
	const LogLevel LogInterface::LOGLEVEL_ERROR("Error","e",Qt::red,LOGLEVEL::LL_ERROR);
	const LogLevel LogInterface::LOGLEVEL_WARNING("Warning","w",QColor(255,150,40),LOGLEVEL::LL_WARNING);
	const LogLevel LogInterface::LOGLEVEL_MESSAGE("Message","m",Qt::darkGreen,LOGLEVEL::LL_MESSAGE);
	const LogLevel LogInterface::LOGLEVEL_INFO("Info","i",Qt::blue,LOGLEVEL::LL_INFO);
	const LogLevel LogInterface::LOGLEVEL_TRACE("Trace","t",Qt::black,LOGLEVEL::LL_TRACE);
	const LogLevel LogInterface::LOGLEVEL_DEBUG("Debug","d",Qt::darkGray,LOGLEVEL::LL_DEBUG);
	const LogLevel LogInterface::LOGLEVEL_INIT("Init","s",Qt::darkRed,LOGLEVEL::LL_INIT);

	LogLevel logLevelArray[8] = { 
		LogInterface::LOGLEVEL_NONE, 
		LogInterface::LOGLEVEL_FATAL,
		LogInterface::LOGLEVEL_ERROR,
		LogInterface::LOGLEVEL_WARNING,
		LogInterface::LOGLEVEL_MESSAGE,
		LogInterface::LOGLEVEL_INFO,
		LogInterface::LOGLEVEL_TRACE,
		LogInterface::LOGLEVEL_DEBUG};

	//==============================================================================
	LogInterface* LogInterface::GetInstance()
	{
		//TODO: Diese Funktion k�nnte gleichzeitig aufgerufen werden! Durch Semaphore absichern!
		if( Instance != nullptr )
		{
			return Instance;
		}
			
		Instance = new LogInterface;

		return Instance;
	}

	//==============================================================================
	bool LogInterface::Init()
	{
		if( nullptr == LogManagerInstance )
		{
			std::cout << "Internal error! LogManagerInstance is null!" << endl;
			return false;
		}
		if( LogInterfaceVisitor == nullptr )
		{
			LogInterfaceVisitor = new LogCategoryVisitor;
			LogCategoryDefault().SetCategory( QCoreApplication::applicationName() );
		}
		connect( this, SIGNAL(PostLogMessage(jha::LogMessage *)), LogManagerInstance, SLOT(AddLogMessage( jha::LogMessage *)) );
		QString message("Starting ");
		message += QCoreApplication::applicationName();
		message += ", version=";
		message += 	QCoreApplication::applicationVersion();
		Log( message, jha::LOGLEVEL::LL_MESSAGE);
		return true;
	}

	//==============================================================================
	void LogInterface::Release()
	{
		delete LogInterfaceVisitor;
		LogInterfaceVisitor = nullptr;

		delete Instance;
		Instance = nullptr;
	}

	//==============================================================================
	LogInterface::LogInterface()
	{
	}

	//==============================================================================
	void LogInterface::Log( const QString& message, jha::LOGLEVEL logLevel, const QString& category )
	{
		LogManagerInstance->AddLogMessage( new jha::LogMessage( QTime::currentTime(), logLevelArray[static_cast<int>(logLevel)], message, category ) );
	}

	//==============================================================================
	void LogInterface::Log( const QString& message, jha::LOGLEVEL logLevel, const LogCategoryInterface& logCategory )
	{
		QString category = "-";
		if( LogInterfaceVisitor != nullptr )
		{
			category = LogInterfaceVisitor->GetCategory( &logCategory );
		}
		LogManagerInstance->AddLogMessage( new jha::LogMessage( QTime::currentTime(), logLevelArray[static_cast<int>(logLevel)], message, category ) );
	}

	//==============================================================================
	void LogInterface::Log_NONE(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_NONE, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_FATAL(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_FATAL, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_ERROR(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_ERROR, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_WARNING(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_WARNING, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_MESSAGE(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_MESSAGE, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_INFO(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_INFO, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_TRACE(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_TRACE, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_DEBUG(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_DEBUG, logCategory );
	}

	//==============================================================================
	void LogInterface::Log_INIT(const QString& message, const LogCategoryInterface& logCategory /*= LogCategoryDefault() */)
	{
		Log( message, jha::LOGLEVEL::LL_INIT, logCategory );
	}

	//==============================================================================
	void LogInterface::SetGlobalLoglevel( LogLevel logLevel )
	{
		LogManagerInstance->SetGlobalLogLevel(logLevel);
	}

	//==============================================================================
	void LogInterface::SetGlobalLoglevel( const QString& logLevel )
	{
		LogManagerInstance->SetGlobalLogLevel( GetLogLevelFromName(logLevel) );
	}

	//==============================================================================
	jha::LogLevel LogInterface::GetLogLevelFromName( const QString& logLevel ) const
	{
		const int EQUALS = 0;
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_NONE.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_NONE;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_FATAL.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_FATAL;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_ERROR.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_ERROR;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_WARNING.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_WARNING;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_MESSAGE.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_MESSAGE;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_INFO.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_INFO;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_TRACE.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_TRACE;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_DEBUG.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_DEBUG;
		}
		if( EQUALS == QString::compare(logLevel, jha::LogInterface::LOGLEVEL_INIT.GetName(), Qt::CaseInsensitive) )
		{
			return jha::LogInterface::LOGLEVEL_INIT;
		}

		Q_ASSERT(nullptr);
		return jha::LogInterface::LOGLEVEL_DEBUG;
	}

	//==============================================================================
	LogInterface* GetLog()
	{
		return LogInterface::GetInstance();
	}

}