#pragma once
#include "Logger.h"

namespace jha
{

class LogMessage;

class LoggerCout : public Logger
{
public:
/** Konstruktor */
	LoggerCout();
/** */
	virtual bool Init();
/** */
	virtual bool LogMessage( const std::vector<jha::LogMessage*>& logMessage );
private:
};

}