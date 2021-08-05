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
class ConnectorEditorModelRepository;

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
	void CreateEditorToolbox( TerrainTypeEditor *terrainTypeEditor );
	TerrainTypeEditor* CreateTerrainTypeEditor( MapEventManager* mapEventManager );
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
	ConnectorEditorModelRepository*	ConnectorEditorModelRepositoryInstance;
};

#endif // GAMEDEMONSTRATOR_H
