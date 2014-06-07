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

	m_ShowIndustryProvinces  = new QAction(QIcon(":HoIModDesigner/images/icon_build_industry.ico"),tr("Industry"), this);
	m_ShowIndustryProvinces->setStatusTip(tr("Shows only provinces with industry"));
	connect(m_ShowIndustryProvinces, SIGNAL(triggered()), this, SLOT(ShowIndustryColorMap()));

	m_ShowMetalProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_metal.ico"),tr("Metal"), this);
	m_ShowMetalProvinces->setStatusTip(tr("Shows only provinces with metal"));
	connect(m_ShowMetalProvinces, SIGNAL(triggered()), this, SLOT(ShowMetalColorMap()));

	m_ShowOilProvinces = new QAction(QIcon(":HoIModDesigner/images/resource_oil.ico"),tr("Crude oil"), this);
	m_ShowOilProvinces->setStatusTip(tr("Shows only provinces with crude oil"));
	connect(m_ShowOilProvinces, SIGNAL(triggered()), this, SLOT(ShowCrudeOilColorMap()));

	m_MapFilterToolBar = addToolBar(tr("Map filter"));
	m_MapFilterToolBar->addAction(m_ShowOriginalMap);
	m_MapFilterToolBar->addAction(m_ShowNationColorMap);
	m_MapFilterToolBar->addAction(m_ShowIndustryProvinces);
	m_MapFilterToolBar->addAction(m_ShowMetalProvinces);
	m_MapFilterToolBar->addAction(m_ShowOilProvinces);

	QToolButton *button = new QToolButton;
	button->setText("Testicon");
	button->setIcon(QIcon(":HoIModDesigner/images/user.ico"));
	button->setIconSize(QSize(48, 48));
	button->setCheckable(true);
	connect(button,SIGNAL(clicked()),this,SLOT(DisplayOriginalMap()));

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

	//	backgroundButtonGroup->addButton(button);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(button2, 1, 0, Qt::AlignHCenter);
	layout->addWidget(button5, 2, 0, Qt::AlignHCenter);

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
	jha::GetLog()->Log( "Hallo Logmanager", jha::LogInterface::LL_INFO );
}

HoIModDesigner::~HoIModDesigner()
{
	ClearProvinceItems();
	ClearNations();
}

bool HoIModDesigner::CreateColorMap( QHash<int,ProvinceItem*>& result )
{
	QImage mapImage = m_OriginalMap.toImage();
	if( mapImage.isNull() == true )
	{
		//Unable to transform bitmap
		return false;
	}

	int width   = mapImage.width();
	int height  = mapImage.height();
	for( int i=0;i<height;i++ )
	{
		for( int j=0;j<width;j++ )
		{
			QRgb color = mapImage.pixel( j, i );
			QHash<int,ProvinceItem*>::iterator found = result.find( color );

			if( found == result.end() )
			{
				//TODO: Kein Eintrag in definition.csv für  Farbcode <x,y,z> aus provinces.bmp
				continue;
			}
			found.value()->m_Contour.append( QPoint(j,i) );
		}
	}
	return result.isEmpty() == false;
}

