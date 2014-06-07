#include "stdafx.h"
#include "LogManager.h"
#include "LogMessage.h"
#include "Logger.h"

namespace jha
{

LogManager::LogManager()
	: m_LogMessageIndex(0),
	m_LogMessagesProcessing(nullptr),
	m_LogMessagesReady(nullptr)
{
	m_LogMessagesProcessing = new QVector<LogMessage*>;
	m_LogMessagesReady = new QVector<LogMessage*>;
}

LogManager::~LogManager()
{
	for( size_t i=0;i<m_Logger.size();i++ )
	{
		delete m_Logger.at(i);
	}
	m_Logger.clear();
	delete m_LogMessagesProcessing;
	m_LogMessagesProcessing = nullptr;
	delete m_LogMessagesReady;
	m_LogMessagesReady = nullptr;
}

bool LogManager::RegisterLogger( Logger* logger )
{
	if( logger == nullptr )
	{
		return false;
	}

	int index = m_Logger.indexOf(logger);
	if( index != -1 )
	{
		return false;
	}
	if( logger->Init() == false )
	{
		return false;
	}

	m_Logger.push_back(logger);
	return true;
}

bool LogManager::ProcessMessages()
{
	if( CheckReinitLogger() == true )
	{
		ReinitLogger();
	}
	bool allMessagesProcessed = true;
	for( size_t i=0;i<m_Logger.size();i++ )
	{
		try
		{
			m_Logger.at(i)->LogMessage( *m_LogMessagesProcessing );
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
	QMutexLocker lock(&m_Mutex);
	m_LogMessagesReady->push_back(logMessage);
}

unsigned long LogManager::CreateLogMessageIndex()
{
	return ++m_LogMessageIndex;
}

void LogManager::ClearLogMessages()
{
	for( size_t i=0;i<m_LogMessagesProcessing->size();i++ )
	{
		delete m_LogMessagesProcessing->at(i);
	}
	m_LogMessagesProcessing->clear();
}

void LogManager::FlipMessageVectors()
{
	QMutexLocker lock(&m_Mutex);
	QVector<LogMessage*> *temp = m_LogMessagesProcessing;
	m_LogMessagesProcessing = m_LogMessagesReady;
	m_LogMessagesReady = temp;
}

bool LogManager::CheckReinitLogger() const
{
	//TODO: Datumswechsel prüfen
	return false;
}

void LogManager::ReinitLogger()
{
	QVector<Logger*>::iterator logger = m_Logger.begin();
	for( logger; logger != m_Logger.end(); logger++ )
	{
		(*logger)->Init();
	}
}

void LogManager::WorkMessages()
{
	ProcessMessages();
	emit Finished();
}

}