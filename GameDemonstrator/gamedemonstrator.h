#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class QActionRepository;
class GameTurnDialog;
class GameMainThread;
class GameMainLoop;

class GameDemonstrator : public QMainWindow
{
	Q_OBJECT
public:
	/** */
	GameDemonstrator(QWidget *parent = 0);
	/** */
	~GameDemonstrator();
signals:
	void StartMainGameLoop();
private:
	Ui::GameDemonstratorClass ui;
private:
	void CreateMenuFile();
	void CreateMenuAbout();
	void CreateGameTurnInfoDialog();
	void CreateMainGameThreadAndLoop();
	void InitMainGameThread();
private:
	QMenu	*m_FileMenu;
	QActionRepository	*m_ActionRepository;
	GameTurnDialog		*m_GameTurnDialog;
	GameMainThread		*m_MainThread;
	GameMainLoop		*m_MainGameLoop;
};

#endif // GAMEDEMONSTRATOR_H
