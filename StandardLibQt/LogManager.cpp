#include "stdafx.h"
#include "LogManager.h"
#include "LogMessage.h"
#include "Logger.h"

namespace jha
{

LogManager::LogManager()
	: LogMessageIndex(0),
	LogMessagesProcessing(nullptr),
	LogMessagesReady(nullptr),
	InitialLogmessage(nullptr)
{
	LogMessagesProcessing = new QVector<LogMessage*>;
	LogMessagesReady = new QVector<LogMessage*>;
	StartingDay = QDate::currentDate().day();
}

LogManager::~LogManager()
{
	for( size_t i=0;i<Loggers.size();i++ )
	{
		delete Loggers.at(i);
	}
	Loggers.clear();

	delete LogMessagesProcessing;
	LogMessagesProcessing = nullptr;

	delete LogMessagesReady;
	LogMessagesReady = nullptr;

	delete InitialLogmessage;
}

bool LogManager::RegisterLogger( jha::Logger* logger )
{
	if( logger == nullptr )
	{
		return false;
	}

	int index = Loggers.indexOf(logger);
	if( index != -1 )
	{
		return false;
	}
	if( logger->Init() == false )
	{
		return false;
	}

	Loggers.push_back(logger);
	return true;
}

bool LogManager::ProcessMessages()
{
	bool allMessagesProcessed = true;
	if( CheckReinitLogger() == true )
	{
		ReinitLogger();
		return allMessagesProcessed;
	}
	for( size_t i=0;i<Loggers.size();i++ )
	{
		try
		{
			Loggers.at(i)->LogMessage( *LogMessagesProcessing );
		}
		catch (...)
		{
			allMessagesProcessed = false;
		}
	}
	ClearLogMessages();
	FlipMessageVectors();
	return allMessagesProcessed;
}

void LogManager::AddLogMessage( jha::LogMessage *logMessage )
{
	QMutexLocker lock(&Mutex);
	if( LogMessageIndex == 0 )
	{
		InjectInitialLogMessage();
	}
	logMessage->SetLogIndex(CreateLogMessageIndex());
	LogMessagesReady->push_back(logMessage);
}

unsigned long LogManager::CreateLogMessageIndex()
{
	return ++LogMessageIndex;
}

void LogManager::ClearLogMessages()
{
	for( size_t i=0;i<LogMessagesProcessing->size();i++ )
	{
		delete LogMessagesProcessing->at(i);
	}
	LogMessagesProcessing->clear();
}

void LogManager::FlipMessageVectors()
{
	QMutexLocker lock(&Mutex);
	QVector<LogMessage*> *temp = LogMessagesProcessing;
	LogMessagesProcessing = LogMessagesReady;
	LogMessagesReady = temp;
}

bool LogManager::CheckReinitLogger() const
{
	int currentDay = QDate::currentDate().day();
	if( currentDay == StartingDay )
	{
		return false;
	}
	StartingDay = currentDay;
	return true;
}

void LogManager::ReinitLogger()
{
	QVector<jha::Logger*>::iterator logger = Loggers.begin();
	for( logger; logger != Loggers.end(); logger++ )
	{
		(*logger)->Init();
	}
}

void LogManager::WorkMessages()
{
	ProcessMessages();
	emit Finished();
}

void LogManager::InjectInitialLogMessage()
{
	QString initialLogMessage("#################### START LOGGING ####################");
	InitialLogmessage = new LogMessage(QTime::currentTime(),LogInterface::LOGLEVEL_INIT,initialLogMessage,QCoreApplication::applicationName());
	InitialLogmessage->SetLogIndex(0);
	LogMessagesReady->push_back(InitialLogmessage);
}

void LogManager::SetGlobalLogLevel( jha::LogLevel logLevel )
{
	QMutexLocker lock(&Mutex);
	for(auto it = std::begin(Loggers); it != std::end(Loggers); ++it) 
	{
		(*it)->SetLogLevel(logLevel);
	}
}

}