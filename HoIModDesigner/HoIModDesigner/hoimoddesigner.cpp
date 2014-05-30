#include "stdafx.h"
#include "hoimoddesigner.h"
#include "PolygonHelper.h"

HoIModDesigner::HoIModDesigner(QWidget *parent)
	: QMainWindow(parent)
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

	m_HilfeMenu = menuBar()->addMenu(tr("Help"));
	m_HilfeMenu->addAction( m_AboutAction );

	m_FileToolBar = addToolBar(tr("Edit"));
	m_FileToolBar->addAction(m_ExitAction);
	m_FileToolBar->addAction(m_LoadMapAction);

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
	
	QToolButton *button3 = new QToolButton;
	button3->setText("Testicon3");
	button3->setIcon(QIcon(":HoIModDesigner/images/add2.ico"));
	button3->setIconSize(QSize(48, 48));
	button3->setCheckable(true);
	connect(button3,SIGNAL(clicked()),this,SLOT(DisplayContourSecondChanceMap()));

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
	layout->addWidget(button3, 2, 0, Qt::AlignHCenter);
	layout->addWidget(button4, 3, 0, Qt::AlignHCenter);
	layout->addWidget(button5, 4, 0, Qt::AlignHCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	m_Scene = new QGraphicsScene(this);
	m_Scene->setSceneRect(QRectF(0, 0, 5000, 5000));

	QGridLayout *backgroundLayout = new QGridLayout;
	backgroundLayout->addWidget(widget, 0, 0);

	m_ToolBox = new QToolBox;
	m_ToolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	m_ToolBox->setMinimumWidth(widget->sizeHint().width());
	m_ToolBox->addItem(widget, tr("First group"));
//	m_ToolBox->addItem(backgroundWidget, tr("Backgrounds"));

// 	connect(scene, SIGNAL(itemInserted(DiagramItem*)),
// 		this, SLOT(itemInserted(DiagramItem*)));
// 	connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
// 		this, SLOT(textInserted(QGraphicsTextItem*)));
// 	connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
// 		this, SLOT(itemSelected(QGraphicsItem*)));
// 	createToolbars();
//	QMenu *itemMenu;


	QHBoxLayout *layoutMain = new QHBoxLayout;
	layoutMain->addWidget(m_ToolBox);
	m_View = new QGraphicsView(m_Scene);
	layoutMain->addWidget(m_View);

	QWidget *widgetMain = new QWidget;
	widgetMain->setLayout(layoutMain);

	setCentralWidget(widgetMain);
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

	int width   = mapImage.width();
	int height  = mapImage.height();

	for( int i=0;i<height;i++ )
	{
		for( int j=0;j<width;j++ )
		{
			bool hasOneForeigner = PolygonHelper().IsMiddlePoint(QPoint(j,i),mapImage,1);
			bool hasOnlyFriends = PolygonHelper().IsMiddlePoint(QPoint(j,i),mapImage,0);

			if( hasOnlyFriends == true )
			{
				continue;
			}

			QRgb color = mapImage.pixel( j, i );
			QHash<int,ProvinceItem>::iterator found = result.find( color );

			if( found == result.end() )
			{
				//TODO: Kein Eintrag in definition.csv für  Farbcode <x,y,z> aus provinces.bmp
				continue;
			}
			if( hasOneForeigner == true )
			{
				found.value().m_ContourSecondChance.append( QPoint(j,i) );
			}
			else
			{
				found.value().m_Contour.append( QPoint(j,i) );
			}
		}
	}
	return result.isEmpty() == false;
}

void HoIModDesigner::LoadMap()
{
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Siziliy2.bmp");
	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Siziliy.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Rectangle.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Abstrakt.bmp");
//	QString mapName("D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media\\Test_Rectangle_4.bmp");
	
//	QString mapName("D:\\Spiele\\HoI3\\map\\provinces.bmp");
//	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "D:\\Projects\\StrategicGameProject\\HoIModDesigner\\HoIModDesigner\\media", tr("Image Files (*.png *.jpg *.bmp)"));
	LoadOriginalMap(mapName);

	QString pathDefinitionCSV("D:\\Spiele\\HoI3\\map\\definition.csv");

	ReadProvinzList(m_ProvinceMapByRGB,pathDefinitionCSV);

	CreateColorMap(m_ProvinceMapByRGB);
	CreateContourMap(m_ProvinceMapByRGB,m_ContourMap);
	CreateContourSecondChanceMap(m_ProvinceMapByRGB,m_ContourSecondChanceMap);
	CreateContourPolygons(m_ProvinceMapByRGB);
	CreateContourSortedMap(m_ProvinceMapByRGB,m_ContourSortedMap);
	m_View->scale(8.0,8.0);
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
	m_Scene->clear();
	m_Scene->setSceneRect(0,0,m_OriginalMap.width(),m_OriginalMap.height());
	m_Scene->addPixmap(m_OriginalMap);
}

