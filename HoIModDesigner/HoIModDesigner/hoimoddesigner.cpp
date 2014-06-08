#include "stdafx.h"
#include "hoimoddesigner.h"
#include "PolygonHelper.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "ProvinceItem.h"
#include "ExtendedGraphicsView.h"
#include "ExtendedGraphicsScene.h"
#include "Nation.h"
#include "std/LogInterface.h"
#include "std/LoggerFile.h"
#include "std/LoggerTableWidget.h"
#include "ParserHoI3.h"
#include "HoI3Context.h"


#include <DDSLoader.h>

HoIModDesigner::HoIModDesigner(QWidget *parent)
	: QMainWindow(parent),
	m_DockWidgetNationList(nullptr),
	m_DockWidgetNationDetails(nullptr)
{
	ui.setupUi(this);

	QIcon recycle(":HoIModDesigner/images/exit.ico");
	QList<QSize> sizes = recycle.availableSizes();

	m_ExitAction = new QAction(recycle,tr("E&xit"), this);
	m_ExitAction->setShortcuts(QKeySequence::Quit);
	m_ExitAction->setStatusTip(tr("Quit Scenediagram example"));
	connect(m_ExitAction, SIGNAL(triggered()), this, SLOT(close()));

	m_LoadMapAction = new QAction(QIcon(":HoIModDesigner/images/folder_document.ico"),tr("Load"),this );
	m_LoadMapAction->setStatusTip(tr("Load HoI3 map"));
	connect(m_LoadMapAction, SIGNAL(triggered()), this, SLOT(LoadMap()));

	m_AboutAction = new QAction(QIcon(":HoIModDesigner/images/about.ico"),tr("About"),this );
	m_AboutAction->setStatusTip(tr("Show about dialog"));
//	connect(m_AboutAction, SIGNAL(triggered()), this, SLOT(About()));

	m_FileMenu = menuBar()->addMenu(tr("&File"));
	m_FileMenu->addAction( m_LoadMapAction );
	m_FileMenu->addSeparator();
	m_FileMenu->addAction( m_ExitAction );

	m_DockWidgetsMenu = menuBar()->addMenu("Windows");

	m_HilfeMenu = menuBar()->addMenu(tr("Help"));
	m_HilfeMenu->addAction( m_AboutAction );

	m_FileToolBar = addToolBar(tr("Edit"));
	m_FileToolBar->addAction(m_ExitAction);
	m_FileToolBar->addAction(m_LoadMapAction);

	m_ShowOriginalMap = new QAction(recycle,tr("Original"), this);
	m_ShowOriginalMap->setStatusTip(tr("Shows original map"));
	connect(m_ShowOriginalMap, SIGNAL(triggered()), this, SLOT(ShowOriginalMap()));

	m_ShowNationColorMap = new QAction(recycle,tr("Nations"), this);
	m_ShowNationColorMap->setStatusTip(tr("Shows map by country colors"));
	connect(m_ShowNationColorMap, SIGNAL(triggered()), this, SLOT(ShowNationColorMap()));

	m_ShowMetalProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_metal.ico"),tr("Metal"), this);
	m_ShowMetalProvinces->setStatusTip(tr("Shows only provinces with metal"));
	connect(m_ShowMetalProvinces, SIGNAL(triggered()), this, SLOT(FilterMapMetal()));

	m_ShowOilProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_oil.ico"),tr("Crude oil"), this);
	m_ShowOilProvinces->setStatusTip(tr("Shows only provinces with crude oil"));
	connect(m_ShowOilProvinces, SIGNAL(triggered()), this, SLOT(FilterMapCrudeOil()));

	m_ShowEnergyProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_energy.ico"),tr("Energy"), this);
	m_ShowEnergyProvinces->setStatusTip(tr("Shows only provinces with energy"));
	connect(m_ShowEnergyProvinces, SIGNAL(triggered()), this, SLOT(FilterMapEnergy()));

	m_ShowRareProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_raremat.ico"),tr("Rare material"), this);
	m_ShowRareProvinces->setStatusTip(tr("Shows only provinces with rare material"));
	connect(m_ShowRareProvinces, SIGNAL(triggered()), this, SLOT(FilterMapRareMaterial()));

	m_ShowIndustryProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_factory.ico"),tr("Industry"), this);
	m_ShowIndustryProvinces->setStatusTip(tr("Shows only provinces with industry"));
	connect(m_ShowIndustryProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowAAProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_aa.ico"),tr("Antiair"), this);
	m_ShowAAProvinces->setStatusTip(tr("Shows only provinces with antiair"));
	connect(m_ShowAAProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowAirbaseProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_airbase.ico"),tr("Airbase"), this);
	m_ShowAirbaseProvinces->setStatusTip(tr("Shows only provinces with airbase"));
	connect(m_ShowAirbaseProvinces, SIGNAL(triggered()), this, SLOT(FilterMapAirbase()));

	m_ShowCoastalfortProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_coastalfort.ico"),tr("Coastalfort"), this);
	m_ShowCoastalfortProvinces->setStatusTip(tr("Shows only provinces with coastalfort"));
	connect(m_ShowCoastalfortProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowInfraProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_infra.ico"),tr("Infrastructure"), this);
	m_ShowInfraProvinces->setStatusTip(tr("Shows only provinces with infrastructure"));
	connect(m_ShowInfraProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowLandfortProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_landfort.ico"),tr("Landfort"), this);
	m_ShowLandfortProvinces->setStatusTip(tr("Shows only provinces with landfort"));
	connect(m_ShowLandfortProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowNavalbaseProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_navalbase.ico"),tr("Navalbase"), this);
	m_ShowNavalbaseProvinces->setStatusTip(tr("Shows only provinces with navalbase"));
	connect(m_ShowNavalbaseProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowNuclearProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_nuclear.ico"),tr("Nuclear"), this);
	m_ShowNuclearProvinces->setStatusTip(tr("Shows only provinces with nuclear"));
	connect(m_ShowNuclearProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowRadarProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_radar.ico"),tr("Radar"), this);
	m_ShowRadarProvinces->setStatusTip(tr("Shows only provinces with radar"));
	connect(m_ShowRadarProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowRocketProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_rocket.ico"),tr("Rocket"), this);
	m_ShowRocketProvinces->setStatusTip(tr("Shows only provinces with rocket"));
	connect(m_ShowRocketProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_MapFilterToolBar = addToolBar(tr("Map filter"));
	m_MapFilterToolBar->addAction(m_ShowOriginalMap);
	m_MapFilterToolBar->addAction(m_ShowNationColorMap);
	m_MapFilterToolBar->addAction(m_ShowEnergyProvinces);
	m_MapFilterToolBar->addAction(m_ShowMetalProvinces);
	m_MapFilterToolBar->addAction(m_ShowRareProvinces);
	m_MapFilterToolBar->addAction(m_ShowOilProvinces);
	m_MapFilterToolBar->addAction(m_ShowIndustryProvinces);
	m_MapFilterToolBar->addAction(m_ShowAAProvinces);
	m_MapFilterToolBar->addAction(m_ShowAirbaseProvinces);
	m_MapFilterToolBar->addAction(m_ShowCoastalfortProvinces);
	m_MapFilterToolBar->addAction(m_ShowInfraProvinces);
	m_MapFilterToolBar->addAction(m_ShowLandfortProvinces);
	m_MapFilterToolBar->addAction(m_ShowNavalbaseProvinces);
	m_MapFilterToolBar->addAction(m_ShowNuclearProvinces);
	m_MapFilterToolBar->addAction(m_ShowRadarProvinces);
	m_MapFilterToolBar->addAction(m_ShowRocketProvinces);

	QToolButton *button2 = new QToolButton;
	button2->setText("Testicon2");
	button2->setIcon(QIcon(":HoIModDesigner/images/add2.ico"));
	button2->setIconSize(QSize(48, 48));
	button2->setCheckable(true);
	connect(button2,SIGNAL(clicked()),this,SLOT(DisplayContourMap()));
	
	QToolButton *button5 = new QToolButton;
	button5->setText("Testicon3");
	button5->setIcon(QIcon(":HoIModDesigner/images/add2.ico"));
	button5->setIconSize(QSize(48, 48));
	button5->setCheckable(true);
	connect(button5,SIGNAL(clicked()),this,SLOT(DisplayItemMap()));


	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button2, 0, 0, Qt::AlignHCenter);
	layout->addWidget(button5, 1, 0, Qt::AlignHCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	QGridLayout *backgroundLayout = new QGridLayout;
	backgroundLayout->addWidget(widget, 0, 0);

	m_ToolBox = new QToolBox;
	m_ToolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	m_ToolBox->setMinimumWidth(widget->sizeHint().width());
	m_ToolBox->addItem(widget, tr("First group"));


	QHBoxLayout *layoutMain = new QHBoxLayout;
	layoutMain->addWidget(m_ToolBox);
	m_View = new ExtendedGraphicsView(this);
	m_View->setMouseTracking(true);
	m_View->setInteractive(true);
	m_View->setOptimizationFlags(QGraphicsView::DontClipPainter);
	m_View->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	m_View->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);
	m_View->setCacheMode(QGraphicsView::CacheBackground);
	layoutMain->addWidget(m_View);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);

	CreateDockWidgets();

	setCentralWidget(widgetMain);
	setWindowState(windowState() | Qt::WindowMaximized);

	jha::LogInterface().Init();
	jha::GetLog()->RegisterLogger( new jha::LoggerFile("e:/temp/Logfile.log") );
	jha::GetLog()->RegisterLogger( new jha::LoggerTableWidget(m_DockWidgetLogging) );
	jha::GetLog()->Start();
}

/** */
void HoIModDesigner::FilterMapEnergy()
{
	ShowMapFiltered( TimeLineDataCriteriaEnergy() );
}

/** */
void HoIModDesigner::FilterMapMetal()
{
	ShowMapFiltered( TimeLineDataCriteriaMetal() );
}

/** */
void HoIModDesigner::FilterMapCrudeOil()
{
	ShowMapFiltered( TimeLineDataCriteriaCrudeOil() );
}

/** */
void HoIModDesigner::FilterMapRareMaterial()
{
	ShowMapFiltered( TimeLineDataCriteriaRareMaterial() );
}

void HoIModDesigner::FilterMapIndustry()
{
	ShowMapFiltered( TimeLineDataCriteriaIndustry() );
}

void HoIModDesigner::FilterMapAirbase()
{
	ShowMapFiltered( TimeLineDataCriteriaAirbase() );
}


HoIModDesigner::~HoIModDesigner()
{
}

void HoIModDesigner::LoadMap()
{
	HoI3Context context;
	ParserHoI3 parser;
	if( parser.Parse(context,m_View->m_Scene) == false )
	{
		return;
	}
	DisplayItemMap(&(context.m_ProvinceMap));
	FillCountryList(context.m_Countries,m_DockWidgetNationList);
	FillProvinceList(context.m_ProvinceMap,m_DockWidgetProvinceList);

//TODO: Sp�ter wieder aktivieren!!!
//	m_View->setSceneRect( 0, 0, m_OriginalMap.size().width(), m_OriginalMap.size().height() );
}

void HoIModDesigner::DisplayContourMap()
{
	connect(this, SIGNAL(SignalAppendRow(LoggingTableWidgetRow*)),m_DockWidgetLogging, SLOT(AppendRow(LoggingTableWidgetRow*)));

	LoggingTableWidgetRow *newRow = new LoggingTableWidgetRow;
	newRow->m_Items.push_back( new QTableWidgetItem("blabla") );
	newRow->m_Items.push_back( new QTableWidgetItem("blabla1") );
	newRow->m_Items.push_back( new QTableWidgetItem("blabla2") );
	newRow->m_Items.push_back( new QTableWidgetItem("blabla3") );

	emit SignalAppendRow(newRow);
		
}

void HoIModDesigner::DisplayItemMap( const QHash<int,ProvinceItem*>* items )
{
	m_View->m_Scene->clear();
 	QHash<int,ProvinceItem*>::ConstIterator iter;
 	for( iter = items->constBegin(); iter != items->constEnd(); iter++ )
 	{
		if( (*iter)->m_GraphicsItem == nullptr )
		{
			continue;
		}
		ProvinceGraphicsPixmapItem *copiedItem = new ProvinceGraphicsPixmapItem(*((*iter)->m_GraphicsItem));
		QPointF offset = copiedItem->offset();
		m_View->m_Scene->addItem( copiedItem );
	}
}

//================================================================================
void HoIModDesigner::CreateDockWidgets()
{
	{
		QDockWidget *dock = new QDockWidget(tr("Province details"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetProvinceDetails = new QTableWidget(16,2,dock);

		QHeaderView *verticalHeader = m_DockWidgetProvinceDetails->verticalHeader();
		verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
		verticalHeader->setDefaultSectionSize(20);

		m_DockWidgetProvinceDetails->verticalHeader()->setVisible(false);
		m_DockWidgetProvinceDetails->setSelectionBehavior(QAbstractItemView::SelectRows);
		
		QTableWidgetItem *headerColumn1 = new QTableWidgetItem("Bezeichner");
		headerColumn1->setBackground(Qt::lightGray);
		m_DockWidgetProvinceDetails->setHorizontalHeaderItem( 0, headerColumn1 );

		QTableWidgetItem *headerColumn2 = new QTableWidgetItem("Wert");
		headerColumn2->setBackground(Qt::lightGray);
		m_DockWidgetProvinceDetails->setHorizontalHeaderItem( 1, headerColumn2 );

		dock->setWidget(m_DockWidgetProvinceDetails);
		addDockWidget(Qt::RightDockWidgetArea, dock);
		m_DockWidgetsMenu->addAction(dock->toggleViewAction());
		connect(m_View->m_Scene, SIGNAL(SignalProvinceEntered(const ProvinceItem*)),this, SLOT(UpdateProvinceDetail(const ProvinceItem*)));
		//	connect(m_View->m_Scene, SIGNAL(SignalProvinceLeft(ProvinceItem*)),this, SLOT(removeProvinceInfo(ProvinceItem*)));
	}

	{
		QDockWidget *dockCountry = new QDockWidget(tr("Country list"), this);
		dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetNationList = new QTableWidget(0,0,dockCountry);
		dockCountry->setWidget( m_DockWidgetNationList );
		addDockWidget(Qt::RightDockWidgetArea, dockCountry);
		m_DockWidgetsMenu->addAction(dockCountry->toggleViewAction());
	}
	{
		QDockWidget *dockCountry = new QDockWidget(tr("Country details"), this);
		dockCountry->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetNationDetails = new QTableWidget(15,2,dockCountry);

		QHeaderView *verticalHeader = m_DockWidgetNationDetails->verticalHeader();
		verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
		verticalHeader->setDefaultSectionSize(20);

		m_DockWidgetNationDetails->verticalHeader()->setVisible(false);
		m_DockWidgetNationDetails->setSelectionBehavior(QAbstractItemView::SelectRows);
		QTableWidgetItem *headerColumn1 = new QTableWidgetItem("Bezeichner");
		headerColumn1->setBackground(Qt::lightGray);
		m_DockWidgetNationDetails->setHorizontalHeaderItem( 0, headerColumn1 );

		QTableWidgetItem *headerColumn2 = new QTableWidgetItem("Wert");
		headerColumn2->setBackground(Qt::lightGray);
		m_DockWidgetNationDetails->setHorizontalHeaderItem( 1, headerColumn2 );
		dockCountry->setWidget( m_DockWidgetNationDetails );
		addDockWidget(Qt::RightDockWidgetArea, dockCountry);
		m_DockWidgetsMenu->addAction(dockCountry->toggleViewAction());
		connect(m_DockWidgetNationList, SIGNAL(itemClicked(QTableWidgetItem *)),this, SLOT(UpdateCountryDetail(QTableWidgetItem*)));
	}

	{
		QDockWidget *dock = new QDockWidget(tr("Province list"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetProvinceList = new QTableWidget(15000,2,dock);

		QHeaderView *verticalHeader = m_DockWidgetProvinceList->verticalHeader();
		verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
		verticalHeader->setDefaultSectionSize(20);

		m_DockWidgetProvinceList->verticalHeader()->setVisible(false);
		m_DockWidgetProvinceList->setSelectionBehavior(QAbstractItemView::SelectRows);
		QTableWidgetItem *headerColumn1 = new QTableWidgetItem("ID");
		headerColumn1->setBackground(Qt::lightGray);
		m_DockWidgetProvinceList->setHorizontalHeaderItem( 0, headerColumn1 );

		QTableWidgetItem *headerColumn2 = new QTableWidgetItem("Name");
		headerColumn2->setBackground(Qt::lightGray);
		m_DockWidgetProvinceList->setHorizontalHeaderItem( 1, headerColumn2 );
		dock->setWidget( m_DockWidgetProvinceList );
		addDockWidget(Qt::RightDockWidgetArea, dock);
		m_DockWidgetsMenu->addAction(dock->toggleViewAction());
	}
	{
		QDockWidget *dock2 = new QDockWidget(tr("Logging"), this);
		dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea );
		m_DockWidgetLogging = new LoggingTableWidget(0,0,dock2);

		dock2->setWidget( m_DockWidgetLogging );
		addDockWidget(Qt::BottomDockWidgetArea, dock2);
		m_DockWidgetsMenu->addAction(dock2->toggleViewAction());
	}
}

void HoIModDesigner::UpdateProvinceDetail( const ProvinceItem* item )
{
	if( item == nullptr )
	{
		return;
	}
	m_DockWidgetProvinceDetails->clearContents();

	int index = 0;
	m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("ID") );
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(QString().setNum(item->m_ID) ) );

	m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Name") );
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(item->m_Name) );

	//TODO: Nur BASE-Datensatz
	if( item->m_TimeLineData.isEmpty() == false )
	{
		const ProvinceTimeLineData& data = item->m_TimeLineData.at(0);

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Owner") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(data.m_Owner ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Controller") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(data.m_Controller ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Points") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Points) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Manpower") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Manpower,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Leadership") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_LeaderShip,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Energy") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Energy,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Metal") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Metal,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Rare materials") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_RareMaterials,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Cruide Oil") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_CrudeOil,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Industry") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Industry) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Infrastructure") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Infrastructure) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Anti air") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_AntiAir) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Air bases") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_AirBases) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Naval bases") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_NavalBase) ) );
	}
}


