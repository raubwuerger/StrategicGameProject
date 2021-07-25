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
	LoggerFile();
/** */
	void SetFilename( const QString& filename ) { Filename = filename; }
/** */
	void SetFilepath( const QString& filepath ) { Filepath = filepath; }
/** */
	virtual bool Init();
/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage );
private:
/** */
	bool CloseLogfile( std::ofstream& file );
/** */
	void AddPrefixToFilename() const;
/** */
	void CreateFilenameIncludingPath() const;
/** */
	bool CheckIfFileCouldBeOpened();
private:
	QString Filepath;
	QString Filename;
	mutable QString FilenameIncludingPrefix;
	mutable QString FilenameIncludingPath;
};

}