void HoIModDesigner::LoadMap()
{
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Siziliy3.bmp");
//	QString mapName("C:\\Users\\jha\\Documents\\GitHub\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Siziliy.bmp");
//	QString mapName("C:\\Users\\jha\\Documents\\GitHub\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Siziliy3.bmp");
//	QString mapName("C:\\Users\\jha\\Documents\\GitHub\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Error.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Rectangle.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Abstrakt.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Rectangle_4.bmp");
	
//	QString mapName("D:\\Spiele\\HoI3\\map\\provinces.bmp");
	QString mapName = QFileDialog::getOpenFileName(this, tr("Open Image"), "C:\\Users\\jha\\Documents\\GitHub\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\", tr("Image Files (*.png *.jpg *.bmp)"));
	LoadOriginalMap(mapName);
	m_View->setSceneRect( 0, 0, m_OriginalMap.size().width(), m_OriginalMap.size().height() );

	ClearProvinceItems();
	ClearNations();
	QString pathDefinitionCSV("E:\\Spiele\\HoI3\\map\\definition.csv");
	ParseProvinzList(m_ProvinceMapByRGB,m_ProvinceMapByID,pathDefinitionCSV);

	QString pathCountriesTXT("E:\\Spiele\\HoI3\\common\\countries.txt");
	ParseCountryList(m_Nations,pathCountriesTXT);

	FillCountryList(m_Nations,m_DockWidgetNationList);
	FillProvinceList(m_ProvinceMapByID,m_DockWidgetProvinceList);

	QString pathProvinceDetailInfos("E:\\Spiele\\HoI3\\history\\provinces");
	ParseProvinceDetailInfoDirectory( m_ProvinceMapByID, pathProvinceDetailInfos );
	AttachProvincesToNations( m_ProvinceMapByID, m_Nations );

	
	CreateColorMap(m_ProvinceMapByRGB);
	CreateGraphicsItems(m_ProvinceMapByRGB);
	DisplayItemMap();
}

void HoIModDesigner::AttachProvincesToNations( const QHash<int,ProvinceItem*>& provinces, QHash<QString,Nation*>& nations )
{
	QHash<int,ProvinceItem*>::ConstIterator iter;
	for( iter = provinces.constBegin(); iter != provinces.constEnd(); iter++ )
	{
		AttachProvinceToNation((*iter),nations);
	}
}

void HoIModDesigner::AttachProvinceToNation( ProvinceItem *province, QHash<QString,Nation*>& nations )
{
	if( province == nullptr )
	{
		return;
	}
	if( province->m_TimeLineData.isEmpty() == true )
	{
		return;
	}
	QString controller = province->m_TimeLineData.at(0).m_Controller;
	QHash<QString,Nation*>::iterator country = nations.find(controller);
	if( country == nations.end() )
	{
		return;
	}
	(*country)->AttachProvince(province);
	province->m_ColorNation = (*country)->GetColor();
}

void HoIModDesigner::CreateGraphicsItems( QHash<int,ProvinceItem*>& result ) const
{
	QHash<int,ProvinceItem*>::Iterator iter;
	for( iter = result.begin(); iter != result.end(); iter++ )
	{
		(*iter)->m_GraphicsItem = CreateItemFromPixelClash((*iter)->m_Contour,(*iter)->m_Color, m_View->m_Scene );
		if( (*iter)->m_GraphicsItem == nullptr )
		{
			continue;
		}
//		iter->m_GraphicsItem->SetAttachedProvinceItem(&(iter.value()));
		if( (*iter)->m_ID == 11391 )
		{
			int wait = 0;
		}
		(*iter)->m_GraphicsItem->SetAttachedProvinceItem( m_ProvinceMapByID.find(iter.value()->m_ID).value() );
	}
}

ProvinceGraphicsPixmapItem* HoIModDesigner::CreateItemFromPixelClash( const QPolygon& pixelClash, const QColor& color, ExtendedGraphicsScene *scene ) const
{
	if( pixelClash.empty() == true )
	{
		return nullptr;
	}
	QRect rect = PolygonHelper().FindSurroundingRect(pixelClash);
	if( rect.isValid() == false )
	{
		return nullptr;
	}
	QImage mask(rect.width(),rect.height(),QImage::Format_Mono);
	mask.fill(Qt::color1);
	for( int i=0;i<pixelClash.size();i++ )
	{
		QPoint relativ(pixelClash.at(i));
		relativ.setX( relativ.x() - rect.left() );
		relativ.setY( relativ.y() - rect.top() );
		mask.setPixel(relativ,Qt::color0);
	}

	QImage image(rect.width(),rect.height(),QImage::Format_RGB32);
	image.fill(color);

	QPixmap pixmap;
	pixmap.convertFromImage( image );
	pixmap.setMask( QBitmap::fromImage(mask,Qt::MonoOnly) );

	//TODO: Nicht schön, dass hier auf m_View->m_Scene zugegriffen wird!
	ProvinceGraphicsPixmapItem *item = new ProvinceGraphicsPixmapItem( pixmap, rect, scene );
	item->setOffset( rect.left(), rect.top() );
	return item;
}


bool HoIModDesigner::LoadOriginalMap( const QString& fileName )
{
	m_OriginalMap.load(fileName);
	if( m_OriginalMap.isNull() == true )
	{
		//Unable to load bitmap
		return false;
	}
	m_OriginalMap = m_OriginalMap.transformed(QTransform().rotate(180,Qt::XAxis));
	return true;
}

void HoIModDesigner::DisplayOriginalMap()
{
	m_View->m_Scene->clear();
	m_View->m_Scene->setSceneRect(0,0,m_OriginalMap.width(),m_OriginalMap.height());
	m_View->m_Scene->addPixmap(m_OriginalMap);
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
		
//	LoggingTableWidgetRow
// 	for( int i=0;i<100000;i++ )
// 	{
// 		jha::GetLog()->Log("Eine tolle neue Nachricht",jha::LogInterface::LOGLEVEL(i%8),QString().setNum(i));
// 	}
// 	m_View->m_Scene->clear();
// 	m_View->m_Scene->setSceneRect(0,0,m_ContourMap.width(),m_ContourMap.height());
// 	m_View->m_Scene->addPixmap(m_ContourMap);
}

void HoIModDesigner::DisplayItemMap()
{
	m_View->m_Scene->clear();
 	QHash<int,ProvinceItem*>::ConstIterator iter;
 	for( iter = m_ProvinceMapByRGB.constBegin(); iter != m_ProvinceMapByRGB.constEnd(); iter++ )
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

bool HoIModDesigner::ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const
{
// 	QCoreApplication::processEvents();
// 	QCoreApplication::flush();

	QFile file(provincePath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		//HJMessageManager::Instance()->DoPostMessage( HJMessage::mtERROR, QString("Datei konnte nicht geöffnet werden: ") +filepath );
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;

	ParseToLines( data, lines );
	mapRGB.reserve( lines.size() );
	mapID.reserve( lines.size() );

	for( int i=0;i<lines.size();i++ )
	{
		ProvinceItem* newItem = CreateProvinzeItemFromString( lines.at(i) );
		if( newItem == nullptr )
		{
			continue;
		}
		mapRGB.insert(newItem->m_Color.rgb(), newItem);
		mapID.insert(newItem->m_ID, newItem);
	}

	//m_ProvinceMap
	return mapRGB.isEmpty() == false;
}

//================================================================================
bool HoIModDesigner::ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath ) const
{
	QFile file(countryPath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		//HJMessageManager::Instance()->DoPostMessage( HJMessage::mtERROR, QString("Datei konnte nicht geöffnet werden: ") +filepath );
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;

	ParseToLines( data, lines );
	countryList.reserve( lines.size() );

	for( int i=0;i<lines.size();i++ )
	{
		Nation *newNation = CreateCountryFromString( lines.at(i) );
		if( newNation == nullptr )
		{
			continue;
		}
		countryList.insert(newNation->GetID(), newNation);
		ParseCountryDetailInfo( newNation->GetFilePath(), newNation );
	}

	return countryList.isEmpty() == false;
}

//================================================================================
bool HoIModDesigner::ParseCountryDetailInfo( const QString& filename, Nation* nation ) const
{
	if( filename.isEmpty() == true )
	{
		return false;
	}
	if( nation == nullptr )
	{
		return false;
	}

	QString path("E://Spiele//HoI3//common//");
	//TODO: Holt sich aktuell nur die Farbe raus ...
	QFile file(path +filename);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		//HJMessageManager::Instance()->DoPostMessage( HJMessage::mtERROR, QString("Datei konnte nicht geöffnet werden: ") +filepath );
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;
	ParseToLines( data, lines );

	//TODO: Dummyimplementierung. Holt nur die Farbe raus ...
	if( lines.isEmpty() == true )
	{
		return false;
	}

	QStringList items = lines.at(0).split(" ",QString::SkipEmptyParts);
	if( items.size() < 7 )
	{
		return false;
	}

	int r = items.at(3).toInt();
	int g = items.at(4).toInt();
	int b = items.at(5).toInt();

	nation->m_Color = QColor(r,g,b);
	return true;
}

//================================================================================
int HoIModDesigner::ParseToLines( const QByteArray& data, QStringList &lines ) const
{
	lines.clear();
	QString line;
	char CR('\r');
	char LF('\n');
	int size = data.size();
	for( int i=0;i<size;i++ )
	{
		char currentChar = data.at(i);
		if( currentChar == CR || currentChar == LF )
		{
			if( line.isEmpty() == true )
			{
				continue;
			}
			lines.append(line);
			line.clear();
			continue;
		}
		line.append(currentChar);
	}
	lines.append(line);
	return lines.size();
}

//================================================================================
ProvinceItem* HoIModDesigner::CreateProvinzeItemFromString( const QString& line ) const
{
	const QString columnSeparator(";");
	const unsigned int columns = 6;
	QStringList fields  = line.split(columnSeparator);
	if( fields.size() != columns )
	{
		//TODO: Log falsche Spaltenanzahl
		return nullptr;
	}

	bool conversionValid;
	int provinceID = fields.at(0).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 1 konnte nicht in ProvinzID konvertiert werden
		return nullptr;
	}

	int r = fields.at(1).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 2 konnte nicht in r konvertiert werden
		return nullptr;
	}

	int g = fields.at(2).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 3 konnte nicht in g konvertiert werden
		return nullptr;
	}

	int b = fields.at(3).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 4 konnte nicht in b konvertiert werden
		return nullptr;
	}

	QString name = fields.at(4);

	return new ProvinceItem(provinceID,name,QColor(r,g,b));
}


