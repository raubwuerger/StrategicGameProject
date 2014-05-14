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
/** Registriert einen neuen Logger. Übernimmt Besitz! */
	bool RegisterLogger( Logger* logger );
/** Fügt LogMessage ein */
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
/** Prüft ob logger neu initialisiert werden müssen. Datumswechsel */
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
