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
	bool ReadTerrainTypes(QIODevice *device);

private:
	QMenu	*m_FileMenu;
	QActionRepository	*m_ActionRepository;
	GameTurnDialog		*m_GameTurnDialog;
	HexItemInfoDialog	*m_HexItemInfoDialog;
	GameMainThread		*m_MainThread;
	GameMainLoop		*m_MainGameLoop;
	jha::LoggingTableWidget	*m_DockWidgetLogging;
	CTerrainTypeRepository	*m_TerrainTypeRepository;
};

#endif // GAMEDEMONSTRATOR_H
