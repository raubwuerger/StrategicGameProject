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
private:
/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage );
private:
};

}