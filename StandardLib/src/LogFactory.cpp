#include "stdafx.h"
#include "LogFactory.h"
#include "LogManager.h"
#include "LogManagerThread.h"
#include "LoggerCout.h"
#include "LogInterface.h"

namespace jha
{

LogManager* LogFactory::m_LogManager = nullptr;
BaseThread* LogFactory::m_LogManagerThread = nullptr;

void LogFactory::CleanUp()
{
	if( m_LogManagerThread != nullptr )
	{
		m_LogManagerThread->Stop();
	}
	delete m_LogManagerThread;
	m_LogManagerThread = nullptr;
	
	delete m_LogManager;
	m_LogManager = nullptr;
}

LogManager* LogFactory::GetLogManager()
{
	return m_LogManager;
}

bool LogFactory::Init()
{
	if( m_LogManagerThread == nullptr )
	{
		m_LogManager = new LogManager;
		m_LogManager->RegisterLogger( new LoggerCout );
		m_LogManagerThread = new LogManagerThread(m_LogManager);
		m_LogManagerThread->Start();
	}
	return true;
}

}