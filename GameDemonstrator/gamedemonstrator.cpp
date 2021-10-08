#include "stdafx.h"
#include "gamedemonstrator.h"
#include "ActionRepository.h"
#include "Action.h"
#include "LogFactory.h"
#include "io\ConfigurationLoader.h"
#include "dialogs/HexItemInfoDialog.h"
#include "dialogs/UnitTypeInfoDialog.h"
#include "map/MapView.h"
#include "map/MapHexItemEventManager.h"
#include "map/MapUnitItemRepository.h"
#include "io\SerializerGame.h"
#include "io\SerializeBinary.h"
#include "io\SerializerFactory.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorLoadGame.h"
#include "connectors/ConnectorSaveGame.h"
#include "editors/TerrainTypeEditor.h"
#include "editors/EditorToolbox.h"
#include "RepositoryCleaner.h"
#include "dialogs/GameMainDialog.h"
#include "map/MapCityItemRepository.h"
#include "gameController/GameFactory.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr),
	ConnectorLoadGameObject(nullptr),
	ConnectorSaveGameObject(nullptr),
	GameMainDialogObject(nullptr)
{
	ui.setupUi(this);


//	DoSomeExperiments();
//	DoUnitTests();

	FileMenu = menuBar()->addMenu(tr("&File"));
	ViewMenu = menuBar()->addMenu(tr("&View"));
	InfoMenu = menuBar()->addMenu(tr("&Info"));

	MapViewInstance = new MapView(this);
	MapViewInstance->MapEventManagerInstance = new MapHexItemEventManager(nullptr);

	InitLoggingFramwork();

	ActionRepository::GetInstanceFirstTimeInit(parent);

	ConfigurationLoader configurationLoader;
	if (false == configurationLoader.Load())
	{

	}

	QHBoxLayout *layoutMain = new QHBoxLayout;
	layoutMain->addWidget(MapViewInstance);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	MapUnitItemRepository::GetInstance()->MapViewInstance = MapViewInstance;
	MapCityItemRepository::GetInstance()->MapViewInstance = MapViewInstance;

	MapViewInstance->show();

	GameMainDialogObject = new GameMainDialog(this);
	GameMainDialogObject->Init(this);

	ConnectorLoadGameObject = new ConnectorLoadGame;
	ConnectorLoadGameObject->MapViewObject = MapViewInstance;
	ConnectorLoadGameObject->GameDemonstratorObject = this;

	ConnectorSaveGameObject = new ConnectorSaveGame;
	ConnectorSaveGameObject->GameDemonstratorObject = this;

	CreateMenuFile();
	CreateMenuAbout();
	InitGameFactory();
	ShowGameMainDialog();
}

GameDemonstrator::~GameDemonstrator()
{
	RepositoryCleaner::GetInstance()->ReleaseAll();
}

void GameDemonstrator::ShowGameMainDialog()
{
	GameMainDialogObject->show();
}

void GameDemonstrator::InitGameFactory()
{
	GameFactory::MapViewObject = MapViewInstance;
	GameFactory::GameMainDialogObject = GameMainDialogObject;
	GameFactory::GameDemonstratorObject = this;

	GameFactory gameFactory;
}

