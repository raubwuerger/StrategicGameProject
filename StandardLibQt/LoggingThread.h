#pragma once


#include <QThread>

namespace jha
{

class LoggingWorker;

class LoggingThread : public QObject
{
	Q_OBJECT
public:
/** Constructor */
	LoggingThread( LoggingWorker *logManager );
/** Destructor */
	~LoggingThread();
/** */
	bool Init();
/** */
	void Start();
/** */
	void Stop();
/** */
	bool GetIsRunning() const;
public slots:
/** */
	void HasFinished();
/** */
	void RequestStartFromTimer();
signals:
/** */
	void StartLogManager();
private:
	LoggingWorker* LogManagerObject;
	QThread		WorkerThread;
	QTimer		*Timer;
	bool		LogManagerRunning;
};

}