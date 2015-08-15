#pragma once
#include <QVector>
#include <QString>
#include "Logger.h"

namespace jha
{

class LoggingTableWidgetRow;
class LoggingTableWidget;

class WidgetConnector : public QObject
{
	Q_OBJECT
public:
	bool ConnectMe( jha::LoggingTableWidget *widget );
signals:
	void SignalAppendRow( jha::LoggingTableWidgetRow *row );
};

class LogMessage;
class LoggerTableWidget : public Logger
{
public:
/** Konstruktor */
	LoggerTableWidget( jha::LoggingTableWidget *tableWidget );
/** Destruktor */
	~LoggerTableWidget();
/** */
	virtual bool Init();
protected:
/** */
	virtual bool DoLogMessage( const QVector<jha::LogMessage*>& logMessage );
private:
	jha::LoggingTableWidget *m_TableWidget;
	WidgetConnector		*m_WidgetConnector;
};

}