void HoIModDesigner::UpdateCountryDetail( QTableWidgetItem* item )
{
	if( item == nullptr )
	{
		return;
	}

	TableWidgetItemNation *specialItem = dynamic_cast<TableWidgetItemNation*>(item);
	if( item == nullptr )
	{
		return;
	}

	if( specialItem->m_Nation == nullptr )
	{
		return;
	}
	m_DockWidgetNationDetails->clearContents();

	int index = 0;
	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("ID") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem(specialItem->m_Nation->m_ID ) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Provinces") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->m_Provinces.size())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("IC") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcIC())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Points") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcPoints())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Manpower") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcManpower())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Leadership") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcLeadership())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Energy") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcEnergy())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Metal") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcMetal())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Crude oil") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcCrudeOil())) );

	m_DockWidgetNationDetails->setItem(index, 0, new QTableWidgetItem("Rare material") );
	m_DockWidgetNationDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetNationDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(specialItem->m_Nation->CalcRareMaterial())) );
}


void HoIModDesigner::FillCountryList( const QHash<QString,Nation*>& nations, QTableWidget* widget )
{
	if( widget == nullptr )
	{
		return;
	}

	widget->setSortingEnabled(true);
	widget->setRowCount( nations.size() );
	widget->setColumnCount( 10 );

	QHeaderView *verticalHeader = widget->verticalHeader();
	verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader->setDefaultSectionSize(20);

	int columnIndex = 0;
	widget->verticalHeader()->setVisible(false);
	widget->setSelectionBehavior(QAbstractItemView::SelectRows);
	QTableWidgetItem *id = new QTableWidgetItem("Name");
	id->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, id );

	QTableWidgetItem *provinces = new QTableWidgetItem("Provinces");
	provinces->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, provinces );

	QTableWidgetItem *ic = new QTableWidgetItem("IC");
	ic->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, ic );

	QTableWidgetItem *points = new QTableWidgetItem("Points");
	points->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, points );

	QTableWidgetItem *manpower = new QTableWidgetItem("Manpower");
	manpower->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, manpower );

	QTableWidgetItem *leadership = new QTableWidgetItem("Leadership");
	leadership->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, leadership );

	QTableWidgetItem *energy = new QTableWidgetItem("Energy");
	energy->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, energy );

	QTableWidgetItem *metal = new QTableWidgetItem("Metal");
	metal->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, metal );

	QTableWidgetItem *oil = new QTableWidgetItem("Crude oil");
	oil->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, oil );

	QTableWidgetItem *rare = new QTableWidgetItem("Rare material");
	rare->setBackground(Qt::lightGray);
	widget->setHorizontalHeaderItem( columnIndex++, rare );
	if( nations.isEmpty() == true )
	{
		return;
	}

	int rowIndex = 0;
	QHash<QString,Nation*>::ConstIterator iter;
	for( iter = nations.constBegin(); iter != nations.constEnd(); iter++ )
	{
		int columnIndex = 0;
		widget->setItem(rowIndex, columnIndex++, new TableWidgetItemNation((*iter)->GetID(),(*iter)) );
		widget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
		
		QTableWidgetItem *provinces = new TableWidgetItemNation(QString().setNum((*iter)->m_Provinces.size()),(*iter));
		widget->setItem(rowIndex, columnIndex++, provinces );

		QTableWidgetItem *ic = new TableWidgetItemNation(QString().setNum((*iter)->CalcIC()),(*iter));
		widget->setItem(rowIndex, columnIndex++, ic );

		QTableWidgetItem *points = new TableWidgetItemNation(QString().setNum((*iter)->CalcPoints()),(*iter));
		widget->setItem(rowIndex, columnIndex++, points );

		QTableWidgetItem *manpower = new TableWidgetItemNation(QString().setNum((*iter)->CalcManpower()),(*iter));
		widget->setItem(rowIndex, columnIndex++, manpower );

		QTableWidgetItem *leadership = new TableWidgetItemNation(QString().setNum((*iter)->CalcLeadership()),(*iter));
		widget->setItem(rowIndex, columnIndex++, leadership );

		QTableWidgetItem *energy = new TableWidgetItemNation(QString().setNum((*iter)->CalcEnergy()),(*iter));
		widget->setItem(rowIndex, columnIndex++, energy );

		QTableWidgetItem *metal = new TableWidgetItemNation(QString().setNum((*iter)->CalcMetal()),(*iter));
		widget->setItem(rowIndex, columnIndex++, metal );

		QTableWidgetItem *oil = new TableWidgetItemNation(QString().setNum((*iter)->CalcCrudeOil()),(*iter));
		widget->setItem(rowIndex, columnIndex++, oil );

		QTableWidgetItem *rare = new TableWidgetItemNation(QString().setNum((*iter)->CalcRareMaterial()),(*iter));
		widget->setItem(rowIndex, columnIndex++, rare );

		rowIndex++;
	}
}

