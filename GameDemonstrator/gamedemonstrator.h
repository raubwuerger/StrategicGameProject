#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class QActionRepository;
class GameTurnDialog;
class GameMainThread;
class GameMainLoop;
class HexItemInfoDialog;
class CTerrainTypeRepository;
class MapView;
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
	QMenu	*m_FileMenu;
	QMenu	*m_ViewMenu;
	QMenu	*m_InfoMenu;
	QActionRepository	*m_ActionRepository;
	GameTurnDialog		*m_GameTurnDialog;
	HexItemInfoDialog	*m_HexItemInfoDialog;
	GameMainThread		*m_MainThread;
	GameMainLoop		*m_MainGameLoop;
	jha::LoggingTableWidget	*m_DockWidgetLogging;
	CTerrainTypeRepository	*m_TerrainTypeRepository;
	COwnerTypeRepository	*m_OwnerTypeRepository;
	MapView				*mapView;

	CEditorToolbox		*m_EditorToolbox;
};

#endif // GAMEDEMONSTRATOR_H
