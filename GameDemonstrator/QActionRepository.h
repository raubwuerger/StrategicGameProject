#pragma once

#include <QObject>

class QActionRepository : public QObject
{
	Q_OBJECT

public:
	/** */
	static QActionRepository* GetInstanceFirstTimeInit(QObject *parent);
	/** */
	static QActionRepository* GetInstance();
	/** */
	void AddAction( QAction* action );
	/** */
	void Release();
private:
	/** */
	QActionRepository(QObject *parent);
	/** */
	~QActionRepository();
private:
	QList<QAction*>	Actions;
	static QActionRepository* Instance;
};

