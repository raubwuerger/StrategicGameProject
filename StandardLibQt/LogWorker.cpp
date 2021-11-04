#include "stdafx.h"
#include "LogWorker.h"
#include "LogDeviceFile.h"
#include "LogMessage.h"

LogWorker::LogWorker(QObject *parent /*= nullptr*/)
	: QObject(parent),
	LogDevice(nullptr),
	LogMessageIndex(0)
{
	LogDevice = new LogDeviceFile();
	LogDevice->Init();
}

LogWorker::~LogWorker()
{
	delete LogDevice;
}

void LogWorker::Slot_LogMessage(const jha::LogMessage* logMessage)
{
	if (0 == LogMessageIndex)
	{
		InjectInitialLogMessage();
		LogMessageIndex++;
	}
	LogDevice->LogMessage(logMessage);
	//TODO: Part old logmanager with different LogDevices ...
}

void LogWorker::InjectInitialLogMessage()
{
	QString initialLogMessage(tr("#################### START LOGGING (%1) ####################").arg(QDate::currentDate().toString("yyyy-MM-dd")));
	LogDevice->LogMessage( new jha::LogMessage(QTime::currentTime(), jha::LogInterface::LOGLEVEL_INIT, initialLogMessage, QCoreApplication::applicationName()));
}
