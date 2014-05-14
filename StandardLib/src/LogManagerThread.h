#pragma once

#include "BaseThread.h"
#include <string>

namespace jha
{

class LogManager;

class LogManagerThread : public BaseThread
{
public:
/** Constructor */
	LogManagerThread( LogManager *logManager );
/** Destructor */
	~LogManagerThread();
protected:
	/** */
	virtual bool PreRun();
/** */
	virtual bool Run();
private:
	LogManager	*m_LogManager;
};

}