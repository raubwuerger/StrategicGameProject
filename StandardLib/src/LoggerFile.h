#pragma once
#include "Logger.h"

namespace jha
{

class LogMessage;

class LoggerFile : public Logger
{
public:
/** Konstruktor */
	LoggerFile();
/** */
	virtual bool Init();
/** */
	virtual bool LogMessage( const std::vector<jha::LogMessage*>& logMessage );
private:
/** */
	bool OpenLogfile( std::ofstream& file );
/** */
	bool CloseLogfile( std::ofstream& file );
/** */
	std::string CreateLogfileName() const;
private:
	std::string m_LogFileName;
};

}