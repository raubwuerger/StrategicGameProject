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
private:
	void CreateGameModes();
	void CreateMenuFile();
	void CreateMenuAbout();
	void CreateMenuGameMode();
	void InitLoggingFramwork();
	void CreateMenuGameModeMenu();
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	GameMainDialog*				GameMainDialogObject;
	ActionRepository*			ActionRepository;
	GameTurnDialog*				GameTurnDialogInstance;
	GameMainThread*				MainThread;
	GameMainLoop*				MainGameLoopInstance;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	SerializerGame*				ConnectorSaveGameInstance;
	ConnectorLoadCreateGame*	ConnectorLoadCreateGameInstance;
	GameMode*					CurrentGameMode;
	GameMode*					GameModeEditorObject;
	GameMode*					GameModeSinglePlayerObject;
	Ui::GameDemonstratorClass	ui;
};

#endif // GAMEDEMONSTRATOR_H
