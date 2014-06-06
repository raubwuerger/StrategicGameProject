#include "stdafx.h"
#include "hoimoddesigner.h"
#include "PolygonHelper.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "ProvinceItem.h"
#include "ExtendedGraphicsView.h"
#include "ExtendedGraphicsScene.h"
#include "Nation.h"

HoIModDesigner::HoIModDesigner(QWidget *parent)
	: QMainWindow(parent),
	m_DockWidgetNationList(nullptr)
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

	m_MapFilterToolBar = addToolBar(tr("Map filter"));
	m_MapFilterToolBar->addAction(m_ShowOriginalMap);
	m_MapFilterToolBar->addAction(m_ShowNationColorMap);

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
	
	QToolButton *button4 = new QToolButton;
	button4->setText("Testicon4");
	button4->setIcon(QIcon(":HoIModDesigner/images/add2.ico"));
	button4->setIconSize(QSize(48, 48));
	button4->setCheckable(true);
	connect(button4,SIGNAL(clicked()),this,SLOT(DisplayContourSortedMap()));

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
	layout->addWidget(button4, 3, 0, Qt::AlignHCenter);
	layout->addWidget(button5, 4, 0, Qt::AlignHCenter);

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
}

HoIModDesigner::~HoIModDesigner()
{

}

bool HoIModDesigner::CreateColorMap( QHash<int,ProvinceItem>& result )
{
	QImage mapImage = m_OriginalMap.toImage();
	if( mapImage.isNull() == true )
	{
		//Unable to transform bitmap
		return false;
	}

// 	int smooth1 = Smooth(mapImage,3);
// 	int smooth2 = Smooth(mapImage,3);
// 	int smooth3 = Smooth(mapImage,3);

	int width   = mapImage.width();
	int height  = mapImage.height();
	for( int i=0;i<height;i++ )
	{
		for( int j=0;j<width;j++ )
		{
// 			if( PolygonHelper().CalcNeigboursColorCount(QPoint(j,i),mapImage) == 8 )
// 			{
// 				continue;
// 			}

			QRgb color = mapImage.pixel( j, i );
			QHash<int,ProvinceItem>::iterator found = result.find( color );

			if( found == result.end() )
			{
				//TODO: Kein Eintrag in definition.csv für  Farbcode <x,y,z> aus provinces.bmp
				continue;
			}
			found.value().m_Contour.append( QPoint(j,i) );
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

	m_ProvinceMapByRGB.clear();
	m_ProvinceMapByID.clear();
	QString pathDefinitionCSV("E:\\Spiele\\HoI3\\map\\definition.csv");
	ParseProvinzList(m_ProvinceMapByRGB,m_ProvinceMapByID,pathDefinitionCSV);

	QString pathCountriesTXT("E:\\Spiele\\HoI3\\common\\countries.txt");
	ParseCountryList(m_Nations,pathCountriesTXT);
	FillNationList(m_Nations,m_DockWidgetNationList);
	FillProvinceList(m_ProvinceMapByID,m_DockWidgetProvinceList);

	QString pathProvinceDetailInfos("E:\\Spiele\\HoI3\\history\\provinces");
	ParseProvinceDetailInfoDirectory( m_ProvinceMapByID, pathProvinceDetailInfos );
	
	CreateColorMap(m_ProvinceMapByRGB);
	CreateGraphicsItems(m_ProvinceMapByRGB);
	DisplayItemMap();
// 	CreateContourImage(m_ProvinceMapByRGB,m_ContourMap);
// 	CreateContourPolygons(m_ProvinceMapByRGB);
// 	OversampleContourPixel(m_ProvinceMapByRGB);
// 	CreateContourSortedMap(m_ProvinceMapByRGB,m_ContourSortedMap);
}

void HoIModDesigner::CreateGraphicsItems( QHash<int,ProvinceItem>& result ) const
{
	QHash<int,ProvinceItem>::Iterator iter;
	for( iter = result.begin(); iter != result.end(); iter++ )
	{
		iter->m_GraphicsItem = CreateItemFromPixelClash(iter->m_Contour,iter->m_Color, m_View->m_Scene );
		if( iter->m_GraphicsItem == nullptr )
		{
			continue;
		}
		if( iter.value().m_ID == 1737 )
		{
			int wait_hamburg = 0;
		}
//		iter->m_GraphicsItem->SetAttachedProvinceItem(&(iter.value()));
		iter->m_GraphicsItem->SetAttachedProvinceItem( &(m_ProvinceMapByID.find(iter.value().m_ID).value()) );
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
	m_View->m_Scene->clear();
	m_View->m_Scene->setSceneRect(0,0,m_ContourMap.width(),m_ContourMap.height());
	m_View->m_Scene->addPixmap(m_ContourMap);
}

void HoIModDesigner::DisplayContourSortedMap()
{
	QPixmap provinceItem(20,20);
	provinceItem.fill(Qt::red);
	
	QImage maskImage(20,20,QImage::Format_Mono);
	maskImage.fill(Qt::color0);
	int colorCount = maskImage.colorCount();
	QVector<QRgb> colorTable = maskImage.colorTable();
	for( int i=4;i<10;i++ )
	{
		for( int j=4;j<10;j++ )
		{
			maskImage.setPixel(i,j,Qt::color1);
		}
	}
	provinceItem.setMask( QBitmap::fromImage(maskImage,Qt::MonoOnly) );
	m_View->m_Scene->addPixmap(provinceItem);
}

void HoIModDesigner::DisplayItemMap()
{
	m_View->m_Scene->clear();
 	QHash<int,ProvinceItem>::ConstIterator iter;
 	for( iter = m_ProvinceMapByRGB.constBegin(); iter != m_ProvinceMapByRGB.constEnd(); iter++ )
 	{
		if( iter->m_GraphicsItem == nullptr )
		{
			continue;
		}
		ProvinceGraphicsPixmapItem *copiedItem = new ProvinceGraphicsPixmapItem(*(iter->m_GraphicsItem));
		QPointF offset = copiedItem->offset();
		m_View->m_Scene->addItem( copiedItem );
	}
}

bool HoIModDesigner::CreateContourImage( QHash<int,ProvinceItem>& result, QPixmap& pixmap )
{
	pixmap = QPixmap(m_OriginalMap.width(),m_OriginalMap.height());
	pixmap.fill(Qt::yellow);
	QImage tempImage(pixmap.toImage());
	tempImage.fill(Qt::white);
	
	QHash<int,ProvinceItem>::ConstIterator iter;
	for( iter = result.constBegin();iter != result.constEnd();iter++ )
	{
		QRgb color = iter.key();
		for( int i=0;i<iter->m_Contour.size();i++ )
		{
			tempImage.setPixel(iter->m_Contour.at(i),color);
		}
	}
	pixmap.convertFromImage(tempImage);
	return true;
}

bool HoIModDesigner::CreateContourSortedMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap )
{
// 	pixmap = QPixmap(m_OriginalMap.width(),m_OriginalMap.height());
// 	pixmap.fill(Qt::yellow);
// 	QImage tempImage(pixmap.toImage());
// 	tempImage.fill(Qt::white);
// 
// 	QHash<int,ProvinceItem>::ConstIterator iter;
// 	for( iter = result.constBegin();iter != result.constEnd();iter++ )
// 	{
// 		QRgb color = iter.key();
// 		for( int i=0;i<iter->m_SortedContours.size();i++ )
// 		{
// 			for( int j=0;j<iter->m_SortedContours.at(i).size();j++ )
// 			{
// 				tempImage.setPixel((iter->m_SortedContours.at(i).at(j)).toPoint(),color);
// 			}
// 		}
// 	}
// 	pixmap.convertFromImage(tempImage);
// 	return true;
	return false;
}

bool HoIModDesigner::CreateContourPolygons( QHash<int,ProvinceItem>& result ) const
{
/*
// 	QImage mapImage = m_OriginalMap.toImage();
// 	QHash<int,ProvinceItem>::Iterator iter;
// 	for( iter = result.begin(); iter != result.end(); iter++ )
// 	{
// 		QPolygon pointsToSort(iter->m_Contour);
// 		while( pointsToSort.isEmpty() == false )
// 		{
// 			iter->m_SortedContours.push_back(PolygonHelper().SortToProvinceContourFlip(pointsToSort));
// 		}
// 	}
// 
// 	return true;
*/
	return false;
}

bool HoIModDesigner::ParseProvinzList( QHash<int,ProvinceItem>& mapRGB, QHash<int,ProvinceItem>& mapID, const QString& provincePath ) const
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
		ProvinceItem item;
		if( CreateProvinzeItemFromString( lines.at(i), item ) == false )
		{
			continue;
		}
		mapRGB.insert(item.m_Color.rgb(), item);
		mapID.insert(item.m_ID, item);
	}

	//m_ProvinceMap
	return mapRGB.isEmpty() == false;
}

