#ifndef LOGWORKER_H
#define LOGWORKER_H

class LogDeviceInterface;
namespace jha
{
	class LogMessage;
}


class LogWorker : public QObject
{
	Q_OBJECT
public:
/** */
	explicit LogWorker(QObject *parent = nullptr);
/** */
	~LogWorker();
public slots:
	// this slot will be executed by event loop (one call at a time)
	void Slot_LogMessage(const jha::LogMessage* logMessage);
private:
	/** */
	void InjectInitialLogMessage();
private:
	LogDeviceInterface*	LogDevice;
	unsigned long			LogMessageIndex;
};

#endif // LOGWORKER_H