void HoIModDesigner::FillProvinceList( QHash<int,ProvinceItem*>& provinces, QTableWidget* widget )
{
	if( widget == nullptr )
	{
		return;
	}
	widget->clearContents();
	if( provinces.isEmpty() == true )
	{
		return;
	}

	int rowIndex = 0;
	QHash<int,ProvinceItem*>::ConstIterator iter;
	for( iter = provinces.constBegin(); iter != provinces.constEnd(); iter++ )
	{
		if( (*iter)->m_Name.isEmpty() == true )
		{
			continue;
		}
		widget->setItem(rowIndex, 0, new QTableWidgetItem(QString().setNum((*iter)->m_ID)) );
		widget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
		widget->setItem(rowIndex, 1, new QTableWidgetItem((*iter)->m_Name) );
		rowIndex++;
	}
}

void HoIModDesigner::ShowOriginalMap()
{
	m_View->setVisible(false);
	QList<QGraphicsItem *> items = m_View->m_Scene->items();
	for( int i=0;i<items.size();i++ )
	{
		ProvinceGraphicsPixmapItem* item = dynamic_cast<ProvinceGraphicsPixmapItem*>(items.at(i));
		if( item == nullptr )
		{
			continue;
		}
		if( item->GetAttachedProvinceItem() == nullptr )
		{
			continue;
		}

		item->UpdateColor(item->GetAttachedProvinceItem()->m_Color);
	}
	m_View->setVisible(true);
}

