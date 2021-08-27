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
	void CreateGameTurnInfoDialog();
	void CreateMainGameThreadAndLoop();
	void CreateHexItemInfoDialog();
	void CreateUnitTypeInfoDialog();
	void CreateCityTypeInfoDialog();
	void InitMainGameThread();
	void InitLoggingFramwork();
	void CreateEditorToolbox();
	void CreateMenuGameModeMenu();
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	QMenu	*EditorMenu;
	QMenu	*GameModeMenu;
	GameMainDialog*				GameMainDialogObject;
	ActionRepository*			ActionRepository;
	GameTurnDialog*				GameTurnDialogInstance;
	HexItemInfoDialog*			HexItemInfoDialogInstance;
	UnitTypeInfoDialog*			UnitTypeInfoDialogInstance;
	CityTypeInfoDialog*			CityTypeInfoDialogInstance;
	GameMainThread*				MainThread;
	GameMainLoop*				MainGameLoopInstance;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	SerializerGame*				ConnectorSaveGameInstance;
	EditorToolbox*				EditorToolboxInstance;
	ConnectorLoadCreateGame*	ConnectorLoadCreateGameInstance;
	GameMode*					CurrentGameMode;
	GameMode*					GameModeEditorObject;
	GameMode*					GameModeSinglePlayerObject;
	Ui::GameDemonstratorClass ui;
};

#endif // GAMEDEMONSTRATOR_H
