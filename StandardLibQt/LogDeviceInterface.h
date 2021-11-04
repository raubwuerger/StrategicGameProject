#ifndef LOGDEVICEINTERFACE_H
#define LOGDEVICEINTERFACE_H

#include "LogLevel.h"

class LogDeviceInterface
{
public:
	/** */
	LogDeviceInterface(const QString& name);
	/** */
	virtual bool Init() = 0;
	/** */
	bool LogMessage(const jha::LogMessage* logMessage);
	/** */
	QString GetName() const;
protected:
	/** */
	QString CreateLogString(const jha::LogMessage *message) const;
private:
	/** */
	LogDeviceInterface();
	/** */
	bool LogThisLogLevel(jha::LogMessage *message) const;
	/** */
	virtual bool DoLogMessage(const jha::LogMessage* logMessage) = 0;
protected:
	const QString DEFAULT_TIME_FORMAT;
	const QString DEFAULT_DATE_FORMAT;
	const QString SEPARATOR;
private:
	QString			Name;
	bool			Enabled;
	jha::LogLevel	LogLevelInstance;
};

#endif // LOGDEVICEINTERFACE_H