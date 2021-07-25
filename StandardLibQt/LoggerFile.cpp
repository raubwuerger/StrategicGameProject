#include "stdafx.h"
#include "LoggerFile.h"
#include "LogMessage.h"
#include <fstream>
#include <io.h>

namespace jha
{

LoggerFile::LoggerFile( const QString& path )
	: Logger("LoggerFile"),
	LogFilePathName(path)
{
}

bool LoggerFile::Init()
{
	std::ofstream logFile;
	if( OpenLogfile(logFile) == false )
	{
		return false;
	}
	return CloseLogfile(logFile);
}

bool LoggerFile::DoLogMessage( const QVector<jha::LogMessage*>& logMessage )
{
	std::ofstream logFile;
	if( OpenLogfile(logFile) == false )
	{
		return false;
	}
	for( size_t i=0;i<logMessage.size();i++ )
	{
		logFile << CreateDefaultLogString(logMessage.at(i)).toStdString() << "\n";
	}
	return CloseLogfile(logFile);
}

bool LoggerFile::OpenLogfile( std::ofstream& file )
{
	file.open( CreateLogfileName().toStdString(), std::ios::app);
	if( file.fail() == true || file.bad() == true )
	{
		//TODO: Fehlermedlung ausgeben. Aber wie? Darf ja nicht an sich selber weitergegeben werden ... Endlosschleife
		//TODO: Mechanismus überlegen, damit nicht an sich selber übergeben wird!
		//TODO: Kann nur über cout ausgegeben werden, oder Messagebox?!
		return false;
	}

	return true;
}

bool LoggerFile::CloseLogfile( std::ofstream& file )
{
	file.close();
	return true; //TODO: Nur damit Kompilierbar ist
}

QString LoggerFile::CreateLogfileName() const
{
	QFileInfo fileInfo(LogFilePathName);
	QString newFileName;
	newFileName += fileInfo.absolutePath();
	newFileName += "/";
	newFileName += QDate::currentDate().toString(jha::Logger::DEFAULT_DATE_FORMAT);
	newFileName += "_";
	newFileName += fileInfo.fileName();
	return newFileName;
}

}