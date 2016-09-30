#include "stdafx.h"
#include "gamedemonstrator.h"
#include "QActionRepository.h"
#include "GameMainThread.h"
#include "GameMainLoop.h"
#include "GameTurnDialog.h"
#include "MapView.h"
#include "MapViewHexItem.h"
#include "MapEventManager.h"
#include "TerrainTypeEditor.h"
#include "OwnerTypeRepository.h"

GameDemonstrator::GameDemonstrator(QWidget *parent)
	: QMainWindow(parent),
	m_GameTurnDialog(nullptr),
	m_MainGameLoop(nullptr),
	m_HexItemInfoDialog(nullptr),
	m_TerrainTypeRepository(nullptr),
	m_OwnerTypeRepository(nullptr),
	m_EditorToolbox(nullptr),
	m_FileMenu(nullptr),
	m_ViewMenu(nullptr),
	m_InfoMenu(nullptr)
{
	ui.setupUi(this);

	m_ActionRepository = new QActionRepository(parent);
	m_FileMenu = menuBar()->addMenu(tr("&File"));
	m_ViewMenu = menuBar()->addMenu(tr("&View"));
	m_InfoMenu = menuBar()->addMenu(tr("&Info"));

	mapView = new MapView(this);

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

	mapView->HexItemEventManager = new HexItemEventManager;
	mapView->MapEventManager = new CMapEventManager(nullptr);
	mapView->MapEventManager->HexItemInfoDialog = m_HexItemInfoDialog;

	CTerrainTypeEditor *terrainTypeEditor = CreateTerrainTypeEditor( m_TerrainTypeRepository, mapView->MapEventManager );
	CreateEditorToolbox( m_TerrainTypeRepository, terrainTypeEditor );

	connect( mapView->HexItemEventManager, SIGNAL(HexItemPressed(int,int)), terrainTypeEditor, SLOT(ChangeTerrainTypeHexItem(int,int)) );

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
	delete m_OwnerTypeRepository;
}

void GameDemonstrator::CreateGameTurnInfoDialog()
{
	QDockWidget *dockCountry = new QDockWidget(tr("Game turn"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_GameTurnDialog = new GameTurnDialog(dockCountry);
	dockCountry->setWidget( m_GameTurnDialog );
	addDockWidget(Qt::RightDockWidgetArea, dockCountry);
	m_ViewMenu->addAction(dockCountry->toggleViewAction());
}

void GameDemonstrator::CreateMainGameThreadAndLoop()
{
	m_MainGameLoop = new GameMainLoop(nullptr);
	m_MainThread = new GameMainThread();
	m_MainThread->Init( m_MainGameLoop );
	connect( m_MainGameLoop, SIGNAL(TurnFinished(QDate)),m_GameTurnDialog, SLOT(UpdateGameTurnInfo(QDate)) );
}

#include "MapFactory.h"
#include "CreateNewMap.h" //connect kann sonst den Typ nicht auf QObject auflösen ...
#include "TerrainTypeRepository.h"
void GameDemonstrator::CreateMenuFile()
{
	QIcon create(":GameDemonstrator/Resources/gear_run.ico");
	QAction* createAction = new QAction(create,tr("&Create"), this);
	createAction->setStatusTip(tr("Create new game"));
	CMapFactory().CreateNewMapAction(this,createAction,mapView,m_TerrainTypeRepository->GetDefaultTerrainType());
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

	m_InfoMenu->addAction( aboutAction );
}

#include "HexItemInfoDialog.h"
void GameDemonstrator::CreateHexItemInfoDialog()
{
	QDockWidget *dockHexItem = new QDockWidget(tr("Hex item"), this);
	dockHexItem->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	m_HexItemInfoDialog = new HexItemInfoDialog(dockHexItem);
	dockHexItem->setWidget( m_HexItemInfoDialog );
	addDockWidget(Qt::RightDockWidgetArea, dockHexItem);
	m_ViewMenu->addAction(dockHexItem->toggleViewAction());
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
	m_ViewMenu->addAction(dockWidget->toggleViewAction());


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
	m_TerrainTypeRepository = new CTerrainTypeRepository;

	jha::GetLog()->Log("Loading TerrainTypes.xml ...", LEVEL::LL_MESSAGE);
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
	m_TerrainTypeRepository->SetDefaultTerrainType( m_TerrainTypeRepository->FindTerrainTypeById(1) );
	jha::GetLog()->Log("TerrainTypes registered: " +QString::number(m_TerrainTypeRepository->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}

#include "OwnerTypeFactory.h"
#include "OwnerTypeRepository.h"
bool GameDemonstrator::LoadOwnerTypes()
{
	m_OwnerTypeRepository = new COwnerTypeRepository;

	jha::GetLog()->Log("Loading OwnerTypes.xml ...", LEVEL::LL_MESSAGE);
	QString fileName(".\\conf\\OwnerTypes.xml");

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
		m_OwnerTypeRepository->RegisterOwnerType( COwnerTypeFactory().CreateOwnerTypeFromXML( ownerTypeNodes.at(i) ) );
	}
	m_OwnerTypeRepository->SetDefaultOwnerType( m_OwnerTypeRepository->FindOwnerTypeById(1) );
	jha::GetLog()->Log("OwnerTypes registered: " +QString::number(m_OwnerTypeRepository->GetCount()), LEVEL::LL_MESSAGE);
	return true;
}

#include "TerrainType.h"
#include "TerrainTypeRepository.h"
#include "EditorToolbox.h"
void GameDemonstrator::CreateEditorToolbox( CTerrainTypeRepository *repository, CTerrainTypeEditor *terrainTypeEditor )
{
	QDockWidget *dockCountry = new QDockWidget(tr("Editor Palette"), this);
	dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	m_EditorToolbox = new CEditorToolbox(dockCountry);
	m_EditorToolbox->TerrainTypeEditor = terrainTypeEditor;
	m_EditorToolbox->Create(repository);
//	m_EditorToolbox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));

	dockCountry->setWidget( m_EditorToolbox );
	addDockWidget(Qt::LeftDockWidgetArea, dockCountry);
	m_ViewMenu->addAction(dockCountry->toggleViewAction());
}

#include "TerrainTypeEditor.h"
CTerrainTypeEditor* GameDemonstrator::CreateTerrainTypeEditor( CTerrainTypeRepository *terrainTypeRepository, CMapEventManager*mapEventManager )
{
	CTerrainTypeEditor *terrainTypeEditor = new CTerrainTypeEditor(nullptr);
	terrainTypeEditor->TerrainTypeRepository = terrainTypeRepository;
	terrainTypeEditor->MapEventManager = mapEventManager;
	return terrainTypeEditor;
}