//================================================================================
bool HoIModDesigner::ParseCountryList( QHash<QString,Nation>& countryList, const QString& countryPath ) const
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
		Nation nation;
		if( CreateNationFromString( lines.at(i), nation ) == false )
		{
			continue;
		}
		countryList.insert(nation.GetID(), nation);
	}

	return countryList.isEmpty() == false;
}


//================================================================================
int HoIModDesigner::ParseToLines( const QByteArray& data, QStringList &lines ) const
{
	lines.clear();
	QString line;
	char LE('\n');
	int size = data.size();
	for( int i=0;i<size;i++ )
	{
		char currentChar = data.at(i);
		if( currentChar == LE )
		{
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
bool HoIModDesigner::CreateProvinzeItemFromString( const QString& line, ProvinceItem& item ) const
{
	const QString columnSeparator(";");
	const unsigned int columns = 6;
	QStringList fields  = line.split(columnSeparator);
	if( fields.size() != columns )
	{
		//TODO: Log falsche Spaltenanzahl
		return false;
	}

	bool conversionValid;
	int provinceID = fields.at(0).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 1 konnte nicht in ProvinzID konvertiert werden
		return false;
	}

	int r = fields.at(1).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 2 konnte nicht in r konvertiert werden
		return false;
	}

	int g = fields.at(2).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 3 konnte nicht in g konvertiert werden
		return false;
	}

	int b = fields.at(3).toInt(&conversionValid);
	if( conversionValid == false )
	{
		//TODO: Wert aus Spalte 4 konnte nicht in b konvertiert werden
		return false;
	}

	QString name = fields.at(4);

	item = ProvinceItem(provinceID,name,QColor(r,g,b));

	return true;
}


