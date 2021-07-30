#include "stdafx.h"
#include "LoggerFile.h"
#include "LogMessage.h"
#include <iostream>

namespace jha
{

	//==============================================================================
	LoggerFile::LoggerFile()
		: Logger("LoggerFile"),
		Filename(""),
		Filepath("")
	{
	}

	//==============================================================================
	bool LoggerFile::Init()
	{
		if( true == Filename.isEmpty() )
		{
			std::cout << "Init failed! Filename is empty -> SetFilename(...) " << endl;
			return false;
		}

		if( true == Filepath.isEmpty() )
		{
			std::cout << "Init failed! Filepath is empty -> SetFilepath(...) " << endl;
			return false;
		}

		AddPrefixToFilename();
		CreateFilenameIncludingPath();
		if( false == CheckIfFileCouldBeOpened() )
		{
			std::cout << "Unable to open log file: " << Filename.toStdString() << endl;
			return false;
		}
		return true;
	}

	//==============================================================================
	void LoggerFile::AddPrefixToFilename() const
	{
		QString filenameWithPrefix;
		filenameWithPrefix += QDate::currentDate().toString(jha::Logger::DEFAULT_DATE_FORMAT);
		filenameWithPrefix += "_";
		filenameWithPrefix += Filename;
		FilenameIncludingPrefix = filenameWithPrefix;
	}

	//==============================================================================
	void LoggerFile::CreateFilenameIncludingPath() const
	{
		QString fullFileNameTemp;
		fullFileNameTemp += Filepath;
		fullFileNameTemp += QDir::separator();
		fullFileNameTemp += FilenameIncludingPrefix;

		QFileInfo fileInfo(fullFileNameTemp);
		FilenameIncludingPath += fileInfo.absolutePath();
		FilenameIncludingPath += QDir::separator();
		FilenameIncludingPath += fileInfo.fileName();
	}

	//==============================================================================
	bool LoggerFile::CheckIfFileCouldBeOpened()
	{
		QFileInfo fileInfo(FilenameIncludingPath);
		QString filePath = fileInfo.absolutePath();
		QDir logDirectory(filePath);

		if( false == logDirectory.exists() )
		{
			if( false == logDirectory.mkpath(fileInfo.absolutePath()) )
			{
				std::cout << "Unable to create path: " << filePath.toStdString() << endl;
				return false;
			}
		}

		QString fileName = fileInfo.absoluteFilePath();
		QFile logFile( fileName );
		if( false == logFile.exists() )
		{
			std::cout << "File dos not exist: " << fileName.toStdString() << endl;
			if( false == logFile.open(QIODevice::ReadWrite | QIODevice::Text) )
			{
				std::cout << "Unable to create File: " << fileName.toStdString() << endl;
				return false;
			}
			std::cout << "File has been created: " << fileName.toStdString() << endl;
		}
		logFile.close();
		return true;
	}

	//==============================================================================
	bool LoggerFile::DoLogMessage( const QVector<jha::LogMessage*>& logMessage )
	{
		if( true == logMessage.isEmpty() )
		{
			return true;
		}

		QFile logFile( FilenameIncludingPath );
		if( false == logFile.open( QIODevice::Append | QIODevice::Text ) )
		{
			std::cout << "Unable to open log file: " << FilenameIncludingPath.toStdString() << endl;
			return false;
		}

		QTextStream out(&logFile);
		for( size_t i=0;i<logMessage.size();i++ )
		{
			out << CreateDefaultLogString( logMessage.at(i) )  << "\n";
		}

		bool flushResult = logFile.flush();
		logFile.close();
		return true;
	}

}