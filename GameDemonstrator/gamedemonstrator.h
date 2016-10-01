#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class QActionRepository;
class CGameTurnDialog;
class CHexItemInfoDialog;
class GameMainThread;
class GameMainLoop;
class CTerrainTypeRepository;
class CMapView;
class CEditorToolbox;
class CMapEventManager;
class CTerrainTypeEditor;
class COwnerTypeRepository;

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
	bool ReadTerrainTypes(QIODevice *device);
	void CreateEditorToolbox( CTerrainTypeRepository *repository, CTerrainTypeEditor *terrainTypeEditor );
	CTerrainTypeEditor* CreateTerrainTypeEditor( CTerrainTypeRepository *terrainTypeRepository, CMapEventManager* mapEventManager );
private:
	QMenu	*FileMenu;
	QMenu	*ViewMenu;
	QMenu	*InfoMenu;
	QActionRepository	*ActionRepository;
	CGameTurnDialog		*GameTurnDialog;
	CHexItemInfoDialog	*HexItemInfoDialog;
	GameMainThread		*MainThread;
	GameMainLoop		*MainGameLoop;
	jha::LoggingTableWidget	*DockWidgetLogging;
	CTerrainTypeRepository	*TerrainTypeRepository;
	COwnerTypeRepository	*OwnerTypeRepository;
	CMapView				*MapView;

	CEditorToolbox		*EditorToolbox;
};

#endif // GAMEDEMONSTRATOR_H
