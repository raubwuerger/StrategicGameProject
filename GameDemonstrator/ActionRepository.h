#ifndef QActionRepository_H
#define QActionRepository_H

#include <QObject>

class ActionRepository : public QObject
{
	Q_OBJECT

public:
	/** */
	static ActionRepository* GetInstanceFirstTimeInit(QObject *parent);
	/** */
	static ActionRepository* GetInstance();
	/** */
	void AddAction( QAction* action );
	/** */
	void Release();
private:
	/** */
	ActionRepository(QObject *parent);
	/** */
	~ActionRepository();
private:
	QList<QAction*>	Actions;
	static ActionRepository* Instance;
};

#endif

