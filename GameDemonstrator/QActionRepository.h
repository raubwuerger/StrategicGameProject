#pragma once

#include <QObject>

class QActionRepository : public QObject
{
	Q_OBJECT

public:
	/** */
	QActionRepository(QObject *parent);
	/** */
	~QActionRepository();
	/** */
	void AddAction( QAction* action );
private:
	QList<QAction*>	m_Actions;
};

