#include "stdafx.h"
#include "gamedemonstrator.h"
#include "ActionRepository.h"
#include "game/GameMainThread.h"
#include "game/GameMainLoop.h"
#include "GameTurnDialog.h"
#include "MapView.h"
#include "MapEventManager.h"
#include "HexItemEventManager.h"
#include "TerrainTypeEditor.h"
#include "model/ModelOwnerTypeRepository.h"
#include "HexItemInfoDialog.h"
#include "SerializerInterface.h"
#include "SerializeBinary.h"
#include "SerializerFactory.h"
#include "Action.h"
#include "LogFactory.h"
#include "model/ModelTerrainTypeRepository.h"
#include "game/GameFactory.h"
#include "model/ModelProgramFactory.h"
#include "model/ModelProgramSettings.h"
#include "connectors/ConnectorEditorModelRepository.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	GameTurnDialogInstance(nullptr),
	MainGameLoop(nullptr),
	HexItemInfoDialogInstance(nullptr),
	EditorToolboxInstance(nullptr),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr)
{
	ui.setupUi(this);

	ConnectorEditorModelRepositoryInstance = new ConnectorEditorModelRepository();

	FileMenu = menuBar()->addMenu(tr("&File"));
	ViewMenu = menuBar()->addMenu(tr("&View"));
	InfoMenu = menuBar()->addMenu(tr("&Info"));



	MapViewInstance = new MapView(this);

	ActionRepository::GetInstanceFirstTimeInit(parent);
	SerializerInterface = SerializerFactory().CreateInterface();
	InitLoggingFramwork();
	LoadTerrainTypes();
	LoadOwnerTypes();
	CreateGameTurnInfoDialog();
	CreateMainGameThreadAndLoop();
	CreateMenuFile();
	CreateHexItemInfoDialog();
	CreateMenuAbout();
	InitMainGameThread();

	QHBoxLayout *layoutMain = new QHBoxLayout;

	MapViewInstance->HexItemEventManager = new HexItemEventManager;
	MapViewInstance->MapEventManager = new MapEventManager(nullptr);
	MapViewInstance->MapEventManager->HexItemInfoDialog = HexItemInfoDialogInstance;

	TerrainTypeEditor *terrainTypeEditor = CreateTerrainTypeEditor( MapViewInstance->MapEventManager );
	CreateEditorToolbox( terrainTypeEditor );

	connect( MapViewInstance->HexItemEventManager, SIGNAL(HexItemPressed(int,int)), terrainTypeEditor, SLOT(ChangeTerrainTypeHexItem(int,int)) );

	layoutMain->addWidget(MapViewInstance);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	GameFactory::GetInstance()->SetMapView(MapViewInstance);

	MapViewInstance->show();
}

GameDemonstrator::~GameDemonstrator()
{
	ModelTerrainTypeRepository::GetInstance()->Release();
	ActionRepository::GetInstance()->Release();
	ModelOwnerTypeRepository::GetInstance()->Release();
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

#include "model/ModelTerrainTypeRepository.h"
void GameDemonstrator::CreateMenuFile()
{
	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	ActionRepository::GetInstance()->AddAction(createAction);
	connect(createAction,SIGNAL(triggered()),GameFactory::GetInstance(), SLOT(CreateNewGame()), Qt::QueuedConnection );

	QIcon load(":GameDemonstrator/Resources/folder_document.ico");
	QAction* loadGameAction = new QAction(load,tr("&Load"), this);
	loadGameAction->setStatusTip(tr("Load current game"));
	ActionRepository::GetInstance()->AddAction( loadGameAction );
	connect(loadGameAction, SIGNAL(triggered()),GameFactory::GetInstance(),SLOT(LoadSaveGame()), Qt::QueuedConnection );

	QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
	Action* saveGameAction = new Action(save,tr("&Save"), this);
	saveGameAction->setStatusTip(tr("Save current game"));
	ActionRepository::GetInstance()->AddAction(saveGameAction);
	connect(saveGameAction, SIGNAL(triggered()),SerializerInterface,SLOT(SaveGame()), Qt::QueuedConnection );

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
	ModelProgramFactory::GetInstance()->Create();
	jha::GetLog()->SetGlobalLoglevel(ModelProgramFactory::GetInstance()->GetConfig()->GlobalLogLevel);
}

#include "model/ModelTerrainTypeFactory.h"
bool GameDemonstrator::LoadTerrainTypes()
{
	return ModelTerrainTypeFactory::GetInstance()->Create();
}

#include "model/ModelOwnerTypeFactory.h"
bool GameDemonstrator::LoadOwnerTypes()
{
	return ModelOwnerTypeFactory::GetInstance()->Create();
}

#include "model/ModelTerrainType.h"
#include "model/ModelTerrainTypeRepository.h"
#include "EditorToolbox.h"
void GameDemonstrator::CreateEditorToolbox( TerrainTypeEditor *terrainTypeEditor )
{
	QDockWidget *dockCountry = new QDockWidget(tr("Editor Palette"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	EditorToolboxInstance = new EditorToolbox(dockCountry);
	EditorToolboxInstance->TerrainTypeEditor = terrainTypeEditor;
	EditorToolboxInstance->Create();

	dockCountry->setWidget( EditorToolboxInstance );
	addDockWidget(Qt::LeftDockWidgetArea, dockCountry);
	ViewMenu->addAction(dockCountry->toggleViewAction());

}

#include "TerrainTypeEditor.h"
TerrainTypeEditor* GameDemonstrator::CreateTerrainTypeEditor( MapEventManager*mapEventManager )
{
	TerrainTypeEditor *terrainTypeEditor = new TerrainTypeEditor(nullptr);
	terrainTypeEditor->MapEventManager = mapEventManager;
	QObject::connect(terrainTypeEditor, &TerrainTypeEditor::TerrainTypeChanged,
		ConnectorEditorModelRepositoryInstance, &ConnectorEditorModelRepository::TerrainTypeChanged);
	return terrainTypeEditor;
}
