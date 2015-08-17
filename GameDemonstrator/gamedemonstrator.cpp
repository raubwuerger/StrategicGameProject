#include "stdafx.h"
#include "gamedemonstrator.h"
#include "QActionRepository.h"
#include "GameMainThread.h"
#include "GameMainLoop.h"
#include "GameTurnDialog.h"
#include "MapView.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	m_GameTurnDialog(nullptr),
	m_MainGameLoop(nullptr),
	m_HexItemInfoDialog(nullptr),
	m_TerrainTypeRepository(nullptr)
{
	ui.setupUi(this);

	m_ActionRepository = new QActionRepository(parent);
	CreateGameTurnInfoDialog();
	CreateHexItemInfoDialog();
	CreateMainGameThreadAndLoop();
	CreateMenuFile();
	CreateMenuAbout();
	InitMainGameThread();
	InitLoggingFramwork();
	LoadTerrainTypes();

	QHBoxLayout *layoutMain = new QHBoxLayout;
	MapView *mapView = new MapView(this);

	mapView->m_HexItemEventManager = new HexItemEventManager;
	mapView->m_MapEventManager = new MapEventManager(nullptr);
	mapView->m_MapEventManager->m_HexItemInfoDialog = m_HexItemInfoDialog;
	mapView->Init();


	layoutMain->addWidget(mapView);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);
	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	mapView->show();
}

GameDemonstrator::~GameDemonstrator()
{
	delete m_ActionRepository;
	delete m_TerrainTypeRepository;
}

void GameDemonstrator::CreateGameTurnInfoDialog()
{
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_GameTurnDialog = new GameTurnDialog(dockCountry);
	dockCountry->setWidget( m_GameTurnDialog );
	addDockWidget(Qt::RightDockWidgetArea, dockCountry);
	m_GameTurnDialog->addAction(dockCountry->toggleViewAction());
}

void GameDemonstrator::CreateMainGameThreadAndLoop()
{
	m_MainGameLoop = new GameMainLoop(nullptr);
	m_MainThread = new GameMainThread();
	m_MainThread->Init( m_MainGameLoop );
	connect( m_MainGameLoop, SIGNAL(TurnFinished(QDate)),m_GameTurnDialog, SLOT(UpdateGameTurnInfo(QDate)) );
}