void HoIModDesigner::ShowNationColorMap()
{
	m_View->setVisible(false);
	QList<QGraphicsItem *> items = m_View->m_Scene->items();
	for( int i=0;i<items.size();i++ )
	{
		ProvinceGraphicsPixmapItem* item = dynamic_cast<ProvinceGraphicsPixmapItem*>(items.at(i));
		if( item == nullptr )
		{
			continue;
		}
		if( item->GetAttachedProvinceItem() == nullptr )
		{
			continue;
		}

		item->UpdateColor(item->GetAttachedProvinceItem()->m_ColorNation);
	}
	m_View->setVisible(true);
}

void HoIModDesigner::ShowMapFiltered( const TimeLineDataCriteria& criteria )
{
	m_View->setVisible(false);
	QList<QGraphicsItem *> items = m_View->m_Scene->items();
	for( int i=0;i<items.size();i++ )
	{
		ProvinceGraphicsPixmapItem* item = dynamic_cast<ProvinceGraphicsPixmapItem*>(items.at(i));
		if( item == nullptr )
		{
			continue;
		}
		if( item->GetAttachedProvinceItem() == nullptr )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}

		if( item->GetAttachedProvinceItem()->m_ColorNation == Qt::white )
		{
			item->UpdateColor(QColor(135,165,230));
			continue; //Wasser
		}

		if( item->GetAttachedProvinceItem()->m_TimeLineData.isEmpty() == true )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}

		if( criteria.CriteriaFullfilled(item->GetAttachedProvinceItem()->m_TimeLineData.at(0)) == true )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}
		item->UpdateColor(Qt::green);
	}
	m_View->setVisible(true);
}

