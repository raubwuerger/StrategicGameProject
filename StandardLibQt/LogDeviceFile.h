#ifndef LOGDEVICEFILE_H
#define LOGDEVICEFILE_H

#include "LogDeviceInterface.h"

class LogDeviceFile : public LogDeviceInterface
{
public:
	/** */
	LogDeviceFile();
	/** */
	~LogDeviceFile();
	/** */
	bool Init() override;
private:
	/** */
	bool DoLogMessage(const jha::LogMessage* logMessage) override;
	/** */
	QString AddPrefixToFilename() const;
	/** */
	QString CreateFilenameIncludingPath() const;
	/** */
	bool Open();
	/** */
	bool CreateAbsoluteFilepathIfNotExisting(QString& absoluteFilepath);
private:
	QString	LogFileName;
	QString	LogFilePath;
	QFile*	LogFile;
};

#endif // LOGDEVICEFILE_H