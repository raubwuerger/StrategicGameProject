#include "stdafx.h"
#include "LoggerCout.h"
#include "LogMessage.h"
#include <iostream>

namespace jha
{

LoggerCout::LoggerCout()
	: Logger("LoggerCout")
{
}

bool LoggerCout::Init()
{
	return true;
}

bool LoggerCout::LogMessage( const std::vector<jha::LogMessage*>& logMessage )
{
	for( size_t i=0;i<logMessage.size();i++ )
	{
		std::cout << logMessage.at(0)->GetLogTime().TimeToString() << "\t" << "LogLevel" << "\t" << "Kategorie" << "\t" << logMessage.at(0)->GetMessage() << std::endl;
	}
	return true;
}

}