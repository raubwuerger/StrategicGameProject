#include "stdafx.h"
#include "gamedemonstrator.h"
#include "QActionRepository.h"
#include "GameMainThread.h"
#include "GameMainLoop.h"
#include "GameTurnDialog.h"
#include "MapView.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"
#include "HexItemEventManager.h"
#include "TerrainTypeEditor.h"
#include "OwnerTypeRepository.h"
#include "HexItemInfoDialog.h"
#include "SerializerInterface.h"
#include "SaveBinary.h"
#include "SerializerFactory.h"
#include "Action.h"
#include "LogFactory.h"
#include "TerrainTypeRepository.h"
#include "MapFactory.h"
#include "GameFactory.h"
#include "CreateNewMap.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	GameTurnDialogInstance(nullptr),
	MainGameLoop(nullptr),
	HexItemInfoDialogInstance(nullptr),
	OwnerTypeRepository(nullptr),
	EditorToolboxInstance(nullptr),
	FileMenu(nullptr),
	ViewMenu(nullptr),
	InfoMenu(nullptr),
	CreateNewMapInstance(nullptr)
{
	ui.setupUi(this);

	FileMenu = menuBar()->addMenu(tr("&File"));
	ViewMenu = menuBar()->addMenu(tr("&View"));
	InfoMenu = menuBar()->addMenu(tr("&Info"));

	CreateNewMapInstance = new CreateNewMap(this);

	MapViewInstance = new MapView(this);
	MapFactory::GetInstance()->SetMapView(MapViewInstance);
	MapFactory::GetInstance()->SetParent(this);

	QActionRepository::GetInstanceFirstTimeInit(parent);
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
	TerrainTypeRepository::GetInstance()->Release();
	QActionRepository::GetInstance()->Release();
	OwnerTypeRepository::GetInstance()->Release();
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

#include "TerrainTypeRepository.h"
void GameDemonstrator::CreateMenuFile()
{
	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	QActionRepository::GetInstance()->AddAction(createAction);
	connect(createAction,SIGNAL(triggered()),CreateNewMapInstance, SLOT(DoCreateNewMap()), Qt::QueuedConnection );

	QIcon load(":GameDemonstrator/Resources/folder_document.ico");
	QAction* loadGameAction = new QAction(load,tr("&Load"), this);
	loadGameAction->setStatusTip(tr("Load current game"));
	QActionRepository::GetInstance()->AddAction( loadGameAction );
	connect(loadGameAction, SIGNAL(triggered()),SerializerInterface,SLOT(LoadGame()), Qt::QueuedConnection );

	QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
	Action* saveGameAction = new Action(save,tr("&Save"), this);
	saveGameAction->setStatusTip(tr("Save current game"));
	QActionRepository::GetInstance()->AddAction(saveGameAction);
	connect(saveGameAction, SIGNAL(triggered()),SerializerInterface,SLOT(SaveGame()), Qt::QueuedConnection );

	QIcon start(":GameDemonstrator/Resources/media_play_green.ico");
	QAction* startTurnAction = new QAction(start,tr("&Start"), this);
	startTurnAction->setStatusTip(tr("Start turn"));
	connect(startTurnAction, SIGNAL(triggered()), MainGameLoop, SLOT(Start()), Qt::QueuedConnection );
	QActionRepository::GetInstance()->AddAction(startTurnAction);

	QIcon stop(":GameDemonstrator/Resources/media_stop_red.ico");
	QAction* stopTurnAction = new QAction(stop,tr("S&top"), this);
	stopTurnAction->setStatusTip(tr("Stop turn"));
	connect(stopTurnAction, &QAction::triggered, MainGameLoop, &GameMainLoop::Pause, Qt::QueuedConnection);
	QActionRepository::GetInstance()->AddAction(stopTurnAction);

	QIcon exit(":GameDemonstrator/Resources/exit.ico");
	QAction* exitAction = new QAction(exit,tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	QActionRepository::GetInstance()->AddAction(exitAction);

	FileMenu->addAction( createAction );
	FileMenu->addAction( loadGameAction );
	FileMenu->addAction( saveGameAction );
	FileMenu->addSeparator();
	FileMenu->addAction( startTurnAction );
	FileMenu->addAction( stopTurnAction );
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
	QActionRepository::GetInstance()->AddAction(aboutAction);

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
}

#include "TerrainTypeFactory.h"
#include <QDomDocument>
bool GameDemonstrator::LoadTerrainTypes()
{
	jha::GetLog()->Log("Loading TerrainTypes.xml ...", LEVEL::LL_MESSAGE);
	QString fileName(".\\conf\\TerrainTypes.xml");

	QFile file(fileName);
	if( file.open(QFile::ReadOnly | QFile::Text) == false )
	{
		QMessageBox::warning(this, tr("SAX Bookmarks"), tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;

	if( domDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"),tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if( root.tagName() != "TerrainTypes") 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"), tr("The file is not an TerrainTypes file."));
		return false;
	}

	if (root.hasAttribute("version") && root.attribute("version") != "1.0") 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"), tr("The file is not an TerrainTypes version 1.0 file."));
		return false;
	}

	QDomNodeList terrainTypeNodes = root.childNodes();
	for( int i=0; i <terrainTypeNodes.count(); i++ )
	{
		TerrainTypeRepository::GetInstance()->RegisterTerrainType( TerrainTypeFactory().CreateTerrainTypeFromXML( terrainTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("TerrainTypes registered: " +QString::number(TerrainTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}

#include "ModelOwnerTypeFactory.h"
#include "OwnerTypeRepository.h"
bool GameDemonstrator::LoadOwnerTypes()
{
	jha::GetLog()->Log("Loading OwnerTypes.xml ...", LEVEL::LL_MESSAGE);
	QString fileName(".\\conf\\OwnerTypes.xml");

	QFile file(fileName);
	if( file.open(QFile::ReadOnly | QFile::Text) == false )
	{
		QMessageBox::warning(this, tr("SAX Bookmarks"),	tr("Cannot read file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;

	if( domDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"),	tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr));
		return false;
	}

	QDomElement root = domDocument.documentElement();
	if( root.tagName() != "OwnerTypes") 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"), tr("The file is not an OwnerTypes file."));
		return false;
	}

	if (root.hasAttribute("version") && root.attribute("version") != "1.0") 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"), tr("The file is not an OwnerTypes version 1.0 file."));
		return false;
	}

	QDomNodeList ownerTypeNodes = root.childNodes();
	for( int i=0; i <ownerTypeNodes.count(); i++ )
	{
		OwnerTypeRepository::GetInstance()->RegisterOwnerType( ModelOwnerTypeFactory().CreateOwnerTypeFromXML( ownerTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("OwnerTypes registered: " +QString::number(OwnerTypeRepository::GetInstance()->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}

#include "TerrainType.h"
#include "TerrainTypeRepository.h"
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
	return terrainTypeEditor;
}
