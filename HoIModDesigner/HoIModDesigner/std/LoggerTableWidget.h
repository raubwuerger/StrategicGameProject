#pragma once
#include <QVector>
#include <QString>
#include "Logger.h"

class LoggingTableWidgetRow;
class LoggingTableWidget;

namespace jha
{

class WidgetConnector : public QObject
{
	Q_OBJECT
public:
	bool ConnectMe( LoggingTableWidget *widget );
signals:
	void SignalAppendRow(LoggingTableWidgetRow*);
};

class LogMessage;
class LoggerTableWidget : public Logger
{
public:
/** Konstruktor */
	LoggerTableWidget( LoggingTableWidget *tableWidget );
/** Destruktor */
	~LoggerTableWidget();
/** */
	virtual bool Init();
protected:
/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage );
private:
	LoggingTableWidget *m_TableWidget;
	WidgetConnector		*m_WidgetConnector;
};

}