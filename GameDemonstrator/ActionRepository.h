#ifndef QACTIONREPOSITORY_H
#define QACTIONREPOSITORY_H

#include <QObject>
#include "BaseRepository.h"

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
private:
	/** */
	ActionRepository(QObject *parent);
	/** */
	~ActionRepository();
private:
	QList<QAction*>	Actions;
	static ActionRepository* Instance;
};

#endif // QACTIONREPOSITORY_H

