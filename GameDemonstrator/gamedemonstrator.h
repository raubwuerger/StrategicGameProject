#ifndef GAMEDEMONSTRATOR_H
#define GAMEDEMONSTRATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_gamedemonstrator.h"

class QActionRepository;
class CGameTurnDialog;
class CHexItemInfoDialog;
class GameMainThread;
class GameMainLoop;
class CMapView;
class CEditorToolbox;
class CMapEventManager;
class CTerrainTypeEditor;
class COwnerTypeRepository;
class CSerializerInterface;

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
	void CreateEditorToolbox( CTerrainTypeEditor *terrainTypeEditor );
	CTerrainTypeEditor* CreateTerrainTypeEditor( CMapEventManager* mapEventManager );
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
	COwnerTypeRepository	*OwnerTypeRepository;
	CMapView				*MapView;
	CSerializerInterface* SerializerInterface;
	CEditorToolbox		*EditorToolbox;
};

#endif // GAMEDEMONSTRATOR_H
