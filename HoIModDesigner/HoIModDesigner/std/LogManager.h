#pragma once

#include <vector>
//#include "concrt.h"

namespace jha
{
class LogMessage;
class Logger;
class LogMessage;

/** LogManager, Singleton */
class LogManager : public QObject
{
	Q_OBJECT
public:
/** Konstructor */
	LogManager();
/** Destructor */
	~LogManager();
/** */
	unsigned long CreateLogMessageIndex();
public slots:
/** Startet abarbeitung der aufgelaufenen Meldungen */
	void WorkMessages();
/** Registriert einen neuen Logger. �bernimmt Besitz! */
	bool RegisterLogger( Logger* logger );
/** F�gt LogMessage ein */
	void AddLogMessage( jha::LogMessage *logMessage );
signals:
		void Finished();
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
	QVector<Logger*>	m_Logger;
	QVector<LogMessage*>	*m_LogMessagesProcessing;
	QVector<LogMessage*>	*m_LogMessagesReady;
	unsigned long m_LogMessageIndex;
	QMutex m_Mutex;
};

}
