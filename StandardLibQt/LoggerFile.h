#pragma once
#include <QVector>
#include <QString>
#include "Logger.h"

namespace jha
{

class LogMessage;

class LoggerFile : public Logger
{
public:
/** Konstruktor */
	LoggerFile( const QString& pathName );
/** */
	virtual bool Init();
/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage );
private:
/** */
	bool OpenLogfile( std::ofstream& file );
/** */
	bool CloseLogfile( std::ofstream& file );
/** */
	QString CreateLogfileName() const;
private:
	QString LogFilePathName;
};

}