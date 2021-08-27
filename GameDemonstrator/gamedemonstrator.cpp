#include "stdafx.h"
#include "gamedemonstrator.h"
#include "ActionRepository.h"
#include "Action.h"
#include "LogFactory.h"
#include "ConfigurationLoader.h"
#include "game/GameMainThread.h"
#include "game/GameMainLoop.h"
#include "dialogs/GameTurnDialog.h"
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
#include "connectors/ConnectorLoadCreateGame.h"
#include "editors/TerrainTypeEditor.h"
#include "editors/EditorToolbox.h"
#include "RepositoryCleaner.h"
#include "dialogs/GameMainDialog.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	GameTurnDialogInstance(nullptr),
	MainGameLoopInstance(nullptr),
	HexItemInfoDialogInstance(nullptr),
	UnitTypeInfoDialogInstance(nullptr),
	EditorToolboxInstance(nullptr),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr),
	EditorMenu(nullptr),
	GameModeMenu(nullptr),
	CurrentGameMode(nullptr),
	ConnectorLoadCreateGameInstance(nullptr),
	MainDialog(nullptr)
{
	ui.setupUi(this);

	FileMenu = menuBar()->addMenu(tr("&File"));
	GameModeMenu = menuBar()->addMenu(tr("&GameMode"));
	EditorMenu = menuBar()->addMenu(tr("&Editor"));
	ViewMenu = menuBar()->addMenu(tr("&View"));
	InfoMenu = menuBar()->addMenu(tr("&Info"));

	MapViewInstance = new MapView(this);
	MapViewInstance->MapEventManagerInstance = new MapHexItemEventManager(nullptr);

	InitLoggingFramwork();

	ActionRepository::GetInstanceFirstTimeInit(parent);
	ConnectorSaveGameInstance = SerializerFactory().CreateInterface();

	ConfigurationLoader configurationLoader;
	if (false == configurationLoader.Load())
	{

	}

	CreateGameTurnInfoDialog();
	CreateMainGameThreadAndLoop();
	CreateMenuFile();
	CreateMenuAbout();
	InitMainGameThread();

//	CreateHexItemInfoDialog();
//	CreateUnitTypeInfoDialog();
//	CreateCityTypeInfoDialog();
//	CreateEditorToolbox();

	QHBoxLayout *layoutMain = new QHBoxLayout;
	layoutMain->addWidget(MapViewInstance);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	MapUnitItemRepository::GetInstance()->MapViewInstance = MapViewInstance;

	ConnectorLoadCreateGameInstance->SetMapView(MapViewInstance);

	MapViewInstance->show();

	MainDialog = new QDialog(this);
	Ui::GameMainDialog* gameMainDialog = new Ui::GameMainDialog(MainDialog);
	gameMainDialog->Init(this);

	MainDialog->show();
}

GameDemonstrator::~GameDemonstrator()
{
	RepositoryCleaner::GetInstance()->ReleaseAll();
}

void GameDemonstrator::CreateGameTurnInfoDialog()
{
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
 	GameTurnDialogInstance = new GameTurnDialog(dockCountry);
 	dockCountry->setWidget( GameTurnDialogInstance );
	addDockWidget(Qt::RightDockWidgetArea, dockCountry);
	ViewMenu->addAction(dockCountry->toggleViewAction());
}

void GameDemonstrator::CreateMainGameThreadAndLoop()
{
	MainGameLoopInstance = new GameMainLoop(nullptr);
	MainThread = new GameMainThread();
	MainThread->Init(MainGameLoopInstance);
	connect(MainGameLoopInstance, &GameMainLoop::SignalTurnFinished, GameTurnDialogInstance, &GameTurnDialog::SlotUpdateGameTurnInfo);
}