bool HoIModDesigner::CreateNationFromString( const QString& line, Nation& nation ) const
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

// 	int startQuote = filePath.indexOf("\"");
// 	int endQuote = filePath.lastIndexOf("\"");
// 	if( startQuote == -1 || endQuote == -1 || startQuote == endQuote )
// 	{
// 		//TODO: No country definition file
// 		return false;
// 	}
	filePath = filePath.section("\"",1,1);
	if( filePath.isEmpty() == true )
	{
		//TODO: No country definition file
		return false;
	}

	nation = Nation(nationID,filePath);
	return true;
}

int HoIModDesigner::Smooth( QImage &mapImage, int level /*= 3 */ )
{
	int width   = mapImage.width();
	int height  = mapImage.height();
	int count = 0;
	//Remove inclusions
	for( int i=0;i<height;i++ )
	{
		for( int j=0;j<width;j++ )
		{
			QPoint current(j,i);
			int neigboursOfSameColor = PolygonHelper().CalcNeigboursColorCount(current,mapImage);
			if( neigboursOfSameColor <= level )
			{
				if( SmoothColor(mapImage, current, QPoint(j+1,i) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j-1,i) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j+1,i+1) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j-1,i-1) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j,i+1) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j,i-1) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j+1,i-1) ) == true )
				{
					count++;
				}
				else if( SmoothColor(mapImage, current, QPoint(j-1,i+1) ) == true )
				{
					count++;
				}
			}

		}
	}
	return count;
}

bool HoIModDesigner::SmoothColor( QImage &mapImage, const QPoint& org, const QPoint& updateFrom )
{
	if( mapImage.valid(updateFrom) == false )
	{
		return false;
	}

	QRgb myColor = mapImage.pixel( org );
	if( myColor == mapImage.pixel(updateFrom) )
	{
		return false;
	}

	mapImage.setPixel(org,mapImage.pixel(updateFrom));
	return true;
}

