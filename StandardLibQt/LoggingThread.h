#pragma once


#include <QThread>

namespace jha
{

class LoggingWorker;

class LoggingThread : public QThread
{
	Q_OBJECT
public:
/** Constructor */
	LoggingThread();
	/** Destructor */
	~LoggingThread();
/** */
	bool Init();
signals:
	void ProcessMessages();
private:
	QTimer*			Timer;
};

}