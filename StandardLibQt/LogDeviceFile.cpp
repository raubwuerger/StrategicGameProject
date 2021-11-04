#include "stdafx.h"
#include "LogDeviceFile.h"
#include <iostream>

LogDeviceFile::LogDeviceFile()
	: LogDeviceInterface("LogDeviceFile"),
	LogFile(nullptr)
{
	//TODO: Parametrierung sollte über LogDeviceFactory laufen
	LogFileName = QCoreApplication::applicationName();
	LogFileName += ".log";
	LogFilePath = "./log";
}

LogDeviceFile::~LogDeviceFile()
{
	if (nullptr == LogFile)
	{
		return;
	}
	LogFile->close();
	delete LogFile;
	LogFile = nullptr;
}

bool LogDeviceFile::Init()
{
	if (true == LogFileName.isEmpty())
	{
		std::cout << "Init failed! Filename is empty -> SetFilename(...) " << endl;
		return false;
	}

	if (true == LogFilePath.isEmpty())
	{
		std::cout << "Init failed! Filepath is empty -> SetFilepath(...) " << endl;
		return false;
	}

	if (false == Open())
	{
		std::cout << "Unable to open log file: " << LogFileName.toStdString() << endl;
		return false;
	}
	return true;
}

bool LogDeviceFile::Open()
{
	QString logFilepath;
	if (false == CreateAbsoluteFilepathIfNotExisting(logFilepath))
	{
		return false;
	}

	LogFile = new QFile(logFilepath);
	if (false == LogFile->open(QIODevice::Append | QIODevice::Text))
	{
		std::cout << "Unable to open log file: " << LogFile->fileName().toStdString() << endl;
		return false;
	}

	return true;
}

bool LogDeviceFile::CreateAbsoluteFilepathIfNotExisting(QString& absoluteFilepath)
{
	QFileInfo fileInfo(CreateFilenameIncludingPath());
	QString filePath = fileInfo.absolutePath();
	QDir logDirectory(filePath);

	if (true == logDirectory.exists())
	{
		absoluteFilepath = fileInfo.absoluteFilePath();
		return true;
	}

	if (true == logDirectory.mkpath(fileInfo.absolutePath()))
	{
		absoluteFilepath = fileInfo.absoluteFilePath();
		return true;
	}

	std::cout << "Unable to create path: " << filePath.toStdString() << endl;
	return false;
}

QString LogDeviceFile::CreateFilenameIncludingPath() const
{
	QString fullFileNameTemp;
	fullFileNameTemp += LogFilePath;
	fullFileNameTemp += QDir::separator();
	fullFileNameTemp += AddPrefixToFilename();

	QFileInfo fileInfo(fullFileNameTemp);
	QString filenameIncludingPath(fileInfo.absolutePath());
	filenameIncludingPath += QDir::separator();
	filenameIncludingPath += fileInfo.fileName();
	return filenameIncludingPath;
}

QString LogDeviceFile::AddPrefixToFilename() const
{
	QString filenameWithPrefix;
	filenameWithPrefix += QDate::currentDate().toString(DEFAULT_DATE_FORMAT);
	filenameWithPrefix += "_";
	filenameWithPrefix += LogFileName;
	return filenameWithPrefix;
}

bool LogDeviceFile::DoLogMessage(const jha::LogMessage* logMessage)
{
	Q_ASSERT(logMessage);
	Q_ASSERT(LogFile);

	QTextStream out(LogFile);
	out << CreateLogString(logMessage) << "\n";

	bool flushResult = LogFile->flush(); //???
	return true;
}

