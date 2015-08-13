#ifndef QACTIONREPOSITORY_H
#define QACTIONREPOSITORY_H

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

#endif // QACTIONREPOSITORY_H
