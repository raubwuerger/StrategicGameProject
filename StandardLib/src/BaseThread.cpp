#include "stdafx.h"
#include "BaseThread.h"

namespace jha
{

BaseThread::BaseThread(const std::string& name)
	:	m_RunRequested(false),
	m_Running(false),
	m_PauseRequested(false),
	m_Pause(false),
	m_ThreadHandle(0),
	m_Name(name),
	m_CycleTimeMS(0)
{
}

BaseThread::~BaseThread()
{
	Stop();
}

bool BaseThread::Start(int priority /*=THREAD_PRIORITY_NORMAL*/, bool startPaused /*=false*/)
{
	if( m_ThreadHandle != nullptr )
	{
		m_PauseRequested = startPaused;
		return true;
	}

	LPVOID pData = (LPVOID)this;
	m_RunRequested = true;
	CWinThread * winThread = AfxBeginThread(AFX_THREADPROC(StaticThreadFunc), pData, priority, 0, CREATE_SUSPENDED);
	if(winThread == NULL)
	{
		//gLog(LOG_ERROR) << "Failed to create thread" << endl;
		Stop();
		return false;
	}
	HANDLE hSourceProcess = ::GetCurrentProcess();
	if( !::DuplicateHandle(hSourceProcess, winThread->m_hThread, hSourceProcess, &m_ThreadHandle, THREAD_ALL_ACCESS, FALSE, 0) )
	{
		//gLog(LOG_ERROR) << "Handle to thread can not be duplicated!" << endl;
		Stop();
		return false;
	}
	m_ThreadId = winThread->m_nThreadID;
	winThread->ResumeThread();
	return true;
}

bool BaseThread::Stop(unsigned int timeout/*=5000*/)
{
	m_RunRequested = false;
	m_PauseRequested = false;
	if( m_ThreadHandle == nullptr )
	{
		return true;
	}

	DWORD dwExitCode = STILL_ACTIVE;
	// Wait max 60 Seconds to stop the Thread
// 	SARTime::CSARClock clk;
// 	while(clk.Current() < timeout)
// 	{
// 		ProcessPendingMessages();
// 
// 		GetExitCodeThread(m_ThreadHandle, &dwExitCode);
// 		if(dwExitCode != STILL_ACTIVE)
// 		{
// 			break;
// 		}
// 		Sleep(100);
// 	}

	if( dwExitCode == STILL_ACTIVE )
	{
		TerminateThread(m_ThreadHandle, 0);
		//gLog(LOG_ERROR) << "Thread: Terminated hard!" << endl;
		SetIsRunning(false);
	}
	::CloseHandle(m_ThreadHandle);
	m_ThreadHandle = 0;
	m_ThreadId = 0;
	return true;
}

void BaseThread::ProcessPendingMessages()
{
	try
	{
		MSG msg;
		while(PeekMessage( &msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if( msg.message == WM_TIMER )
			{
				continue;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	catch(...)
	{

	}
}

bool BaseThread::IsActive() const
{
	if(m_ThreadHandle != nullptr)
	{
		return true;
	}

	DWORD dwExitCode;
	::GetExitCodeThread(m_ThreadHandle, &dwExitCode);
	return !(dwExitCode == STILL_ACTIVE);
}

void BaseThread::SetPauseRequest(bool pause)
{
	Concurrency::critical_section::scoped_lock lock(m_CriticalSection);
	m_PauseRequested = pause;
}

bool BaseThread::GetPauseRequest() const
{
	Concurrency::critical_section::scoped_lock lock(m_CriticalSection);
	return m_PauseRequested;
}

void BaseThread::SetIsPaused(bool state)
{
	m_Pause = state;
}

void BaseThread::SetIsRunning(bool state)
{
	m_Running = state;
}

UINT BaseThread::StaticThreadFunc(LPVOID pParam)
{
	try
	{
		BaseThread *thread = (BaseThread*)pParam;
		thread->SetIsRunning(true);
		thread->PreRun();

		while( thread->IsActive() )//thread->GetRun())
		{
			if( thread->GetPauseRequest() == true )
			{
				if( thread->GetRunning() == true )
				{
					thread->EnteringPause();
					thread->SetIsPaused(true);
				}
				thread->Pause();
				continue;
			}

			if( thread->GetRunning() == false )
			{
				thread->LeavingPause();
				thread->SetIsPaused(false);
			}
			thread->Run();
		}

		thread->PostRun();
		thread->SetIsRunning(false);
	}
	catch(...)
	{
		Sleep(1000);
	}
	return 0;
}

// Virtual 'inline' functions
bool BaseThread::Pause()
{
	Sleep(10);
	return true;
}

bool BaseThread::PreRun()
{
	return true;
}

bool BaseThread::PostRun()
{
	return true;
}

bool BaseThread::EnteringPause()
{
	return true;
}

bool BaseThread::LeavingPause()
{
	return true;
}

int BaseThread::SetPriority( int nPrio )
{
	return SetThreadPriority(m_ThreadHandle, nPrio);
}

const std::string& BaseThread::GetName() const
{
	return m_Name;
}

int BaseThread::GetThreadId() const
{
	return m_ThreadId;
}

void BaseThread::SetCycleTimeMS( int obj )
{
	m_CycleTimeMS = obj;
}

int BaseThread::GetCycleTimeMS() const
{
	return m_CycleTimeMS;
}

bool BaseThread::GetRunning() const
{
	Concurrency::critical_section::scoped_lock lock(m_CriticalSection);
	return m_Running;
}

}