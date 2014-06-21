#include "stdafx.h"
#include "ParserHoI3.h"
#include "std\LogInterface.h"
#include "ProvinceItem.h"
#include "Nation.h"
#include "PolygonHelper.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "HoI3Context.h"
#include "HoI3Scriptparser.h"
#include "HoI3Scriptparser.h"
#include "BuildingItem.h"
#include "HoI3Context.h"


ParserHoI3::ParserHoI3( ExtendedGraphicsScene *scene, HoI3Context *context )
	: m_Scene(scene),
	m_Context(context)
{
	BuildingItemPrototypeRepository().Init();
	ProvinceItemPrototypeRepository().Init();
}

void ParserHoI3::Parse()
{
	if( m_Context == nullptr )
	{
		return;
	}
	QPixmap *map = LoadProvincesBMP(m_Context->GetPathProvinceBMP());
	if( map == nullptr )
	{
		emit Finished();
		moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
		return;
	}

	QHash<int,ProvinceItem*>	provinceMapByRGB;
	ParseProvinzList(provinceMapByRGB,m_Context->m_ProvinceMap,m_Context->GetPathDefinitionCSV());

 	ParseCountryList(m_Context->m_Countries,m_Context->GetPathCountriesTXT(),m_Context->GetPathCommonDir());
 
	QVector<QString> provinceDirPaths = m_Context->GetPathProvincesDir();
	for( int i=0;i<provinceDirPaths.size();i++ )
	{
		ParseProvinceDetailInfoDirectory( m_Context->m_ProvinceMap, provinceDirPaths.at(i) );
	}

 	AttachProvincesToNations( m_Context->m_ProvinceMap, m_Context->m_Countries );

	if( CreateColorMap(provinceMapByRGB,map) == false )
	{
		emit Finished();
		moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
		return;
	}
 	CreateGraphicsItems(provinceMapByRGB,m_Scene);

	if( ParseBuildingsTXT( m_Context->m_BuildingTypes, m_Context->GetPathBuildingsTXT() ) == false )
	{
		jha::GetLog()->Log( "Unable to parse: " +m_Context->GetPathBuildingsTXT(), LEVEL::LL_ERROR );
	}

	jha::GetLog()->Log( "Finished parsing HoI3 context: " +m_Context->m_ModPath, LEVEL::LL_MESSAGE );

	emit Finished();
	moveToThread(QApplication::instance()->thread()); //Muss sich selber zurückschieben (push, not pull!)
}

QPixmap* ParserHoI3::LoadProvincesBMP( const QString& fileName )
{
	jha::GetLog()->Log("Loading file: " +fileName, LEVEL::LL_INFO);
	QPixmap *newPixmap = new QPixmap;
	newPixmap->load(fileName);
	if( newPixmap->isNull() == true )
	{
		jha::GetLog()->Log("Unable to load file: " +fileName, LEVEL::LL_ERROR);
		delete newPixmap;
		return nullptr;
	}
	newPixmap->operator=( newPixmap->transformed(QTransform().rotate(180,Qt::XAxis)) );
	return newPixmap;
}

bool ParserHoI3::ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const
{
	jha::GetLog()->Log("Loading file: " +provincePath, LEVEL::LL_INFO);
	QFile file(provincePath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +provincePath, LEVEL::LL_ERROR);
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

	jha::GetLog()->Log("Created province items: " +QString().setNum(mapRGB.size()), LEVEL::LL_INFO);
	//m_ProvinceMap
	return mapRGB.isEmpty() == false;
}

//================================================================================
int ParserHoI3::ParseToLines( const QByteArray& data, QStringList &lines ) const
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
			if( line.trimmed().isEmpty() == true )
			{
				continue;
			}
			lines.append(line);
			line.clear();
			continue;
		}
		line.append(currentChar);
	}
	if( line.trimmed().isEmpty() == false )
	{
		lines.append(line);
	}
	return lines.size();
}

//================================================================================
ProvinceItem* ParserHoI3::CreateProvinzeItemFromString( const QString& line ) const
{
	if( line.trimmed().isEmpty() == true )
	{
		return nullptr;
	}
	const QString columnSeparator(";");
	const unsigned int columns = 6;
	QStringList fields  = line.split(columnSeparator);
	if( fields.size() != columns )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, LEVEL::LL_WARNING);
		return nullptr;
	}

	bool conversionValid;
	int provinceID = fields.at(0).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, LEVEL::LL_WARNING);
		return nullptr;
	}

	int r = fields.at(1).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, LEVEL::LL_WARNING);
		return nullptr;
	}

	int g = fields.at(2).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, LEVEL::LL_WARNING);
		return nullptr;
	}

	int b = fields.at(3).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, LEVEL::LL_WARNING);
		return nullptr;
	}

	QString name = fields.at(4);

	return ProvinceItemPrototypeRepository().CreateProvinceItem(provinceID,name,QColor(r,g,b));
}

