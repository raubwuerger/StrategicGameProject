#pragma once

#include <vector>
#include "LogLevel.h"

namespace jha
{

class LogMessage;
class Logger;

/** LogManager, Singleton */
class LoggingWorker : public QObject
{
	Q_OBJECT
public:
/** Konstructor */
	explicit LoggingWorker( QObject* parent = nullptr );
/** Destructor */
	~LoggingWorker();
public slots:
/** Registriert einen neuen Logger. �bernimmt Besitz! */
	bool RegisterLogger( jha::Logger* logger );
/** F�gt LogMessage ein */
	void AddLogMessage( jha::LogMessage *logMessage );
/** */
	void SetGlobalLogLevel( jha::LogLevel logLevel );
/** */
	void Start();
/** */
	void Stop();
signals:
/** */
	void Finished();
/** */
	void Stopped();
/** */
	void Started();
protected:
	friend class LogManagerThread;
	/** Startet abarbeitung der aufgelaufenen Meldungen */
	void WorkMessages();
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
/** */
	unsigned long CreateLogMessageIndex();
/** */
	void InjectInitialLogMessage();
private:
	QVector<Logger*>		Loggers;
	QVector<LogMessage*>	*LogMessagesProcessing;
	QVector<LogMessage*>	*LogMessagesReady;
	LogMessage*				InitialLogmessage;
	unsigned long			LogMessageIndex;
	mutable int				StartingDay;
	volatile bool			IsRunning;
	volatile bool			IsStopping;
	QMutex Mutex;
};

}