Nation* HoIModDesigner::CreateCountryFromString( const QString& line ) const
{
	const QString columnSeparator("=");
	const unsigned int columns = 2;
	QStringList fields  = line.split(columnSeparator);
	if( fields.size() != columns )
	{
		//TODO: Log falsche Spaltenanzahl
		return false;
	}

	QString nationID = fields.at(0);
	nationID = nationID.trimmed();
	if( nationID.size() != 3 )
	{
		//TODO: Wert aus Spalte 1 konnte nicht in ProvinzID konvertiert werden
		return false;
	}

	QString filePath = fields.at(1);
	filePath = filePath.trimmed();

	filePath = filePath.section("\"",1,1);
	if( filePath.isEmpty() == true )
	{
		//TODO: No country definition file
		return false;
	}

	return new Nation(nationID,filePath);
}

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
		m_DockWidgetNationList = new QTableWidget(150,2,dockCountry);

		QHeaderView *verticalHeader = m_DockWidgetNationList->verticalHeader();
		verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
		verticalHeader->setDefaultSectionSize(20);

		m_DockWidgetNationList->verticalHeader()->setVisible(false);
		m_DockWidgetNationList->setSelectionBehavior(QAbstractItemView::SelectRows);
		QTableWidgetItem *headerColumn1 = new QTableWidgetItem("ID");
		headerColumn1->setBackground(Qt::lightGray);
		m_DockWidgetNationList->setHorizontalHeaderItem( 0, headerColumn1 );

		QTableWidgetItem *headerColumn2 = new QTableWidgetItem("Name");
		headerColumn2->setBackground(Qt::lightGray);
		m_DockWidgetNationList->setHorizontalHeaderItem( 1, headerColumn2 );
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
		QDockWidget *dock = new QDockWidget(tr("Logging"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea );
		m_DockWidgetLogging = new LoggingTableWidget(0,0,dock);

		dock->setWidget( m_DockWidgetLogging );
		addDockWidget(Qt::BottomDockWidgetArea, dock);
		m_DockWidgetLogging->addAction(dock->toggleViewAction());
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
	widget->clearContents();
	if( nations.isEmpty() == true )
	{
		return;
	}

	int rowIndex = 0;
	QHash<QString,Nation*>::ConstIterator iter;
	for( iter = nations.constBegin(); iter != nations.constEnd(); iter++ )
	{
		widget->setItem(rowIndex, 0, new TableWidgetItemNation((*iter)->GetID(),(*iter)) );
		widget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
		
		QTableWidgetItem *countryPath = new TableWidgetItemNation((*iter)->GetFilePath(),(*iter));
		widget->setItem(rowIndex, 1, countryPath );
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

bool HoIModDesigner::ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem*>& provinceList, const QString& provincePath ) const
{
	QDir directory(provincePath);
	QFileInfoList infos = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	for( int i=0;i<infos.size();i++ )
	{
		if( infos.at(i).isFile()  )
		{
			if( infos.at(i).fileName() == "11391.txt" )
			{
				int wait = 0;
			}
			int provinceID = CreateProvinceIDFromFilename( infos.at(i).fileName() );
			if( provinceID == -1 )
			{
				provinceID = CreateProvinceIDFromFilename( infos.at(i).fileName(), "." );
				if( provinceID == -1 )
				{
					continue;
				}
				//TODO: provinceFileNames.at(i) not valid. contains no provinceID
			}

			QHash<int,ProvinceItem*>::iterator provinceItem = provinceItem = provinceList.find(provinceID);
			if( provinceItem == provinceList.end() )
			{
				//TODO: ProvinceID not found in province list from provinces.csv
				continue;
			}

			if( ParseProvinceDetailInfo( infos.at(i).absoluteFilePath(), provinceItem.value() ) == false )
			{
				//TODO: Unable to parse province detail info 
				continue;
			}
		}
		else
		{
			if( infos.at(i).isDir() == true )
			{
				ParseProvinceDetailInfoDirectory( provinceList, infos.at(i).filePath() );
			}
		}

	}
	return true;
}

bool HoIModDesigner::ParseProvinceDetailInfo( const QString& filename, ProvinceItem* provinceItem ) const
{
	if( provinceItem->m_ID == 11391 )
	{
		int wait = 0;
	}
	jha::GetLog()->Log("Parsing file: " +filename,jha::LogInterface::LL_INFO);
//  	QCoreApplication::processEvents();
//  	QCoreApplication::flush();
	QFile file(filename);
	if( file.open(QIODevice::ReadOnly /*| QIODevice::Text*/) == false )
	{
		//HJMessageManager::Instance()->DoPostMessage( HJMessage::mtERROR, QString("Datei konnte nicht geöffnet werden: ") +filepath );
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;
	ParseToLines( data, lines );

	QVector<QStringList> linesPerTimeline;
	if( SortLinesByTimeline( lines, linesPerTimeline ) == false )
	{
		//TODO: Was eigentlich?
		return false;
	}
	
	//TODO: Aktuell wird nur die BASE-Timeline ausgewertet
	QHash<QString,QString> tokenList;
	tokenList.insert("TIMELINE","BASE");
	if( CreateTokenMap( linesPerTimeline.at(0), tokenList ) == false )
	{
		//TODO: War wohl doch keine gültige Datei?!
		return false;
	}

	return CreateProvinceTimeLineData( tokenList, provinceItem );
}


bool HoIModDesigner::SortLinesByTimeline( const QStringList& data, QVector<QStringList>& timeLineParts ) const
{
	if( data.isEmpty() == true )
	{
		return false;
	}

	timeLineParts.push_back(QStringList());
	int currentIndex = 0;

	const QString timeLineStart("{");
	const QString timeLineEnd("}");
	for( int i=0; i<data.size(); i++ )
	{
		if( data.at(i).isEmpty() == true )
		{
			continue;
		}
		if( data.at(i).indexOf(timeLineStart) != -1 )
		{
			timeLineParts.push_back(QStringList(data.at(i)));
			if( data.at(i).indexOf(timeLineEnd) == -1 )  //{ und } können ja auch in einer Zeile stehen
			{
				currentIndex = timeLineParts.size()-1;
			}
			continue;
		}
		if( data.at(i).indexOf(timeLineEnd) != -1 )
		{
			timeLineParts[currentIndex].append(data.at(i));
			currentIndex = 0;
		}
		else
		{
			timeLineParts[currentIndex].append(data.at(i));
		}
	}
	return true;
}


bool HoIModDesigner::CreateTokenMap( const QStringList& lines, QHash<QString,QString> &tokens, const QString& separator ) const
{
	if( lines.isEmpty() == true )
	{
		return false;
	}

	for( int i=0;i<lines.size();i++ )
	{
		QStringList fields = lines.at(i).split(separator);
		const int expectedPartsCount = 2;
		if( fields.size() != expectedPartsCount )
		{
			continue;
		}
		if( fields.at(1).indexOf("{") == -1 )
		{
			//TODO: Doppelte Einträge?! add_core
			tokens.insert(fields.at(0).trimmed(),fields.at(1).trimmed());
		}
		else
		{
			//TOOD: Ist das schön??
			tokens.insert("TIMELINE",fields.at(0).trimmed());
		}

	}
	return true;
}

int HoIModDesigner::CreateProvinceIDFromFilename( const QString& filename, const QString& separator ) const
{
	if( filename.isEmpty() == true )
	{
		return -1;
	}

	//TODO: Analyzing file <filename>
	const unsigned int columns = 2;
	QStringList fields  = filename.split(separator);
	if( fields.isEmpty() == true )
	{
		//TODO: Not a valid Name <ID - Name.txt> <filename>
		return -1;
	}

	bool conversionValid;
	int provinceID = fields.at(0).trimmed().toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: No valid provinceid <filename>
		return -1;
	}
	return provinceID;
}

bool HoIModDesigner::CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem* data ) const
{
	if( tokens.isEmpty() == true )
	{
		return false;
	}

	if( data == nullptr )
	{
		return false;
	}

	if( data->m_ID == 11391 )
	{
		int wait = 0;
	}

	QString timeLine;
	if( UpdateTokenValue(tokens,"TIMELINE",timeLine) == false )
	{
		//TODO: Hmm da ist was falsch gelaufen ...
		return false;
	}
	ProvinceTimeLineData timeLineData(timeLine.trimmed());

	if( UpdateTokenValue(tokens,"owner",timeLineData.m_Owner) == false )
	{
		//TODO: Hmm Provinz ohne controller
		return false;
	}

	if( UpdateTokenValue(tokens,"controller",timeLineData.m_Controller) == false )
	{
		//TODO: Hmm Provinz ohne controller
		return false;
	}

	UpdateTokenValue(tokens,"points",timeLineData.m_Points);
	UpdateTokenValue(tokens,"metal",timeLineData.m_Metal);
	UpdateTokenValue(tokens,"energy",timeLineData.m_Energy);
	UpdateTokenValue(tokens,"rare_materials",timeLineData.m_RareMaterials);
	UpdateTokenValue(tokens,"crude_oil",timeLineData.m_CrudeOil);
	UpdateTokenValue(tokens,"industry",timeLineData.m_Industry);
	UpdateTokenValue(tokens,"anti_air",timeLineData.m_AntiAir);
	UpdateTokenValue(tokens,"infra",timeLineData.m_Infrastructure);
	UpdateTokenValue(tokens,"air_base",timeLineData.m_AirBases);
	UpdateTokenValue(tokens,"naval_base",timeLineData.m_NavalBase);
	UpdateTokenValue(tokens,"manpower",timeLineData.m_Manpower);
	UpdateTokenValue(tokens,"leadership",timeLineData.m_LeaderShip);

	data->m_TimeLineData.push_back(timeLineData);
	return true;
}

