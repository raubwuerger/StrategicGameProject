#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class ActionRepository;
class MapView;
class MapHexItemEventManager;
class GameMode;
class GameMainDialog;
class GameModeController;
class GameMainLoop;
class ConnectorCreateGame;
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
	void CreateGameModeController();
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
	GameMainLoop*				MainGameLoopInstance;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	ConnectorCreateGame*		ConnectorCreateGameObject;
	ConnectorLoadGame*			ConnectorLoadGameObject;
	ConnectorSaveGame*			ConnectorSaveGameObject;
	GameModeController*			GameModeControllerObject;
	Ui::GameDemonstratorClass	ui;
};

#endif // GAMEDEMONSTRATOR_H
