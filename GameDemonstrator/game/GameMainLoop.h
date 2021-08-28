#ifndef GAMEMAINLOOP_H
#define GAMEMAINLOOP_H

#include <QObject>

class GameMainLoop : public QObject
{
	Q_OBJECT
public:
	/** */
	GameMainLoop(QObject *parent);
	/** */
	~GameMainLoop();
public slots:
	/** */
	void SlotStep();
signals:
	void SignalTurnFinished( QDate date );
private:
	bool	RunLoop;
};

#endif // GAMEMAINLOOP_H
