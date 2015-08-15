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

bool LoggerCout::DoLogMessage( const QVector<jha::LogMessage*>& logMessage )
{
	for( size_t i=0;i<logMessage.size();i++ )
	{
		std::cout << CreateDefaultLogString(logMessage.at(i)).toStdString() << endl;
	}
	return true;
}

}