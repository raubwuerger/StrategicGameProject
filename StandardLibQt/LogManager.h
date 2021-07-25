#pragma once

#include <vector>

namespace jha
{

class LogMessage;
class Logger;

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
	bool RegisterLogger( jha::Logger* logger );
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
	QVector<Logger*>	Logger;
	QVector<LogMessage*>	*LogMessagesProcessing;
	QVector<LogMessage*>	*LogMessagesReady;
	unsigned long LogMessageIndex;
	QMutex Mutex;
};

}
