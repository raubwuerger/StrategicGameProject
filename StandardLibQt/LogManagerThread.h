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
/** */
	bool GetIsRunning() const { return m_Timer->isActive(); }
public slots:
/** */
	void HasFinished();
/** */
	void RequestStartFromTimer();
signals:
/** */
	void StartLogManager();
private:
	LogManager	*LogManager;
	QThread		WorkerThread;
	QTimer		*m_Timer;
	bool		LogManagerRunning;
};

}