void GameDemonstrator::CreateMenuFile()
{
	ConnectorLoadCreateGameInstance = new ConnectorLoadCreateGame;

	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	ActionRepository::GetInstance()->AddAction(createAction);
	connect(createAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotCreateNewGame, Qt::QueuedConnection);

	QIcon load(":GameDemonstrator/Resources/folder_document.ico");
	QAction* loadGameAction = new QAction(load,tr("&Load"), this);
	loadGameAction->setStatusTip(tr("Load current game"));
	ActionRepository::GetInstance()->AddAction( loadGameAction );
	connect(loadGameAction, &QAction::triggered, ConnectorLoadCreateGameInstance, &ConnectorLoadCreateGame::SlotLoadSaveGame, Qt::QueuedConnection);

	QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
	Action* saveGameAction = new Action(save,tr("&Save"), this);
	saveGameAction->setStatusTip(tr("Save current game"));
	ActionRepository::GetInstance()->AddAction(saveGameAction);
	connect(saveGameAction, &QAction::triggered, ConnectorSaveGameInstance, &SerializerGame::SlotSaveGame, Qt::QueuedConnection);

	QIcon next(QPixmap(".//Resources//media_end.ico"));
	QAction* nextTurnAction = new QAction(next, tr("&Next turn"), this);
	nextTurnAction->setStatusTip(tr("Next turn"));
	connect(nextTurnAction, &QAction::triggered, MainGameLoopInstance, &GameMainLoop::SlotStep, Qt::QueuedConnection);
	ActionRepository::GetInstance()->AddAction(nextTurnAction);

	QIcon start(":GameDemonstrator/Resources/media_play_green.ico");
	QAction* startTurnAction = new QAction(start,tr("&Start"), this);
	startTurnAction->setStatusTip(tr("Start turn"));
	connect(startTurnAction, &QAction::triggered, MainGameLoopInstance, &GameMainLoop::SlotStart, Qt::QueuedConnection);
	ActionRepository::GetInstance()->AddAction(startTurnAction);

	QIcon stop(":GameDemonstrator/Resources/media_stop_red.ico");
	QAction* stopTurnAction = new QAction(stop,tr("S&top"), this);
	stopTurnAction->setStatusTip(tr("Stop turn"));
	connect(stopTurnAction, &QAction::triggered, MainGameLoopInstance, &GameMainLoop::SlotPause, Qt::QueuedConnection);
	ActionRepository::GetInstance()->AddAction(stopTurnAction);

	QIcon exit(":GameDemonstrator/Resources/exit.ico");
	QAction* exitAction = new QAction(exit,tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit application"));
	connect(exitAction, &QAction::triggered, this, &GameDemonstrator::close);
	ActionRepository::GetInstance()->AddAction(exitAction);

	FileMenu->addAction( createAction );
	FileMenu->addAction( loadGameAction );
	FileMenu->addAction( saveGameAction );
	FileMenu->addSeparator();
	FileMenu->addAction( startTurnAction );
	FileMenu->addAction( stopTurnAction );
	FileMenu->addAction( nextTurnAction );
	FileMenu->addSeparator();
	FileMenu->addAction( exitAction );
}

void GameDemonstrator::InitMainGameThread()
{
	MainGameLoopInstance->moveToThread(MainThread);
	MainThread->start();
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

void GameDemonstrator::CreateMenuGameMode()
{
	//TODO: Togglebutton editor/single player
	//TODO: Dialog mit parametern (Kartengröße, Gegneranzahl, ...)
}

void GameDemonstrator::CreateHexItemInfoDialog()
{
	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), this);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
 	HexItemInfoDialogInstance = new HexItemInfoDialog(dockHexItem);
 	dockHexItem->setWidget( HexItemInfoDialogInstance );
	addDockWidget(Qt::RightDockWidgetArea, dockHexItem);
	EditorMenu->addAction(dockHexItem->toggleViewAction());
	MapViewInstance->MapEventManagerInstance->HexItemInfoDialog = HexItemInfoDialogInstance; //TODO: Sollte das hier passieren
}

void GameDemonstrator::CreateUnitTypeInfoDialog()
{
	QDockWidget *dockUnitType = new QDockWidget(tr("Unit type"), this);
	dockUnitType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	UnitTypeInfoDialogInstance = new UnitTypeInfoDialog(dockUnitType);
	dockUnitType->setWidget(UnitTypeInfoDialogInstance);
	addDockWidget(Qt::RightDockWidgetArea, dockUnitType);
	EditorMenu->addAction(dockUnitType->toggleViewAction());
	MapViewInstance->MapEventManagerInstance->UnitTypeInfoDialog = UnitTypeInfoDialogInstance; //TODO: Sollte das hier passieren
}

#include "dialogs/CityTypeInfoDialog.h"
void GameDemonstrator::CreateCityTypeInfoDialog()
{
	QDockWidget *dockCityType = new QDockWidget(tr("City type"), this);
	dockCityType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	CityTypeInfoDialogInstance = new CityTypeInfoDialog(dockCityType);
	dockCityType->setWidget(CityTypeInfoDialogInstance);
	addDockWidget(Qt::RightDockWidgetArea, dockCityType);
	EditorMenu->addAction(dockCityType->toggleViewAction());
	MapViewInstance->MapEventManagerInstance->CityTypeInfoDialog = CityTypeInfoDialogInstance; //TODO: Sollte das hier passieren
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
	jha::LogFactory::GetInstance()->RegisterLogger( new jha::LoggerTableWidget(DockWidgetLogging) );

	//TODO: Darf erst hier initialisiert werden weil die GameDemonstratorFactory selbst das logging framework verwendet!
	ModelProgramFactory modelProgramFactory;
	modelProgramFactory.Create();
	jha::GetLog()->SetGlobalLoglevel(modelProgramFactory.GetConfig()->GlobalLogLevel);
}

void GameDemonstrator::CreateEditorToolbox()
{
	QDockWidget *editorToolbox = new QDockWidget(tr("Editor Palette"), this);
	editorToolbox->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	EditorToolboxInstance = new EditorToolbox(editorToolbox);
	EditorToolboxInstance->MapViewInstance = MapViewInstance;
	EditorToolboxInstance->Create();

	editorToolbox->setWidget( EditorToolboxInstance );
	addDockWidget(Qt::LeftDockWidgetArea, editorToolbox);
	ViewMenu->addAction(editorToolbox->toggleViewAction());
}
