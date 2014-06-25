#include "stdafx.h"
#include "hoimoddesigner.h"
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
#include "MapFilter.h"
#include "ContextFactory.h"


HoIModDesigner::HoIModDesigner(QWidget *parent)
	: QMainWindow(parent),
	m_DockWidgetNationList(nullptr),
	m_DockWidgetNationDetails(nullptr),
	m_Parser(nullptr)
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

	m_SaveChangesAction = new QAction(QIcon(":HoIModDesigner/images/floppy_disk.ico"),tr("Save"),this );
	m_SaveChangesAction->setStatusTip(tr("Save changes"));
	connect(m_SaveChangesAction, SIGNAL(triggered()), this, SLOT(SaveChanges()));

	m_FileConfigurationAction = new QAction(QIcon(":HoIModDesigner/images/gear.ico"),tr("Configuration..."),this );
	m_FileConfigurationAction->setStatusTip(tr("Open configuration dialog"));
	connect(m_FileConfigurationAction, SIGNAL(triggered()), this, SLOT(OpenConfigurationDialog()));

	m_AboutAction = new QAction(QIcon(":HoIModDesigner/images/about.ico"),tr("About..."),this );
	m_AboutAction->setStatusTip(tr("Show about dialog"));
//	connect(m_AboutAction, SIGNAL(triggered()), this, SLOT(About()));

	m_FileMenu = menuBar()->addMenu(tr("&File"));
	m_FileMenu->addAction( m_LoadMapAction );
	m_FileMenu->addAction( m_SaveChangesAction );
	m_FileMenu->addSeparator();
	m_FileMenu->addAction( m_FileConfigurationAction );
	m_FileMenu->addSeparator();
	m_FileMenu->addAction( m_ExitAction );

	m_DockWidgetsMenu = menuBar()->addMenu("Windows");

	m_HilfeMenu = menuBar()->addMenu(tr("Help"));
	m_HilfeMenu->addAction( m_AboutAction );

	m_FileToolBar = addToolBar(tr("Edit"));
	m_FileToolBar->addAction(m_ExitAction);
	m_FileToolBar->addAction(m_LoadMapAction);
	m_FileToolBar->addAction(m_SaveChangesAction);

	m_ShowOriginalMap = new QAction(QIcon("images/test.png"),tr("Original"), this);
	m_ShowOriginalMap->setStatusTip(tr("Shows original map"));
	connect(m_ShowOriginalMap, SIGNAL(triggered()), this, SLOT(ShowOriginalMap()));

	m_ShowNationColorMap = new QAction(QIcon(":HoIModDesigner/images/mapmode_political.ico"),tr("Nations"), this);
	m_ShowNationColorMap->setStatusTip(tr("Shows map by country colors"));
	connect(m_ShowNationColorMap, SIGNAL(triggered()), this, SLOT(ShowNationColorMap()));

	m_ShowMetalProvinces = new FilterAction(QIcon(":HoIModDesigner/images/resource_metal.ico"),tr("Metal"), new TimeLineDataCriteriaMetal(), this);
	m_ShowMetalProvinces->setStatusTip(tr("Shows only provinces with metal"));

	m_ShowOilProvinces = new FilterAction(QIcon(":HoIModDesigner/images/resource_oil.ico"),tr("Crude oil"), new TimeLineDataCriteriaCrudeOil(), this);
	m_ShowOilProvinces->setStatusTip(tr("Shows only provinces with crude oil"));

	m_ShowEnergyProvinces = new FilterAction(QIcon(":HoIModDesigner/images/resource_energy.ico"),tr("Energy"), new TimeLineDataCriteriaEnergy(), this);
	m_ShowEnergyProvinces->setStatusTip(tr("Shows only provinces with energy"));

	m_ShowRareProvinces = new FilterAction(QIcon(":HoIModDesigner/images/resource_raremat.ico"),tr("Rare material"), new TimeLineDataCriteriaRareMaterial(), this);
	m_ShowRareProvinces->setStatusTip(tr("Shows only provinces with rare material"));

	m_ShowIndustryProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_factory.ico"),tr("Industry"), new TimeLineDataCriteriaIndustry(), this);
	m_ShowIndustryProvinces->setStatusTip(tr("Shows only provinces with industry"));

	m_ShowAAProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_aa.ico"),tr("Antiair"), new TimeLineDataCriteriaAntiair(), this);
	m_ShowAAProvinces->setStatusTip(tr("Shows only provinces with antiair"));

	m_ShowAirbaseProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_airbase.ico"),tr("Airbase"), new TimeLineDataCriteriaAirbase(), this);
	m_ShowAirbaseProvinces->setStatusTip(tr("Shows only provinces with airbase"));

	m_ShowCoastalfortProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_coastalfort.ico"),tr("Coastalfort"), new TimeLineDataCriteriaCoastalfort(), this);
	m_ShowCoastalfortProvinces->setStatusTip(tr("Shows only provinces with coastalfort"));

	m_ShowInfraProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_infra.ico"),tr("Infrastructure"), new TimeLineDataCriteriaInfrastructure(), this);
	m_ShowInfraProvinces->setStatusTip(tr("Shows only provinces with infrastructure"));

	m_ShowLandfortProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_landfort.ico"),tr("Landfort"), new TimeLineDataCriteriaLandfort(), this);
	m_ShowLandfortProvinces->setStatusTip(tr("Shows only provinces with landfort"));

	m_ShowNavalbaseProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_navalbase.ico"),tr("Navalbase"), new TimeLineDataCriteriaNavalbase(), this);
	m_ShowNavalbaseProvinces->setStatusTip(tr("Shows only provinces with navalbase"));

	m_ShowNuclearProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_nuclear.ico"),tr("Nuclear"), new TimeLineDataCriteriaNuclear(), this);
	m_ShowNuclearProvinces->setStatusTip(tr("Shows only provinces with nuclear"));

	m_ShowRadarProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_radar.ico"),tr("Radar"), new TimeLineDataCriteriaRadar(), this);
	m_ShowRadarProvinces->setStatusTip(tr("Shows only provinces with radar"));

	m_ShowRocketProvinces  = new FilterAction(QIcon(":HoIModDesigner/images/icon_build_rocket.ico"),tr("Rocket"), new TimeLineDataCriteriaRocket(), this);
	m_ShowRocketProvinces->setStatusTip(tr("Shows only provinces with rocket"));

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

	QButtonGroup *paintEvents = new QButtonGroup(this);
	paintEvents->setExclusive(true);
	QVBoxLayout *layoutPaintEvents = new QVBoxLayout;
	layoutPaintEvents->addWidget(CreatePaintButton( tr("Country") ));
	layoutPaintEvents->addWidget(CreatePaintButton( tr("Industry") ));
	layoutPaintEvents->addWidget(CreatePaintButton( tr("Metal") ));
	QWidget *itemWidget = new QWidget;
	itemWidget->setLayout(layoutPaintEvents);
	m_ToolBox->addItem(itemWidget, tr("Painters"));

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

	connect(m_View->m_Scene, SIGNAL(SignalProvinceEntered(ProvinceItem*)),m_View->m_Scene, SLOT(SlotProvinceEntered(ProvinceItem*)));
	connect(m_View->m_Scene, SIGNAL(SignalProvinceMouseReleased(ProvinceItem*)),this, SLOT(SlotProvinceMouseReleased(ProvinceItem*)));

	jha::LogInterface().Init();
	jha::GetLog()->RegisterLogger( new jha::LoggerFile("d:/temp/Logfile.log") );
	jha::GetLog()->RegisterLogger( new jha::LoggerTableWidget(m_DockWidgetLogging) );
	jha::GetLog()->Start();
}