void HoIModDesigner::DisplayContourMap()
{
	m_Scene->clear();
	m_Scene->setSceneRect(0,0,m_ContourMap.width(),m_ContourMap.height());
	m_Scene->addPixmap(m_ContourMap);
}

void HoIModDesigner::DisplayContourSecondChanceMap()
{
	m_Scene->clear();
	m_Scene->setSceneRect(0,0,m_ContourSecondChanceMap.width(),m_ContourSecondChanceMap.height());
	m_Scene->addPixmap(m_ContourSecondChanceMap);
}

void HoIModDesigner::DisplayContourSortedMap()
{
	m_Scene->clear();
	m_Scene->setSceneRect(0,0,m_ContourSortedMap.width(),m_ContourSortedMap.height());
	m_Scene->addPixmap(m_ContourSortedMap);
}

void HoIModDesigner::DisplayItemMap()
{
	m_Scene->clear();
	QHash<int,ProvinceItem>::ConstIterator iter;
	for( iter = m_ProvinceMapByRGB.constBegin(); iter != m_ProvinceMapByRGB.constEnd(); iter++ )
	{
		for( int j=0;j<iter->m_SortedContours.size();j++)
		{
			QGraphicsPolygonItem *item = new QGraphicsPolygonItem(iter->m_SortedContours.at(j));
			item->setPen( QPen( iter->m_Color) );
			m_Scene->addItem( item );
		}
	}
}

bool HoIModDesigner::CreateContourMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap )
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

bool HoIModDesigner::CreateContourSecondChanceMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap )
{
	pixmap = QPixmap(m_OriginalMap.width(),m_OriginalMap.height());
	pixmap.fill(Qt::yellow);
	QImage tempImage(pixmap.toImage());
	tempImage.fill(Qt::white);

	QHash<int,ProvinceItem>::ConstIterator iter;
	for( iter = result.constBegin();iter != result.constEnd();iter++ )
	{
		QRgb color = iter.key();
		for( int i=0;i<iter->m_ContourSecondChance.size();i++ )
		{
			tempImage.setPixel(iter->m_ContourSecondChance.at(i),color);
		}
	}
	pixmap.convertFromImage(tempImage);
	return true;
}

bool HoIModDesigner::CreateContourSortedMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap )
{
	pixmap = QPixmap(m_OriginalMap.width(),m_OriginalMap.height());
	pixmap.fill(Qt::yellow);
	QImage tempImage(pixmap.toImage());
	tempImage.fill(Qt::white);

	QHash<int,ProvinceItem>::ConstIterator iter;
	for( iter = result.constBegin();iter != result.constEnd();iter++ )
	{
		QRgb color = iter.key();
		for( int i=0;i<iter->m_SortedContours.size();i++ )
		{
			for( int j=0;j<iter->m_SortedContours.at(i).size();j++ )
			{
				tempImage.setPixel((iter->m_SortedContours.at(i).at(j)).toPoint(),color);
			}
		}
	}
	pixmap.convertFromImage(tempImage);
	return true;
}

bool HoIModDesigner::CreateContourPolygons( QHash<int,ProvinceItem>& result ) const
{
	QImage mapImage = m_OriginalMap.toImage();
	QHash<int,ProvinceItem>::Iterator iter;
	for( iter = result.begin(); iter != result.end(); iter++ )
	{
		QPolygon pointsToSort(iter->m_Contour);
		QPolygon pointsToSortSecondChance(iter->m_ContourSecondChance);
		while( pointsToSort.isEmpty() == false )
		{
			iter->m_SortedContours.push_back(PolygonHelper().SortToProvinceContour(pointsToSort,pointsToSortSecondChance));
		}
	}

	return true;
}

bool HoIModDesigner::ReadProvinzList( QHash<int,ProvinceItem>& provinzList, const QString& provincePath ) const
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
	provinzList.reserve( lines.size() );

	for( int i=0;i<lines.size();i++ )
	{
		ProvinceItem item;
		if( CreateProvinzeItemFromString( lines.at(i), item ) == false )
		{
			continue;
		}
		provinzList.insert(item.m_Color.rgb(), item);
	}

	//m_ProvinceMap
	return provinzList.isEmpty() == false;
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
