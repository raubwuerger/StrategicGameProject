#pragma once

#include <vector>
#include "concrt.h"

namespace jha
{
class LogMessage;
class Logger;
class LogMessage;

/** LogManager, Singleton */
class LogManager
{
public:
/** Konstructor */
	LogManager();
/** Destructor */
	~LogManager();
/** Registriert einen neuen Logger. �bernimmt Besitz! */
	bool RegisterLogger( Logger* logger );
/** F�gt LogMessage ein */
	void AddLogMessage( LogMessage *logMessage );
/** */
	unsigned long CreateLogMessageIndex();
protected:
	friend class LogManagerThread;
/** Verarbeitet Meldungen */
	bool ProcessMessages();
/** */
	void ClearLogMessages();
/** */
	void FlipMessageVectors();
private:
/** Pr�ft ob logger neu initialisiert werden m�ssen. Datumswechsel */
	bool CheckReinitLogger() const;
/** */
	void ReinitLogger();
private:
	std::vector<Logger*>	m_Logger;
	std::vector<LogMessage*>	*m_LogMessagesProcessing;
	std::vector<LogMessage*>	*m_LogMessagesReady;
	unsigned long m_LogMessageIndex;
	Concurrency::critical_section	m_CriticalSection;
};

}
