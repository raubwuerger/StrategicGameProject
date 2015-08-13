#ifndef GAMEMAINLOOP_H
#define GAMEMAINLOOP_H

#include <QObject>
class GameMainCounter;

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
	void Run();
	/** */
	void Start();
	/** */
	void Stop();
	/** */
	void Pause();
signals:
	void TurnFinished( QDate date );
private:
	GameMainCounter	*GameCounter;
	bool	m_RunLoop;
};

#endif // GAMEMAINLOOP_H
