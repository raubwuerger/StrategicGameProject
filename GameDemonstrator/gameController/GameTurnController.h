#ifndef GAMETURNCONTROLLER_H
#define GAMETURNCONTROLLER_H

/** Controlls Game Turn */
class GameTurnController : public QObject
{
	Q_OBJECT
public:
	/** */
	GameTurnController();
public slots:
	/** */
	void SlotStartNextTurn();
signals:
	/** */
	void SignalUpdateTurnDialog();
	/** */
	void SignalUpdateTurnObjects();
};

#endif // GAMETURNCONTROLLER_H