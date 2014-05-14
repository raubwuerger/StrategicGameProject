#include "stdafx.h"
#include "LoggerFile.h"
#include "LogMessage.h"
#include "DateTime.h"
#include <fstream>
#include <io.h>

namespace jha
{

LoggerFile::LoggerFile()
	: Logger("LoggerFile")
{
}

bool LoggerFile::Init()
{
	std::ofstream logFile;
	return OpenLogfile(logFile);
}

bool LoggerFile::LogMessage( const std::vector<jha::LogMessage*>& logMessage )
{
// 	for( size_t i=0;i<logMessage.size();i++ )
// 	{
// 		std::cout << logMessage.at(0)->GetLogTime().TimeToString() << "\t" << "LogLevel" << "\t" << "Kategorie" << "\t" << logMessage.at(0)->GetMessage() << std::endl;
// 	}
// 	return true;
	return false;
}

bool LoggerFile::OpenLogfile( std::ofstream& file )
{
	file.open(CreateLogfileName(), std::ios::app);
	if( file.fail() == true || file.bad() == true )
	{
		//TODO: Fehlermedlung ausgeben. Aber wie? Darf ja nicht an sich selber weitergegeben werden ... Endlosschleife
		//TODO: Mechanismus überlegen, damit nicht an sich selber übergeben wird!
		return false;
	}

	return true;
}

bool LoggerFile::CloseLogfile( std::ofstream& file )
{
	file.close();
	return true; //TODO: Nur damit Kompilierbar ist
}

std::string LoggerFile::CreateLogfileName() const
{
	std::string fileName;
	std::string date = Time().DateToString();

	fileName += date;
	fileName += "_";
	fileName += m_LogFileName;
	return fileName;
}

}