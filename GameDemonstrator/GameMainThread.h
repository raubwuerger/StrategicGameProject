#ifndef GAMEMAINTHREAD_H
#define GAMEMAINTHREAD_H

#include <QThread>
class GameMainLoop;

class GameMainThread : public QThread
{
	Q_OBJECT
public:
	/** */
	GameMainThread();
	/** */
	~GameMainThread();
	/** */
	void Init( GameMainLoop *gameMainLoop );
	/** */
	void run();
public slots:
	void CheckTriggerGameMainLoop();
	void TurnFinished();
signals:
	void TriggerGameMainLoop();
private:
	QTimer	*m_TriggerGameMainLoop;
	bool	m_TurnFinished;
};

#endif // GAMEMAINTHREAD_H
