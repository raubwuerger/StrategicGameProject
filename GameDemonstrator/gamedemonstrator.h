#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class ActionRepository;
class GameTurnDialog;
class HexItemInfoDialog;
class CityTypeInfoDialog;
class UnitTypeInfoDialog;
class GameMainThread;
class GameMainLoop;
class MapView;
class MapHexItemEventManager;
class EditorToolbox;
class CreateNewMap;
class ConnectorTerrainEditorGameMap;
class ConnectorUnitTypeGameMap;
class ConnectorLoadCreateGame;
class SerializerGame;
class GameMode;
class GameMainDialog;
class GameModeController;

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
	GameTurnDialog*				GameTurnDialogInstance;
	GameMainLoop*				MainGameLoopInstance;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	SerializerGame*				ConnectorSaveGameInstance;
	ConnectorLoadCreateGame*	ConnectorLoadCreateGameInstance;
	GameModeController*			GameModeControllerObject;
	Ui::GameDemonstratorClass	ui;
};

#endif // GAMEDEMONSTRATOR_H