#include "CreateNewMap.h"
void GameDemonstrator::CreateMenuFile()
{
	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	connect(createAction, SIGNAL(triggered()), new CreateNewMap(this), SLOT(DoCreateNewMap()), Qt::QueuedConnection );
	m_ActionRepository->AddAction(createAction);

	QIcon load(":GameDemonstrator/Resources/folder_document.ico");
	QAction* loadGameAction = new QAction(load,tr("&Load"), this);
	loadGameAction->setStatusTip(tr("Load current game"));
	connect(loadGameAction, SIGNAL(triggered()), m_MainGameLoop, SLOT(Start()), Qt::QueuedConnection );
	m_ActionRepository->AddAction(loadGameAction);

	QIcon save(":GameDemonstrator/Resources/floppy_disk_blue.ico");
	QAction* saveGameAction = new QAction(save,tr("&Save"), this);
	saveGameAction->setStatusTip(tr("Save current game"));
	connect(saveGameAction, SIGNAL(triggered()), m_MainGameLoop, SLOT(Start()), Qt::QueuedConnection );
	m_ActionRepository->AddAction(saveGameAction);

	QIcon start(":GameDemonstrator/Resources/media_play_green.ico");
	QAction* startTurnAction = new QAction(start,tr("&Start"), this);
	startTurnAction->setStatusTip(tr("Start turn"));
	connect(startTurnAction, SIGNAL(triggered()), m_MainGameLoop, SLOT(Start()), Qt::QueuedConnection );
	m_ActionRepository->AddAction(startTurnAction);

	QIcon stop(":GameDemonstrator/Resources/media_stop_red.ico");
	QAction* stopTurnAction = new QAction(stop,tr("S&top"), this);
	stopTurnAction->setStatusTip(tr("Stop turn"));
	connect(stopTurnAction, &QAction::triggered, m_MainGameLoop, &GameMainLoop::Pause, Qt::QueuedConnection);
	m_ActionRepository->AddAction(stopTurnAction);

	QIcon exit(":GameDemonstrator/Resources/exit.ico");
	QAction* exitAction = new QAction(exit,tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	m_ActionRepository->AddAction(exitAction);

	m_FileMenu = menuBar()->addMenu(tr("&File"));
	m_FileMenu->addAction( createAction );
	m_FileMenu->addAction( loadGameAction );
	m_FileMenu->addAction( saveGameAction );
	m_FileMenu->addSeparator();
	m_FileMenu->addAction( startTurnAction );
	m_FileMenu->addAction( stopTurnAction );
	m_FileMenu->addSeparator();
	m_FileMenu->addAction( exitAction );
}

void GameDemonstrator::InitMainGameThread()
{
	m_MainGameLoop->moveToThread(m_MainThread);
	m_MainThread->start();
}

void GameDemonstrator::CreateMenuAbout()
{
	QIcon info(":GameDemonstrator/Resources/about.ico");
	QAction* aboutAction = new QAction(info,tr("&About"), this);
	aboutAction->setStatusTip(tr("Info about application"));
//	connect(aboutAction, SIGNAL(triggered()), this, SLOT(close()));
	m_ActionRepository->AddAction(aboutAction);

	m_FileMenu = menuBar()->addMenu(tr("&Info"));
	m_FileMenu->addAction( aboutAction );
}

#include "HexItemInfoDialog.h"
void GameDemonstrator::CreateHexItemInfoDialog()
{
	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), this);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_HexItemInfoDialog = new HexItemInfoDialog(dockHexItem);
	dockHexItem->setWidget( m_HexItemInfoDialog );
	addDockWidget(Qt::RightDockWidgetArea, dockHexItem);
	m_HexItemInfoDialog->addAction(dockHexItem->toggleViewAction());
}

#include "LogInterface.h"
#include "LoggingTableWidget.h"
#include "LoggerFile.h"
#include "LoggerTableWidget.h"
void GameDemonstrator::InitLoggingFramwork()
{
	QDockWidget *dockWidget = new QDockWidget(tr("Logging"), this);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea );
	m_DockWidgetLogging = new jha::LoggingTableWidget(0,0,dockWidget);

	dockWidget->setWidget( m_DockWidgetLogging );
	addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
	m_FileMenu->addAction(dockWidget->toggleViewAction());


	jha::LogInterface().Init();
	jha::GetLog()->RegisterLogger( new jha::LoggerFile("./log/Logfile.log") );
	jha::GetLog()->RegisterLogger( new jha::LoggerTableWidget(m_DockWidgetLogging) );
	jha::GetLog()->Start();
}

#include "TerrainTypeFactory.h"
#include <QDomDocument>
#include "TerrainTypeRepository.h"
bool GameDemonstrator::LoadTerrainTypes()
{
	jha::GetLog()->Log("Loading TerrainTypes.xml ...", LEVEL::LL_MESSAGE);
	m_TerrainTypeRepository = new CTerrainTypeRepository;
	QString fileName(".\\conf\\TerrainTypes.xml");

	QFile file(fileName);
	if( file.open(QFile::ReadOnly | QFile::Text) == false )
	{
		QMessageBox::warning(this, tr("SAX Bookmarks"),
			tr("Cannot read file %1:\n%2.")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument domDocument;

	if( domDocument.setContent(&file, true, &errorStr, &errorLine,&errorColumn) == false ) 
	{
		QMessageBox::information(window(), tr("DOM Bookmarks"),
			tr("Parse error at line %1, column %2:\n%3")
			.arg(errorLine)
			.arg(errorColumn)
			.arg(errorStr));
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
		m_TerrainTypeRepository->RegisterTerrainType( CTerrainTypeFactory().CreateTerrainTypeFromXML( terrainTypeNodes.at(i) ) );
	}
	jha::GetLog()->Log("TerrainTypes registered: " +QString::number(m_TerrainTypeRepository->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}