QWidget *HoIModDesigner::CreatePaintButton(const QString &text )
{

	QToolButton *button = new QToolButton;
	button->setIcon(QIcon(":HoIModDesigner/images/gear.ico"));
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
//	buttonGroup->addButton(button, int(type));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}


HoIModDesigner::~HoIModDesigner()
{
}

#include "ParserThreadContainer.h"
void HoIModDesigner::LoadMap()
{
	if( m_Parser == nullptr )
	{
		m_Parser = new ParserHoI3(m_View->m_Scene, 	ContextFactory().CreateDefaultContext() );
	}

	ParserThreadContainer *parserThreadContainer = new ParserThreadContainer(m_Parser);
	connect( parserThreadContainer, SIGNAL(ParsingFinished()), this, SLOT(ParsingFinished()) );
	parserThreadContainer->StartParsing();
	connect( m_View->m_Scene, SIGNAL(UpdateProvinceOwner( ProvinceItem* )), this, SLOT(UpdateProvinceColor( ProvinceItem *)));
}


void HoIModDesigner::ParsingFinished()
{
	DisplayItemMap(m_Parser->m_Context->m_ProvinceMap);
	FillCountryList(m_Parser->m_Context->m_Countries,m_DockWidgetNationList);
	FillProvinceList(m_Parser->m_Context->m_ProvinceMap,m_DockWidgetProvinceList);
	FillBuildinsList(m_Parser->m_Context->m_BuildingTypes,m_DockWidgetBuildingTypes);
// 	m_TestContext = new HoI3Context("dfsf");
// 	m_TestContext =	*(m_Parser->m_Context);
}

// #include "property/QPropertyEditorWidget.h"
// #include "property/CustomTypes.h"
// #include "property/TestClass.h"
// void HoIModDesigner::DisplayContourMap()
// {
// 	QDockWidget *dock = new QDockWidget(tr("Properties"), this);
// 	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
// 
// 	CustomTypes::registerTypes();
// 	m_PropertyEdit = new  QPropertyEditorWidget(dock);
// 
// 	m_PropertyEdit->registerCustomPropertyCB(CustomTypes::createCustomProperty);
//  	TestClass *testClass = new TestClass(this);
// 	testClass->setProperty("Dynamic prop",QVariant("Text"));
// 	testClass->setProperty("Dynamic2",QVariant(23));
// //	testClass->
// 	//testClass->property()
//  	m_PropertyEdit->addObject(testClass);
// 
// 	dock->setWidget(m_PropertyEdit);
// 	addDockWidget(Qt::RightDockWidgetArea, dock);
// 	m_DockWidgetsMenu->addAction(dock->toggleViewAction());
// }

//#include "prop\propertyeditor.h"
#include "HoI3Scriptparser.h"
#include "ParserHoI3.h"
void HoIModDesigner::DisplayContourMap()
{
	QPixmap newPixmap;
	newPixmap.load("E:/temp/building_airbase.dds");
	m_View->m_Scene->addPixmap(newPixmap);

	ParserHoI3 parser(nullptr,nullptr);
	HoI3Script *script = parser.ParseScript("E:/Spiele/HoI3/events/ClaimingMemel.txt");
	if( script == nullptr )
	{
		return;
	}
	HoI3Scriptparser scriptParser;
	scriptParser.SaveScript( *script, "E:/Spiele/HoI3/events/ClaimingMemel2.txt" );

// 
// 	QDockWidget *dock = new QDockWidget(tr("Script"), this);
// 	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
// 	m_TreeView = new QTreeWidget(dock);
// 	m_TreeView->setColumnCount(2);
// 
// 	QList<QTreeWidgetItem*> topLevelItems;
// 	QList<HoI3Token>::const_iterator iter;
// 	for( iter = script->m_TokenList.constBegin(); iter  != script->m_TokenList.constEnd(); iter++ )
// 	{
// 		QStringList newData;
// 		newData << iter->m_Name << iter->m_Value;
// 		QTreeWidgetItem *newTopLevelItem = new QTreeWidgetItem( m_TreeView, newData );
// 		CreateColumn( newTopLevelItem, (*iter) );
// 	}
// 
// 	m_TreeView->addTopLevelItems(topLevelItems);
// 	m_TreeView->expandAll();
// 
// 	dock->setWidget(m_TreeView);
// 	addDockWidget(Qt::RightDockWidgetArea, dock);
// 	m_DockWidgetsMenu->addAction(dock->toggleViewAction());
}

void HoIModDesigner::CreateColumn( QTreeWidgetItem* parent, const HoI3Token& token ) const
{
	QList<HoI3Token>::ConstIterator iter;
	for( iter = token.m_Tokens.constBegin(); iter != token.m_Tokens.constEnd(); iter++ )
	{
		QStringList newData;
		newData << iter->m_Name << iter->m_Value;
		QTreeWidgetItem *newItem = new QTreeWidgetItem( parent, newData );
		CreateColumn( newItem, (*iter) );
	}
}

void HoIModDesigner::DisplayItemMap( const QHash<int,ProvinceItem*>& items )
{
	try
	{
		m_View->m_Scene->clear();
		QHash<int,ProvinceItem*>::ConstIterator iter;
		for( iter = items.constBegin(); iter != items.constEnd(); iter++ )
		{
			if( (*iter)->m_GraphicsItem == nullptr )
			{
				continue;
			}
 			m_View->m_Scene->addItem( (*iter)->m_GraphicsItem );
		}
	}
	catch(...)
	{

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
		connect(m_View->m_Scene, SIGNAL(SignalProvinceEntered(ProvinceItem*)),this, SLOT(UpdateProvinceDetail(ProvinceItem*)));
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
	{
		QDockWidget *dock2 = new QDockWidget(tr("Buildings"), this);
		dock2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea );
		m_DockWidgetBuildingTypes = new QTableWidget(0,0,dock2);

		dock2->setWidget( m_DockWidgetBuildingTypes );
		addDockWidget(Qt::BottomDockWidgetArea, dock2);
		m_DockWidgetsMenu->addAction(dock2->toggleViewAction());
		
	}
}

void HoIModDesigner::UpdateProvinceDetail( ProvinceItem* item )
{
	if( item == nullptr )
	{
		return;
	}
	m_DockWidgetProvinceDetails->clearContents();
	m_DockWidgetProvinceDetails->setRowCount(item->GetItemMap().size() + 2);
	int index = 0;
	m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("ID") );
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(QString().setNum(item->m_ID) ) );

	m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Name") );
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(item->m_Name) );

	QMap<QString,ItemData>::ConstIterator iter;
	for( iter = item->GetItemMap().constBegin(); iter != item->GetItemMap().constEnd(); iter++ )
	{
		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem( iter->GetName()) );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( iter->GetData().type() == QVariant::StringList ? iter->GetData().toStringList().join(", ") : iter->GetData().toString() ) );
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
		TableWidgetItemNation *nameItem = new TableWidgetItemNation((*iter)->GetID(),(*iter), new TableWidgetItemComparatorString() );
		widget->setItem(rowIndex, columnIndex++, nameItem );
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

