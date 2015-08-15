#include "stdafx.h"
#include "LoggerTableWidget.h"
#include "LogMessage.h"
#include "LoggingTableWidget.h"

namespace jha
{

LoggerTableWidget::LoggerTableWidget( jha::LoggingTableWidget *tableWidget )
	: Logger("TableWidget"),
	m_TableWidget(tableWidget)
{
	m_WidgetConnector = new WidgetConnector;
}

LoggerTableWidget::~LoggerTableWidget()
{
	delete m_WidgetConnector;
}

bool LoggerTableWidget::Init()
{
	if( m_TableWidget == nullptr )
	{
		return false;
	}

	return m_WidgetConnector->ConnectMe(m_TableWidget);
}

bool LoggerTableWidget::DoLogMessage( const QVector<jha::LogMessage*>& logMessage )
{
	if( m_TableWidget == nullptr )
	{
		return false;
	}
	for( size_t i=0;i<logMessage.size();i++ )
	{
		jha::LogMessage* message = logMessage.at(i);
		if( LogThisLogLevel(message)  == false )
		{
			continue;
		}

		QTableWidgetItem *time = new QTableWidgetItem( message->GetLogTime().toString(jha::Logger::DEFAULT_TIME_FORMAT) );
		time->setTextColor(message->GetLogLevel().GetColor());
		time->setFlags(time->flags() & (~Qt::ItemIsEditable));

		QTableWidgetItem *logLevel = new QTableWidgetItem( message->GetLogLevel().GetName() );
		logLevel->setTextColor(message->GetLogLevel().GetColor());
		logLevel->setFlags(time->flags() & (~Qt::ItemIsEditable));

		QTableWidgetItem *category = new QTableWidgetItem( message->GetCategory() );
		category->setTextColor(message->GetLogLevel().GetColor());
		category->setFlags(time->flags() & (~Qt::ItemIsEditable));

		QTableWidgetItem *messageText = new QTableWidgetItem( message->GetMessage() );
		messageText->setTextColor(message->GetLogLevel().GetColor());
		messageText->setFlags(time->flags() & (~Qt::ItemIsEditable));

		LoggingTableWidgetRow *newRow = new LoggingTableWidgetRow;
		newRow->m_Items.push_back(time);
		newRow->m_Items.push_back(logLevel);
		newRow->m_Items.push_back(category);
		newRow->m_Items.push_back(messageText);
		emit m_WidgetConnector->SignalAppendRow(newRow);
	}

	//m_TableWidget->scrollToBottom();
	return true;
}


bool WidgetConnector::ConnectMe( LoggingTableWidget *widget )
{
	if( widget == nullptr )
	{
		return false;
	}
	return connect(this, SIGNAL(SignalAppendRow(jha::LoggingTableWidgetRow*)),widget, SLOT(AppendRow(jha::LoggingTableWidgetRow*))/*,Qt::QueuedConnection*/);
}

}