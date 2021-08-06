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
class EditorToolbox;
class MapEventManager;
class TerrainTypeEditor;
class SerializerInterface;
class CreateNewMap;
class ConnectorTerrainEditorGameMap;
class ConnectorUnitTypeGameMap;
class ConnectorLoadCreateGame;
class UnitTypeEditor;

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
	SerializerInterface*		SerializerInterface;
	EditorToolbox*				EditorToolboxInstance;
	ConnectorTerrainEditorGameMap*	ConnectorEditorModelRepositoryInstance;
	ConnectorUnitTypeGameMap*		ConnectorUnitTypeEditorGameMapInstance;
	ConnectorLoadCreateGame*		ConnectorLoadCreateGameInstance;
};

#endif // GAMEDEMONSTRATOR_H
