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
/** */
	void SlotCheckTriggerGameMainLoop();
/** */
	void SlotTurnFinished();
signals:
	/** */
	void SignalTriggerGameMainLoop();
private:
	QTimer	*TriggerGameMainLoop;
	bool	HasTurnFinished;
};

#endif // GAMEMAINTHREAD_H
