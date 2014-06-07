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
/** Registriert einen neuen Logger. Übernimmt Besitz! */
	bool RegisterLogger( Logger* logger );
/** Fügt LogMessage ein */
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
/** Prüft ob logger neu initialisiert werden müssen. Datumswechsel */
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