//================================================================================
bool ParserHoI3::ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath, const QVector<QString>& pathCountryDetails ) const
{
	jha::GetLog()->Log("Loading file: " +countryPath, LEVEL::LL_INFO);
	QFile file(countryPath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +countryPath, LEVEL::LL_ERROR);
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

		//TODO: Hack für TFH.Da muss ich mir noch was anderes überlegen
		if( ParseCountryDetailInfo( pathCountryDetails.at(0) + newNation->GetFilePath(), newNation ) == false)
		{
			if( pathCountryDetails.size() > 1 )
			{
				ParseCountryDetailInfo( pathCountryDetails.at(1) + newNation->GetFilePath(), newNation );
			}
		}
	}

	jha::GetLog()->Log("Created countries: " +QString().setNum(countryList.size()), LEVEL::LL_INFO);
	return countryList.isEmpty() == false;
}

//================================================================================
Nation* ParserHoI3::CreateCountryFromString( const QString& line ) const
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

//================================================================================
bool ParserHoI3::ParseCountryDetailInfo( const QString& filename, Nation* nation ) const
{
	if( filename.isEmpty() == true )
	{
		return false;
	}
	if( nation == nullptr )
	{
		return false;
	}

	jha::GetLog()->Log("Loading file: " +filename, LEVEL::LL_INFO);
	//TODO: Holt sich aktuell nur die Farbe raus ...
	QFile file(filename);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +filename, LEVEL::LL_ERROR);
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;
	ParseToLines( data, lines );

	//TODO: Dummyimplementierung. Holt nur die Farbe raus ...
	if( lines.isEmpty() == true )
	{
		jha::GetLog()->Log("Unable to parse empty file: " +filename, LEVEL::LL_ERROR);
		return false;
	}

	QStringList items = lines.at(0).split(" ",QString::SkipEmptyParts);
	if( items.size() < 7 )
	{
		jha::GetLog()->Log("Unable to parse color: " +filename, LEVEL::LL_ERROR);
		return false;
	}

	int r = items.at(3).toInt();
	int g = items.at(4).toInt();
	int b = items.at(5).toInt();

	nation->m_Color = QColor(r,g,b);
	return true;
}

