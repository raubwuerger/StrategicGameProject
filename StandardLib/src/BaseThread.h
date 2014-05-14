#pragma once

#include <concrt.h>
#include <string>

namespace jha
{

class BaseThread
{
public:
/** Constructor */
	BaseThread( const std::string& name = "" );
/** Destructor */
	virtual ~BaseThread();
/** Startet Thread*/
	virtual bool Start( int priority = THREAD_PRIORITY_NORMAL, bool startPaused = false);
/** Stoppt Thread */
	virtual bool Stop(unsigned int timeout=5000);
/** Signal the thread to pause / resume */
	void SetPauseRequest(bool pause);
/** Get state of pause signal */
	bool GetPauseRequest() const;
/** Liefert true wenn der Thread gerade ausgeführt wird */
	bool GetRunning() const;
/** Liefert true wenn Thread nicht mehr aktiv ist */
	bool IsActive() const;
/** Setzt Prioritylevel des Threads */
	int SetPriority(int nPrio);
/** Liefert m_LiveCounter */
	size_t GetLiveCounter() const;
/** Liefert m_Name */
	const std::string& GetName() const;
/** Liefert m_ThreadId */
	int GetThreadId() const;
/** Setzt m_CycleTimeMS */
	void SetCycleTimeMS(int obj);
/** Liefert m_CycleTimeMS */
	int GetCycleTimeMS() const;
protected:
/** */
	virtual bool Run() = 0;
/** */
	virtual bool Pause();
/** */
	virtual bool PreRun();
/** */
	virtual bool PostRun();
/** */
	virtual bool EnteringPause();
/** */
	virtual bool LeavingPause();
protected:
/** set the run-state */
	virtual void SetIsRunning(bool state);
/** set the pause-state */
	virtual void SetIsPaused(bool state);
	mutable Concurrency::critical_section m_CriticalSection;
private:
/** Eigentlich Thread-Funktion */
	static UINT StaticThreadFunc(LPVOID pParam);
/** Verarbeitet (Translate/Dispatch) anstehende Meldungen */
	void ProcessPendingMessages();
/** Copy constructor restricted */
	BaseThread( const BaseThread& rhs );
/** Move constructor restricted */
	BaseThread( BaseThread&& rhs );
/** Copy operator */
	BaseThread& operator=( const BaseThread& rhs );
/** Move operator */
	BaseThread& operator=( BaseThread&& rhs );
private:
	HANDLE		m_ThreadHandle;
	bool		m_RunRequested;
	bool		m_PauseRequested;
	bool		m_Running;
	bool		m_Pause;
	std::string	m_Name;
	int			m_CycleTimeMS;
	int			m_ThreadId;
};

}