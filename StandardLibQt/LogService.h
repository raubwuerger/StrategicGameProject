#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include "LogMessage.h" //TODO: Could be solved more elegant with Q_DECLARE_METATYPE(jha::LogMessage)
class LogWorker;

class LogService : public QObject
{
	Q_OBJECT
public:
	/** */
	explicit LogService(QObject *parent = nullptr);
	/** */
	~LogService();
signals:
	// to use the service, just call this signal to send a request:
	// logService->logEvent("event");
	void Signal_LogMessage(const jha::LogMessage* logMessage);
private:
	QThread*	Thread;
	LogWorker*	LogWorkerObject;
};

#endif // LOGSERVICE_H