void HoIModDesigner::CreateDockWidgets()
{
	{
		QDockWidget *dock = new QDockWidget(tr("Province detail list"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetProvinceDetails = new QTableWidget(16,2,dock);
		for( int i=0;i<16;i++ )
		{
			//TODO: Geht doch bestimmt einfacher
			m_DockWidgetProvinceDetails->setRowHeight( i, 20 );
		}
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
		for( int i=0;i<150;i++ )
		{
			//TODO: Geht doch bestimmt einfacher
			m_DockWidgetNationList->setRowHeight( i, 20 );
		}
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
		QDockWidget *dock = new QDockWidget(tr("Province list"), this);
		dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
		m_DockWidgetProvinceList = new QTableWidget(15000,2,dock);
		for( int i=0;i<15000;i++ )
		{
			//TODO: Geht doch bestimmt einfacher
			m_DockWidgetProvinceList->setRowHeight( i, 20 );
		}
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
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(QString().setNum(item->m_ID) ) );

	m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Name") );
	m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
	m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(item->m_Name) );

	//TODO: Nur BASE-Datensatz
	if( item->m_TimeLineData.isEmpty() == false )
	{
		const ProvinceTimeLineData& data = item->m_TimeLineData.at(0);

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Owner") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(data.m_Owner ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Controller") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem(data.m_Controller ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Points") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Points) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Manpower") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Manpower,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Leadership") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_LeaderShip,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Energy") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Energy,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Metal") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Metal,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Rare materials") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_RareMaterials,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Cruide Oil") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_CrudeOil,'g',2) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Industry") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Industry) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Infrastructure") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_Infrastructure) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Anti air") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_AntiAir) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Air bases") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_AirBases) ) );

		m_DockWidgetProvinceDetails->setItem(index, 0, new QTableWidgetItem("Naval bases") );
		m_DockWidgetProvinceDetails->item(index,0)->setTextAlignment(Qt::AlignRight);
		m_DockWidgetProvinceDetails->setItem(index++, 1, new QTableWidgetItem( QString().setNum(data.m_NavalBase) ) );
	}
}

void HoIModDesigner::FillNationList( const QHash<QString,Nation>& nations, QTableWidget* widget )
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
	QHash<QString,Nation>::ConstIterator iter;
	for( iter = nations.constBegin(); iter != nations.constEnd(); iter++ )
	{
		widget->setItem(rowIndex, 0, new QTableWidgetItem(iter->GetID()) );
		widget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
		widget->setItem(rowIndex, 1, new QTableWidgetItem(iter->GetFilePath()) );
		rowIndex++;
	}
}

void HoIModDesigner::FillProvinceList( QHash<int,ProvinceItem>& provinces, QTableWidget* widget )
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
	QHash<int,ProvinceItem>::ConstIterator iter;
	for( iter = provinces.constBegin(); iter != provinces.constEnd(); iter++ )
	{
		if( iter->m_Name.isEmpty() == true )
		{
			continue;
		}
		widget->setItem(rowIndex, 0, new QTableWidgetItem(QString().setNum(iter->m_ID)) );
		widget->item(rowIndex,0)->setTextAlignment(Qt::AlignCenter);
		widget->setItem(rowIndex, 1, new QTableWidgetItem(iter->m_Name) );
		rowIndex++;
	}
}

bool HoIModDesigner::ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem>& provinceList, const QString& provincePath ) const
{
	QDir directory(provincePath);
	QFileInfoList infos = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	for( int i=0;i<infos.size();i++ )
	{
		if( infos.at(i).isFile()  )
		{
			int provinceID = CreateProvinceIDFromFilename( infos.at(i).fileName() );
			if( provinceID == -1 )
			{
				//TODO: provinceFileNames.at(i) not valid. contains no provinceID
				continue;
			}

			QHash<int,ProvinceItem>::iterator provinceItem = provinceItem = provinceList.find(provinceID);
			if( provinceItem == provinceList.end() )
			{
				//TODO: ProvinceID not found in province list from provinces.csv
				continue;
			}

			if( provinceID == 1737 )
			{
				int wait_for_hamb = 0;
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

bool HoIModDesigner::ParseProvinceDetailInfo( const QString& filename, ProvinceItem& provinceItem ) const
{
	QFile file(filename);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		//HJMessageManager::Instance()->DoPostMessage( HJMessage::mtERROR, QString("Datei konnte nicht geöffnet werden: ") +filepath );
		return false;
	}

	if( provinceItem.m_ID == 2137 )
	{
		int wait = 0;
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

int HoIModDesigner::CreateProvinceIDFromFilename( const QString& filename ) const
{
	if( filename.isEmpty() == true )
	{
		return -1;
	}

	//TODO: Analyzing file <filename>
	const QString separator("-");
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

bool HoIModDesigner::CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem& data ) const
{
	if( tokens.isEmpty() == true )
	{
		return false;
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

	data.m_TimeLineData.push_back(timeLineData);
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
	QHash<int,ProvinceItem>::iterator iter;
	for( iter = m_ProvinceMapByRGB.begin(); iter != m_ProvinceMapByRGB.end(); iter++ )
	{
		if( iter->m_GraphicsItem == nullptr )
		{
			continue;
		}
		iter->m_GraphicsItem->ShowOriginal();
	}
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
		item->UpdateColor(Qt::red);
	}
	m_View->setVisible(true);
}
