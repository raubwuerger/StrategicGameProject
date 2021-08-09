#include "stdafx.h"
#include "gamedemonstrator.h"
#include "ActionRepository.h"
#include "game/GameMainThread.h"
#include "game/GameMainLoop.h"
#include "dialogs/GameTurnDialog.h"
#include "dialogs/HexItemInfoDialog.h"
#include "dialogs/UnitTypeInfoDialog.h"
#include "map/MapView.h"
#include "map/MapEventManager.h"
#include "io\SerializerGame.h"
#include "io\SerializeBinary.h"
#include "io\SerializerFactory.h"
#include "Action.h"
#include "LogFactory.h"
#include "model/ModelOwnerTypeRepository.h"
#include "model/ModelTerrainTypeRepository.h"
#include "model/ModelTerrainTypeFactory.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "model/ModelUnitTypeFactory.h"
#include "model/ModelMapRepository.h"
#include "connectors/ConnectorMapHexItem.h"
#include "connectors/ConnectorTerrainEditorGameMap.h"
#include "connectors/ConnectorLoadCreateGame.h"
#include "model/ModelOwnerTypeFactory.h"
#include "editors/TerrainTypeEditor.h"
#include "editors/EditorToolbox.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	GameTurnDialogInstance(nullptr),
	MainGameLoop(nullptr),
	HexItemInfoDialogInstance(nullptr),
	UnitTypeInfoDialogInstance(nullptr),
	EditorToolboxInstance(nullptr),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr),
	ConnectorLoadCreateGameInstance(nullptr)
{
	ui.setupUi(this);

	FileMenu = menuBar()->addMenu(tr("&File"));
	ViewMenu = menuBar()->addMenu(tr("&View"));
	InfoMenu = menuBar()->addMenu(tr("&Info"));

	MapViewInstance = new MapView(this);

	ConnectorLoadCreateGameInstance = new ConnectorLoadCreateGame;

	InitLoggingFramwork();

	ActionRepository::GetInstanceFirstTimeInit(parent);
	ConnectorSaveGameInstance = SerializerFactory().CreateInterface();
	LoadTerrainTypes();
	LoadOwnerTypes();
	LoadUnitTypes();
	CreateGameTurnInfoDialog();
	CreateMainGameThreadAndLoop();
	CreateMenuFile();
	CreateHexItemInfoDialog();
	CreateUnitTypeInfoDialog();
	CreateMenuAbout();
	InitMainGameThread();

	QHBoxLayout *layoutMain = new QHBoxLayout;

	MapViewInstance->MapEventManagerInstance = new MapEventManager(nullptr);
	MapViewInstance->MapEventManagerInstance->HexItemInfoDialog = HexItemInfoDialogInstance;

	CreateEditorToolbox();
	layoutMain->addWidget(MapViewInstance);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	ConnectorLoadCreateGameInstance->SetMapView(MapViewInstance);

	MapViewInstance->show();
}

GameDemonstrator::~GameDemonstrator()
{
	ModelTerrainTypeRepository::GetInstance()->Release();
	ModelOwnerTypeRepository::GetInstance()->Release();
	ModelOwnerTypeRepository::GetInstance()->Release();
	ActionRepository::GetInstance()->Release();
	ModelMapRepository::GetInstance()->Release();
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
	MainGameLoop = new GameMainLoop(nullptr);
	MainThread = new GameMainThread();
	MainThread->Init( MainGameLoop );
	connect( MainGameLoop, SIGNAL(TurnFinished(QDate)),GameTurnDialogInstance, SLOT(UpdateGameTurnInfo(QDate)) );
}