//================================================================================
//================================================================================
//================================================================================
LoggingTableWidget::LoggingTableWidget( int rows, int columns, QWidget * parent )
	: QTableWidget(rows,columns,parent),
	m_RowsAdded(false)
{
	m_TimerScrollToBottom = new QTimer;
	m_TimerScrollToBottom->setInterval(100);
	connect(m_TimerScrollToBottom,SIGNAL(timeout()),SLOT(ScrollToBottom()));
	m_TimerScrollToBottom->start();
	
	setRowCount(0);
	setColumnCount(4);

	verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader()->setDefaultSectionSize(20);

	//	verticalHeader->setVisible(false);
	setSelectionBehavior(QAbstractItemView::SelectRows);

	horizontalHeader()->setStretchLastSection(true);

	QTableWidgetItem *time = new QTableWidgetItem("Time");
	time->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 0, time );

	QTableWidgetItem *logLevel = new QTableWidgetItem("Log level");
	logLevel->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 1, logLevel );

	QTableWidgetItem *category = new QTableWidgetItem("Category");
	category->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 2, category );

	QTableWidgetItem *message = new QTableWidgetItem("Message");
	message->setBackground(Qt::lightGray);
	setHorizontalHeaderItem( 3, message );

	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void LoggingTableWidget::AppendRow( LoggingTableWidgetRow *newRow )
{
	if( newRow == nullptr )
	{
		return;
	}
	if( newRow->m_Items.isEmpty() == true )
	{
		return;
	}

	int newRowIndex = rowCount();
	insertRow( newRowIndex );

	for( int i=0;i<newRow->m_Items.size();i++ )
	{
		setItem(newRowIndex,i,newRow->m_Items.at(i));
	}

	delete newRow;
	newRow = nullptr;

	m_RowsAdded = true;
}

LoggingTableWidget::~LoggingTableWidget()
{
	delete m_TimerScrollToBottom;
}

void LoggingTableWidget::ScrollToBottom()
{
	if( m_RowsAdded == false )
	{
		return;
	}
	m_RowsAdded = false;
	scrollToBottom();
}
