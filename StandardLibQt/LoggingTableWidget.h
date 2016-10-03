#pragma once
#include <QTimer>

namespace jha
{

class LoggingTableWidgetRow
{
public:
	QVector<QTableWidgetItem*> m_Items;
};

class LoggingTableWidget : public QTableWidget
{
	Q_OBJECT
public:
/** */
	LoggingTableWidget(int rows, int columns, QWidget * parent );
/** */
	~LoggingTableWidget();
public slots:
/** */
	void AppendRow( jha::LoggingTableWidgetRow *newRow );
/** */
	void ScrollToBottom();
private:
	QTimer	*TimerScrollToBottom;
	bool	RowsAdded;
};

}