#include "BuildingItem.h"
void HoIModDesigner::FillBuildinsList( QHash<QString,BuildingItem*>& buildings, QTableWidget* widget )
{
	if( widget == nullptr )
	{
		return;
	}
	widget->clearContents();
	if( buildings.isEmpty() == true )
	{
		return;
	}


	widget->setColumnCount(12);
	widget->setRowCount(buildings.size());
	int rowIndex = 0;
	QHash<QString,BuildingItem*>::ConstIterator iter;
	for( iter = buildings.constBegin(); iter != buildings.constEnd(); iter++ )
	{
		if( (*iter)->GetName().isEmpty() == true )
		{
			continue;
		}

		int columnIndex = 0;
		widget->setItem(rowIndex, columnIndex++, new QTableWidgetItem((*iter)->GetName()) );

		QMap<QString,ItemData>::ConstIterator iterData;
		for( iterData = (*iter)->GetItemMap().constBegin(); iterData != (*iter)->GetItemMap().constEnd(); iterData++ )
		{
			widget->setItem(rowIndex, columnIndex++, new QTableWidgetItem( iterData->GetData().toString() ) );
		}
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

void HoIModDesigner::ShowMapFiltered( const TimeLineDataCriteria* criteria )
{
	if( criteria == nullptr )
	{
		return;
	}
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

		if( criteria->CriteriaFullfilled(item->GetAttachedProvinceItem()->GetItemMap()) == true )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}
		item->UpdateColor(Qt::green);
	}
	m_View->setVisible(true);
}

