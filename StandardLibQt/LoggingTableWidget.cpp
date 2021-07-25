#include "stdafx.h"
#include "LoggingTableWidget.h"

namespace jha
{

//================================================================================
//================================================================================
//================================================================================
LoggingTableWidget::LoggingTableWidget( int rows, int columns, QWidget * parent )
	: QTableWidget(rows,columns,parent),
	RowsAdded(false)
{
	TimerScrollToBottom = new QTimer;
	TimerScrollToBottom->setInterval(100);
	connect(TimerScrollToBottom,SIGNAL(timeout()),SLOT(ScrollToBottom()));
	TimerScrollToBottom->start();
	
	setRowCount(0);
	setColumnCount(4);

	verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader()->setDefaultSectionSize(20);

	setSelectionBehavior(QAbstractItemView::SelectRows);

	horizontalHeader()->setStretchLastSection(true);

	QTableWidgetItem *time = new QTableWidgetItem("Time");
	time->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 0, time );

	QTableWidgetItem *logLevel = new QTableWidgetItem("Log level");
	logLevel->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 1, logLevel );

	QTableWidgetItem *category = new QTableWidgetItem("Category");
	category->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 2, category );

	QTableWidgetItem *message = new QTableWidgetItem("Message");
	message->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 3, message );

	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void LoggingTableWidget::AppendRow( jha::LoggingTableWidgetRow *newRow )
{
	if( newRow == nullptr )
	{
		return;
	}
	if( newRow->m_Items.isEmpty() == true )
	{
		return;
	}

	int newRowIndex = rowCount();
	insertRow( newRowIndex );

	for( int i=0;i<newRow->m_Items.size();i++ )
	{
		setItem(newRowIndex,i,newRow->m_Items.at(i));
	}

	delete newRow;
	newRow = nullptr;

	RowsAdded = true;
}

LoggingTableWidget::~LoggingTableWidget()
{
	delete TimerScrollToBottom;
}

void LoggingTableWidget::ScrollToBottom()
{
	if( RowsAdded == false )
	{
		return;
	}
	RowsAdded = false;
	scrollToBottom();
}

}
