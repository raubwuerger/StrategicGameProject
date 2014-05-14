#include "stdafx.h"
#include "LogManagerThread.h"
#include "LogManager.h"
#include "LogFactory.h"
#include "LogInterface.h"

namespace jha
{

LogManagerThread::LogManagerThread( LogManager *logManager )
	:	BaseThread("LogManagerThread"),
	m_LogManager(logManager)
{
}

LogManagerThread::~LogManagerThread()
{

}

bool LogManagerThread::Run()
{
	if( m_LogManager == nullptr )
	{
		return false;
	}
	try
	{
		return m_LogManager->ProcessMessages();
	}
	catch (CMemoryException* e)
	{
		return false;		
	}
	catch (CFileException* e)
	{
		return false;		
	}
	catch (CException* e)
	{
		return false;		
	}
}

bool LogManagerThread::PreRun()
{
	jha::log->Log("LogManagerThread started",LogInterface::LL_INFO, "" );
	return true;
}

}