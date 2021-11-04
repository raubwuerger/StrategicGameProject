#include "stdafx.h"
#include "LogService.h"
#include "LogWorker.h"

LogService::LogService(QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	Thread = new QThread(this);
	LogWorkerObject = new LogWorker;
	LogWorkerObject->moveToThread(Thread);
	connect(this, &LogService::Signal_LogMessage, LogWorkerObject, &LogWorker::Slot_LogMessage);
	connect(Thread, &QThread::finished, LogWorkerObject, &QObject::deleteLater);
	Thread->start();
}

LogService::~LogService()
{
	Thread->quit();
	Thread->wait();
}