bool HoIModDesigner::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, int& valueToUpadte ) const
{
	QString tempValue;
	if( UpdateTokenValue(tokens,tokenName,tempValue) == false )
	{
		return false;
	}

	bool conversionValid;
	int temp = tempValue.trimmed().toInt(&conversionValid);
	if( conversionValid == false )
	{
		return false;
	}
	
	valueToUpadte = temp;

	return true;
}

bool HoIModDesigner::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, double& valueToUpadte ) const
{
	QString tempValue;
	if( UpdateTokenValue(tokens,tokenName,tempValue) == false )
	{
		return false;
	}

	bool conversionValid;
	double temp = tempValue.trimmed().toDouble(&conversionValid);
	if( conversionValid == false )
	{
		return false;
	}

	valueToUpadte = temp;

	return true;
}

bool HoIModDesigner::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, QString& valueToUpadte ) const
{
	QHash<QString,QString>::const_iterator token = tokens.find(tokenName);
	if( token == tokens.end() )
	{
		return false;
	}

	valueToUpadte = token.value();
	return true;
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

void HoIModDesigner::ShowIndustryColorMap()
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

		if( item->GetAttachedProvinceItem()->m_TimeLineData.at(0).m_Industry <= 0 )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}
		item->UpdateColor(Qt::green);
	}
	m_View->setVisible(true);
}

void HoIModDesigner::ShowMetalColorMap()
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

		if( item->GetAttachedProvinceItem()->m_TimeLineData.at(0).m_Metal <= 0 )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}
		item->UpdateColor(Qt::green);
	}
	m_View->setVisible(true);
}

void HoIModDesigner::ShowCrudeOilColorMap()
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

		if( item->GetAttachedProvinceItem()->m_TimeLineData.at(0).m_CrudeOil <= 0 )
		{
			item->UpdateColor(Qt::lightGray);
			continue;
		}
		item->UpdateColor(Qt::green);
	}
	m_View->setVisible(true);
}


void HoIModDesigner::ClearProvinceItems()
{
	QHash<int,ProvinceItem*>::Iterator iter;
	for( iter = m_ProvinceMapByID.begin(); iter != m_ProvinceMapByID.end(); iter++ )
	{
		delete (*iter);
	}
	m_ProvinceMapByRGB.clear();
	m_ProvinceMapByID.clear();
}

void HoIModDesigner::ClearNations()
{
	QHash<QString,Nation*>::Iterator nations;
	for( nations = m_Nations.begin(); nations != m_Nations.end(); nations++ )
	{
		delete (*nations);
	}
	m_Nations.clear();
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