//================================================================================
bool ParserHoI3::ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem*>& provinceList, const QString& provincePath ) const
{
	jha::GetLog()->Log("Parsing directory: " +provincePath, LEVEL::LL_INFO);
	QDir directory(provincePath);
	QFileInfoList infos = directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
	for( int i=0;i<infos.size();i++ )
	{
		if( infos.at(i).isFile() == true )
		{
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
			provinceItem.value()->m_FilePath = infos.at(i).fileName();
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

int ParserHoI3::CreateProvinceIDFromFilename( const QString& filename, const QString& separator ) const
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

bool ParserHoI3::ParseProvinceDetailInfo( const QString& filename, ProvinceItem* provinceItem ) const
{
	if( provinceItem == nullptr )
	{
		return false;
	}

	HoI3Script *script = ParseScript(filename);
	if( script == nullptr )
	{
		return false;
	}

	ProvinceItemPrototypeRepository prototypeFactory;

	bool atLeastOneItemFound = false;
	QList<HoI3Token>::ConstIterator iterType;
	for( iterType = script->m_TokenList.constBegin(); iterType != script->m_TokenList.constEnd(); iterType++ )
	{
		if( HoI3Scriptparser().IsDateToken((*iterType)) == true )
		{
			continue;
		}
		if( provinceItem->FindItem(iterType->m_Name).IsNull() == true )
		{
			continue;
		}
		if( provinceItem->UpdateItem( iterType->m_Name, iterType->m_Value ) == true )
		{
			atLeastOneItemFound = true;
		}
	}
	return atLeastOneItemFound;
}

void ParserHoI3::AttachProvincesToNations( const QHash<int,ProvinceItem*>& provinces, QHash<QString,Nation*>& nations )
{
	QHash<int,ProvinceItem*>::ConstIterator iter;
	for( iter = provinces.constBegin(); iter != provinces.constEnd(); iter++ )
	{
		AttachProvinceToNation((*iter),nations);
	}
}

void ParserHoI3::AttachProvinceToNation( ProvinceItem *province, QHash<QString,Nation*>& nations )
{
	if( province == nullptr )
	{
		return;
	}
	QString controller = province->FindItem( ProvinceItemPrototypeRepository::controller.GetName() ).GetData().toString();
	QHash<QString,Nation*>::iterator country = nations.find(controller);
	if( country == nations.end() )
	{
		return;
	}
	(*country)->AttachProvince(province);
	province->m_ColorNation = (*country)->GetColor();
}

bool ParserHoI3::CreateColorMap( QHash<int,ProvinceItem*>& result, const QPixmap* pixmap )
{
	if( pixmap == nullptr )
	{
		return false;
	}

	QImage mapImage = pixmap->toImage();
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
			int sameColorCount = PolygonHelper().CalcNeigboursColorCount(QPoint(j,i),mapImage);
			QRgb color = mapImage.pixel( j, i );
			QHash<int,ProvinceItem*>::iterator found = result.find( color );

			if( found == result.end() )
			{
				//TODO: Kein Eintrag in definition.csv für  Farbcode <x,y,z> aus provinces.bmp
				continue;
			}
			found.value()->m_ProvincePixels.append( QPoint(j,i) );
			if( sameColorCount != 8 )
			{
				found.value()->m_ContourPixels.append( QPoint(j,i) );
			}
		}
	}
	return result.isEmpty() == false;
}

void ParserHoI3::CreateGraphicsItems( QHash<int,ProvinceItem*>& result, ExtendedGraphicsScene *scene ) const
{
	QHash<int,ProvinceItem*>::Iterator iter;
	for( iter = result.begin(); iter != result.end(); iter++ )
	{
		(*iter)->m_GraphicsItem = CreateItemFromPixelClash((*iter)->m_ProvincePixels,(*iter)->m_ContourPixels, (*iter)->m_Color, scene );
		if( (*iter)->m_GraphicsItem == nullptr )
		{
			continue;
		}
//		(*iter)->m_GraphicsItem->SetAttachedProvinceItem( mapRGB.find(iter.value()->m_ID).value() );
		(*iter)->m_GraphicsItem->SetAttachedProvinceItem( (*iter) );
	}
}

#include "ExtendedGraphicsScene.h"
ProvinceGraphicsPixmapItem* ParserHoI3::CreateItemFromPixelClash( const QPolygon& pixelClash, const QPolygon& pixelClashContour, const QColor& color, ExtendedGraphicsScene *scene ) const
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

	QPolygon relativePixelClash;
	QImage contour(rect.width(),rect.height(),QImage::Format_RGB32);
	contour.fill(color);
	for( int i=0;i<pixelClashContour.size();i++ )
	{
		QPoint relativ(pixelClashContour.at(i));
		relativ.setX( relativ.x() - rect.left() );
		relativ.setY( relativ.y() - rect.top() );
		relativePixelClash.append(relativ);
		contour.setPixel(relativ,Qt::black);
	}

	QPixmap pixmapContour;
	pixmapContour.convertFromImage( contour );
	pixmapContour.setMask( QBitmap::fromImage(mask,Qt::MonoOnly) );

	ProvinceGraphicsPixmapItem *item = new ProvinceGraphicsPixmapItem( pixmap, pixmapContour, rect, scene );
	item->setOffset( rect.left(), rect.top() );
	item->SetContourPolygon(relativePixelClash);
	return item;
}

HoI3Script* ParserHoI3::ParseScript( const QString& filename ) const
{
	jha::GetLog()->Log( "Parsing file: " +filename, LEVEL::LL_MESSAGE, jha::LogCategoryByName(__FILE__) );
	QFile file(filename); 
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +filename, LEVEL::LL_ERROR);
		return nullptr;
	}

	QByteArray data = file.readAll();
	QStringList lines;

	ParseToLines( data, lines );

	HoI3Script *newScript = new HoI3Script(filename);

	HoI3Scriptparser parser;
	parser.Parse(lines,*newScript);
	return newScript;
}

bool ParserHoI3::ParseBuildingsTXT( QHash<QString,BuildingItem*>& buildingList, const QString& filename ) const
{
	HoI3Script *script = ParseScript(filename);
	if( script == nullptr )
	{
		return false;
	}

	BuildingItemPrototypeRepository prototypeFactory;

	QList<HoI3Token>::ConstIterator iterType;
	for( iterType = script->m_TokenList.constBegin(); iterType != script->m_TokenList.constEnd(); iterType++ )
	{
		BuildingItem *newBuilding = prototypeFactory.CreateBuildingItem(iterType->m_Name);
		QList<HoI3Token>::ConstIterator iterData;
		for( iterData = iterType->m_Tokens.constBegin(); iterData != iterType->m_Tokens.constEnd(); iterData++ )
		{
			newBuilding->UpdateItem(iterData->m_Name, iterData->m_Value );
		}

		buildingList.insert(newBuilding->GetName(), newBuilding);
	}
	return buildingList.size() > 0;
}


