#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class ActionRepository;
class GameTurnDialog;
class HexItemInfoDialog;
class GameMainThread;
class GameMainLoop;
class MapView;
class MapEventManager;
class EditorToolbox;
class TerrainTypeEditor;
class UnitTypeEditor;
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
signals:
	void StartMainGameLoop();
private:
	Ui::GameDemonstratorClass ui;
private:
	void CreateMenuFile();
	void CreateMenuAbout();
	void CreateGameTurnInfoDialog();
	void CreateMainGameThreadAndLoop();
	void CreateHexItemInfoDialog();
	void InitMainGameThread();
	void InitLoggingFramwork();
	bool LoadTerrainTypes();
	bool LoadOwnerTypes();
	bool LoadUnitTypes();
	bool ReadTerrainTypes(QIODevice *device);
	void CreateEditorToolbox( TerrainTypeEditor *terrainTypeEditor, UnitTypeEditor *unitTypeEditor );
	TerrainTypeEditor* CreateTerrainTypeEditor(MapEventManager* mapEventManager);
	UnitTypeEditor* CreateUnitTypeEditor(MapEventManager* mapEventManager);
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	ActionRepository*			ActionRepository;
	GameTurnDialog*				GameTurnDialogInstance;
	HexItemInfoDialog*			HexItemInfoDialogInstance;
	GameMainThread*				MainThread;
	GameMainLoop*				MainGameLoop;
	jha::LoggingTableWidget*	DockWidgetLogging;
	MapView*					MapViewInstance;
	SerializerGame*			ConnectorSaveGameInstance;
	EditorToolbox*				EditorToolboxInstance;
	ConnectorTerrainEditorGameMap*	ConnectorEditorModelRepositoryInstance;
	ConnectorUnitTypeGameMap*		ConnectorUnitTypeEditorGameMapInstance;
	ConnectorLoadCreateGame*		ConnectorLoadCreateGameInstance;
};

#endif // GAMEDEMONSTRATOR_H