void GameDemonstrator::CreateMenuFile()
{
	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	ActionRepository::GetInstance()->AddAction(createAction);
	connect(createAction, SIGNAL(triggered()), ConnectorLoadCreateGameInstance, SLOT(CreateNewGame()), Qt::QueuedConnection);

	QIcon load(":GameDemonstrator/Resources/folder_document.ico");
	QAction* loadGameAction = new QAction(load,tr("&Load"), this);
	loadGameAction->setStatusTip(tr("Load current game"));
	ActionRepository::GetInstance()->AddAction( loadGameAction );
	connect(loadGameAction, SIGNAL(triggered()), ConnectorLoadCreateGameInstance, SLOT(LoadSaveGame()), Qt::QueuedConnection);

	QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
	Action* saveGameAction = new Action(save,tr("&Save"), this);
	saveGameAction->setStatusTip(tr("Save current game"));
	ActionRepository::GetInstance()->AddAction(saveGameAction);
	connect(saveGameAction, SIGNAL(triggered()),ConnectorSaveGameInstance,SLOT(SaveGame()), Qt::QueuedConnection );

	QIcon next(":GameDemonstrator/Resources/media_end.ico");
	QAction* nextTurnAction = new QAction(next,tr("&Next turn"), this);
	nextTurnAction->setStatusTip(tr("Next turn"));
	connect(nextTurnAction, SIGNAL(triggered()), MainGameLoop, SLOT(Step()), Qt::QueuedConnection );
	ActionRepository::GetInstance()->AddAction(nextTurnAction);

	QIcon start(":GameDemonstrator/Resources/media_play_green.ico");
	QAction* startTurnAction = new QAction(start,tr("&Start"), this);
	startTurnAction->setStatusTip(tr("Start turn"));
	connect(startTurnAction, SIGNAL(triggered()), MainGameLoop, SLOT(Start()), Qt::QueuedConnection );
	ActionRepository::GetInstance()->AddAction(startTurnAction);

	QIcon stop(":GameDemonstrator/Resources/media_stop_red.ico");
	QAction* stopTurnAction = new QAction(stop,tr("S&top"), this);
	stopTurnAction->setStatusTip(tr("Stop turn"));
	connect(stopTurnAction, &QAction::triggered, MainGameLoop, &GameMainLoop::Pause, Qt::QueuedConnection);
	ActionRepository::GetInstance()->AddAction(stopTurnAction);

	QIcon exit(":GameDemonstrator/Resources/exit.ico");
	QAction* exitAction = new QAction(exit,tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
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
	MainGameLoop->moveToThread(MainThread);
	MainThread->start();
}

void GameDemonstrator::CreateMenuAbout()
{
	QIcon info(":GameDemonstrator/Resources/about.ico");
	QAction* aboutAction = new QAction(info,tr("&About"), this);
	aboutAction->setStatusTip(tr("Info about application"));
//	connect(aboutAction, SIGNAL(triggered()), aboutAction, SLOT(show()));
	ActionRepository::GetInstance()->AddAction(aboutAction);

	InfoMenu->addAction( aboutAction );
}

void GameDemonstrator::CreateHexItemInfoDialog()
{
	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), this);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
 	HexItemInfoDialogInstance = new HexItemInfoDialog(dockHexItem);
 	dockHexItem->setWidget( HexItemInfoDialogInstance );
	addDockWidget(Qt::RightDockWidgetArea, dockHexItem);
	ViewMenu->addAction(dockHexItem->toggleViewAction());
}

void GameDemonstrator::CreateUnitTypeInfoDialog()
{
	QDockWidget *dockUnitType = new QDockWidget(tr("Unit type"), this);
	dockUnitType->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	UnitTypeInfoDialogInstance = new UnitTypeInfoDialog(dockUnitType);
	dockUnitType->setWidget(UnitTypeInfoDialogInstance);
	addDockWidget(Qt::RightDockWidgetArea, dockUnitType);
	ViewMenu->addAction(dockUnitType->toggleViewAction());
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

bool GameDemonstrator::LoadTerrainTypes()
{
	ModelTerrainTypeFactory factory;
	return factory.Create();
}

bool GameDemonstrator::LoadOwnerTypes()
{
	ModelOwnerTypeFactory factory;
	return factory.Create();
}

bool GameDemonstrator::LoadUnitTypes()
{
	ModelUnitTypeFactory factory;
	return factory.Create();
}

void GameDemonstrator::CreateEditorToolbox()
{
	QDockWidget *dockCountry = new QDockWidget(tr("Editor Palette"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	EditorToolboxInstance = new EditorToolbox(dockCountry);
	EditorToolboxInstance->ConnectorMapHexItemInstance = MapViewInstance->GetConnectorMapHexItem();
	EditorToolboxInstance->MapEventManagerInstance = MapViewInstance->MapEventManagerInstance;

	EditorToolboxInstance->Create();

	dockCountry->setWidget( EditorToolboxInstance );
	addDockWidget(Qt::LeftDockWidgetArea, dockCountry);
	ViewMenu->addAction(dockCountry->toggleViewAction());
}
