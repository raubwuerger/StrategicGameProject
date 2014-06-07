#pragma once


#include <QThread>

namespace jha
{

class LogManager;

class LogManagerThreadContainer : public QObject
{
	Q_OBJECT
public:
/** Constructor */
	LogManagerThreadContainer( LogManager *logManager );
/** Destructor */
	~LogManagerThreadContainer();
/** */
	bool Init();
/** */
	void Start();
/** */
	void Stop();
public slots:
	void HasFinished();
/** */
	void RequestStartFromTimer();
signals:
/** */
	void StartLogManager();
private:
	LogManager	*m_LogManager;
	QThread		m_WorkerThread;
	QTimer		*m_Timer;
	bool		m_LogManagerRunning;
};

}