#include "ConfigurationDialog.h"
void HoIModDesigner::OpenConfigurationDialog()
{
	ConfigurationDialog dialog;
	dialog.exec();
}

void HoIModDesigner::UpdateProvinceColor( ProvinceItem *item )
{
	if( item == nullptr )
	{
		return;
	}

	m_Parser->m_Context->UpdateNationColor(item);

	QList<QGraphicsItem *> items = m_View->m_Scene->items();
	for( int i=0;i<items.size();i++ )
	{
		ProvinceGraphicsPixmapItem* itemToUpdate = dynamic_cast<ProvinceGraphicsPixmapItem*>(items.at(i));
		if( itemToUpdate == nullptr )
		{
			continue;
		}
		if( item != itemToUpdate->GetAttachedProvinceItem() )
		{
			continue;
		}
		itemToUpdate->UpdateColor(item->m_ColorNation);
	}
	m_View->setVisible(true);
}

#include "CommandFactory.h"
void HoIModDesigner::SlotProvinceMouseReleased(ProvinceItem *item )
{
	if( item == nullptr )
	{
		return;
	}
	ItemData itemOwner = item->FindItem( ProvinceItemPrototypeRepository::owner.GetName() );
	itemOwner.SetData("GER");
	QSharedPointer<jha::Command> command( CommandFactory().CreateCommandUpdateProvinceItem(item,itemOwner));
	if( command->Execute() == false )
	{
		return;
	}
	ItemData itemController = item->FindItem( ProvinceItemPrototypeRepository::controller.GetName() );
	itemController.SetData("GER");
	QSharedPointer<jha::Command> command2( CommandFactory().CreateCommandUpdateProvinceItem(item,itemController));
	if( command2->Execute() == false )
	{
		return;
	}
	item->m_GraphicsItem->ShowSelected();
	UpdateProvinceColor(item);
}

void HoIModDesigner::SaveChanges()
{
	if( m_Parser == nullptr )
	{
		return;
	}
	m_Parser->SaveProvinceDetailInfo( m_Parser->m_Context->m_ProvinceMap );
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

//================================================================================
bool TableWidgetItemComparatorDouble::Compare( const QTableWidgetItem &lhs, const QTableWidgetItem &rhs ) const
{
	return lhs.text().toDouble() < rhs.text().toDouble();
}

//================================================================================
bool TableWidgetItemComparatorString::Compare( const QTableWidgetItem &lhs, const QTableWidgetItem &rhs ) const
{
	return lhs.text() < rhs.text();
}
