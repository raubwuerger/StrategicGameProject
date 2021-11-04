#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class ActionRepository;
class MapView;
class GameMainDialog;
class ConnectorLoadGame;
class ConnectorSaveGame;

namespace jha
{
	class LoggingTableWidget;
}

class GameDemonstrator : public QMainWindow
{
	Q_OBJECT
public:
	/** */
	GameDemonstrator(QWidget *parent = 0);
	/** */
	~GameDemonstrator();
public slots:
	/** */
	void ShowGameMainDialog();
private:
	void InitGameFactory();
	void CreateMenuFile();
	void CreateMenuAbout();
	void CreateMenuGameMode();
	void InitLoggingFramwork();
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	GameMainDialog*				GameMainDialogObject;
	ActionRepository*			ActionRepository;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	ConnectorLoadGame*			ConnectorLoadGameObject;
	ConnectorSaveGame*			ConnectorSaveGameObject;
	Ui::GameDemonstratorClass	ui;
private:
	void DoSomeExperiments();
	/** */
	void DoUnitTests();
};

#endif // GAMEDEMONSTRATOR_H
