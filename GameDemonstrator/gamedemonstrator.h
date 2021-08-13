#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class ActionRepository;
class GameTurnDialog;
class HexItemInfoDialog;
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
	void CreateMenuFile();
	void CreateMenuAbout();
	void CreateGameTurnInfoDialog();
	void CreateMainGameThreadAndLoop();
	void CreateHexItemInfoDialog();
	void CreateUnitTypeInfoDialog();
	void InitMainGameThread();
	void InitLoggingFramwork();
	bool LoadTerrainTypes();
	bool LoadOwnerTypes();
	bool LoadUnitTypes();
	bool ReadTerrainTypes(QIODevice *device);
	void CreateEditorToolbox();
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	ActionRepository*			ActionRepository;
	GameTurnDialog*				GameTurnDialogInstance;
	HexItemInfoDialog*			HexItemInfoDialogInstance;
	UnitTypeInfoDialog*			UnitTypeInfoDialogInstance;
	GameMainThread*				MainThread;
	GameMainLoop*				MainGameLoopInstance;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	SerializerGame*				ConnectorSaveGameInstance;
	EditorToolbox*				EditorToolboxInstance;
	ConnectorLoadCreateGame*	ConnectorLoadCreateGameInstance;
	Ui::GameDemonstratorClass ui;
};

#endif // GAMEDEMONSTRATOR_H
