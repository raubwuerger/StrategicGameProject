#include "stdafx.h"
#include "gamedemonstrator.h"
#include "ActionRepository.h"
#include "Action.h"
#include "LogFactory.h"
#include "ConfigurationLoader.h"
#include "gameController/GameMainLoop.h"
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
#include "map/MapCityItemRepository.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	GameTurnDialogInstance(nullptr),
	MainGameLoopInstance(nullptr),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr),
	GameModeControllerObject(nullptr),
	ConnectorLoadCreateGameInstance(nullptr),
	GameMainDialogObject(nullptr)
{
	ui.setupUi(this);

	FileMenu = menuBar()->addMenu(tr("&File"));
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
	MainGameLoopInstance = new GameMainLoop(this);
	CreateMenuFile();
	CreateMenuAbout();

	QHBoxLayout *layoutMain = new QHBoxLayout;
	layoutMain->addWidget(MapViewInstance);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	MapUnitItemRepository::GetInstance()->MapViewInstance = MapViewInstance;
	MapCityItemRepository::GetInstance()->MapViewInstance = MapViewInstance;

	ConnectorLoadCreateGameInstance->SetMapView(MapViewInstance);

	MapViewInstance->show();

	QDialog* dialog = new QDialog(this);
	GameMainDialogObject = new GameMainDialog(dialog);
	GameMainDialogObject->Init(this);
	dialog->show();

	CreateGameModeController();
}

GameDemonstrator::~GameDemonstrator()
{
	RepositoryCleaner::GetInstance()->ReleaseAll();
}

#include "gameController/GameModeController.h"
void GameDemonstrator::CreateGameModeController()
{
	GameModeControllerObject = new GameModeController;
	GameModeControllerObject->MapViewObject = MapViewInstance;
	GameModeControllerObject->GameMainDialogObject = GameMainDialogObject;
	GameModeControllerObject->Init(this);
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
	FileMenu->addAction( nextTurnAction );
	FileMenu->addSeparator();
	FileMenu->addAction( exitAction );
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
	jha::LogFactory::GetInstance()->RegisterLogger( new jha::LoggerTableWidget(DockWidgetLogging) );

	//TODO: Darf erst hier initialisiert werden weil die GameDemonstratorFactory selbst das logging framework verwendet!
	ModelProgramFactory modelProgramFactory;
	modelProgramFactory.Create();
	jha::GetLog()->SetGlobalLoglevel(modelProgramFactory.GetConfig()->GlobalLogLevel);
}