void GameDemonstrator::CreateMenuFile()
{
	QAction* loadGameAction = nullptr;
	{
		QIcon load(":GameDemonstrator/Resources/folder_document.ico");
		loadGameAction = new QAction(load, tr("&Load"), this);
		loadGameAction->setStatusTip(tr("Load current game"));
		ActionRepository::GetInstance()->AddAction(loadGameAction);
		connect(loadGameAction, &QAction::triggered, ConnectorLoadGameObject, &ConnectorLoadGame::SlotLoadGame, Qt::QueuedConnection);
	}

	Action* saveGameAction = nullptr;
	{
		QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
		saveGameAction = new Action(save, tr("&Save"), this);
		saveGameAction->setStatusTip(tr("Save current game"));
		ActionRepository::GetInstance()->AddAction(saveGameAction);
		connect(saveGameAction, &QAction::triggered, ConnectorSaveGameObject, &ConnectorSaveGame::SlotSaveGame, Qt::QueuedConnection);
	}

	Action* zoomInAction = nullptr;
	{
		QIcon zoomIn(".\\Resources\\zoom_in.ico");
		zoomInAction = new Action(zoomIn, tr("Zoom in"), this);
		zoomInAction->setStatusTip(tr("Zoom in"));
		zoomInAction->setShortcut(Qt::Key_Plus);
		ActionRepository::GetInstance()->AddAction(zoomInAction);
		connect(zoomInAction, &QAction::triggered, MapViewInstance, &MapView::SlotZoomIn, Qt::QueuedConnection);
	}

	Action* zoomOutAction = nullptr;
	{
		QIcon zoomOut(".\\Resources\\zoom_in.ico");
		zoomOutAction = new Action(zoomOut, tr("Zoom out"), this);
		zoomOutAction->setStatusTip(tr("Zoom out"));
		zoomOutAction->setShortcut(Qt::Key_Minus);
		ActionRepository::GetInstance()->AddAction(zoomOutAction);
		connect(zoomOutAction, &QAction::triggered, MapViewInstance, &MapView::SlotZoomOut, Qt::QueuedConnection);
	}

	Action* zoomOriginalAction = nullptr;
	{
		QIcon zoomOriginal(".\\Resources\\view_1_1.ico");
		zoomOriginalAction = new Action(zoomOriginal, tr("Zoom original"), this);
		zoomOriginalAction->setStatusTip(tr("Zoom original"));
		zoomOriginalAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_1));
		ActionRepository::GetInstance()->AddAction(zoomOriginalAction);
		connect(zoomOriginalAction, &QAction::triggered, MapViewInstance, &MapView::SlotZoomOriginal, Qt::QueuedConnection);
	}

	QAction* exitAction = nullptr;
	{
		QIcon exit(":GameDemonstrator/Resources/exit.ico");
		exitAction = new QAction(exit, tr("E&xit"), this);
		exitAction->setShortcuts(QKeySequence::Quit);
		exitAction->setStatusTip(tr("Quit application"));
		connect(exitAction, &QAction::triggered, this, &GameDemonstrator::close);
		ActionRepository::GetInstance()->AddAction(exitAction);
	}

	FileMenu->addAction( loadGameAction );
	FileMenu->addAction( saveGameAction );
	FileMenu->addSeparator();
	FileMenu->addAction(zoomInAction);
	FileMenu->addAction(zoomOutAction);
	FileMenu->addAction(zoomOriginalAction);
	FileMenu->addSeparator();
	FileMenu->addAction(exitAction);
}

void GameDemonstrator::CreateMenuAbout()
{
	QIcon info(":GameDemonstrator/Resources/about.ico");
	QAction* aboutAction = new QAction(info,tr("&About"), this);
	aboutAction->setStatusTip(tr("Info about application"));
	connect(aboutAction, SIGNAL(triggered()), aboutAction, SLOT(show()));
	ActionRepository::GetInstance()->AddAction(aboutAction);

	InfoMenu->addAction( aboutAction );
}

#include "LogInterface.h"
#include "LoggingTableWidget.h"
#include "LoggerFile.h"
#include "LoggerTableWidget.h"
void GameDemonstrator::InitLoggingFramwork()
{
	QDockWidget *dockWidget = new QDockWidget(tr("Logging"), this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea );
	DockWidgetLogging = new jha::LoggingTableWidget(0,0,dockWidget);

	dockWidget->setWidget( DockWidgetLogging );
	addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
	ViewMenu->addAction(dockWidget->toggleViewAction());

	if( false == jha::LogFactory::GetInstance()->Init() )
	{
		//TODO: Fehlermeldung ausgeben!!!
		return;
	}

	jha::LoggerFile* loggerFile = new jha::LoggerFile();
	loggerFile->SetFilepath("./log");
	QString logfileName( QCoreApplication::applicationName() );
	logfileName += ".log";
	loggerFile->SetFilename( logfileName );

	jha::LogFactory::GetInstance()->RegisterLogger( loggerFile );

	//TODO: Darf erst hier initialisiert werden weil die GameDemonstratorFactory selbst das logging framework verwendet!
	ModelProgramFactory modelProgramFactory;
	modelProgramFactory.Create();
	jha::GetLog()->SetGlobalLoglevel(modelProgramFactory.GetConfig()->GlobalLogLevel);

	jha::LogFactory::GetInstance()->RegisterLogger(new jha::LoggerTableWidget(DockWidgetLogging));
	if (false == modelProgramFactory.GetConfig()->ShowLoggingPane)
	{
		DockWidgetLogging->hide();
	}
}

#include "experimental/ExperimentalClass.h"
void GameDemonstrator::DoSomeExperiments()
{
	ExperimentalClass exp;
	exp.DoExperimental();
}

#include "test/DoUnitTest.h"
void GameDemonstrator::DoUnitTests()
{
	DoUnitTest unitTest;
	unitTest.DoTests();
}
