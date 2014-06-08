#include "stdafx.h"
#include "ParserHoI3.h"
#include "std\LogInterface.h"
#include "ProvinceItem.h"
#include "Nation.h"
#include "PolygonHelper.h"
#include "ProvinceGraphicsPixmapItem.h"
#include "HoI3Context.h"

ParserHoI3::ParserHoI3()
{
}

bool ParserHoI3::Parse( HoI3Context& context, ExtendedGraphicsScene *scene )
{
	QPixmap *map = LoadProvincesBMP(context.GetPathProvinceBMP());
	if( map == nullptr )
	{
		return false;
	}

	QHash<int,ProvinceItem*>	provinceMapByRGB;
	ParseProvinzList(provinceMapByRGB,context.m_ProvinceMap,context.GetPathDefinitionCSV());

 	ParseCountryList(context.m_Countries,context.GetPathCountriesTXT(),context.GetPathCommonDir());
 
	QVector<QString> provinceDirPaths = context.GetPathProvincesDir();
	for( int i=0;i<provinceDirPaths.size();i++ )
	{
		ParseProvinceDetailInfoDirectory( context.m_ProvinceMap, provinceDirPaths.at(i) );
	}

 	AttachProvincesToNations( context.m_ProvinceMap, context.m_Countries );

	if( CreateColorMap(provinceMapByRGB,map) == false )
	{
		return false;
	}
 	CreateGraphicsItems(provinceMapByRGB,scene);
	return true;
}

QPixmap* ParserHoI3::LoadProvincesBMP( const QString& fileName )
{
	jha::GetLog()->Log("Loading file: " +fileName, jha::LogInterface::LL_INFO);
	QPixmap *newPixmap = new QPixmap;
	newPixmap->load(fileName);
	if( newPixmap->isNull() == true )
	{
		jha::GetLog()->Log("Unable to load file: " +fileName, jha::LogInterface::LL_ERROR);
		delete newPixmap;
		return nullptr;
	}
	newPixmap->operator=( newPixmap->transformed(QTransform().rotate(180,Qt::XAxis)) );
	return newPixmap;
}

bool ParserHoI3::ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const
{
	jha::GetLog()->Log("Loading file: " +provincePath, jha::LogInterface::LL_INFO);
	QFile file(provincePath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +provincePath, jha::LogInterface::LL_ERROR);
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

	jha::GetLog()->Log("Created province items: " +QString().setNum(mapRGB.size()), jha::LogInterface::LL_INFO);
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
		jha::GetLog()->Log("Unable to parse line: " +line, jha::LogInterface::LL_WARNING);
		return nullptr;
	}

	bool conversionValid;
	int provinceID = fields.at(0).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, jha::LogInterface::LL_WARNING);
		return nullptr;
	}

	int r = fields.at(1).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, jha::LogInterface::LL_WARNING);
		return nullptr;
	}

	int g = fields.at(2).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, jha::LogInterface::LL_WARNING);
		return nullptr;
	}

	int b = fields.at(3).toInt(&conversionValid);
	if( conversionValid == false )
	{
		jha::GetLog()->Log("Unable to parse line: " +line, jha::LogInterface::LL_WARNING);
		return nullptr;
	}

	QString name = fields.at(4);

	return new ProvinceItem(provinceID,name,QColor(r,g,b));
}

//================================================================================
bool ParserHoI3::ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath, const QVector<QString>& pathCountryDetails ) const
{
	jha::GetLog()->Log("Loading file: " +countryPath, jha::LogInterface::LL_INFO);
	QFile file(countryPath);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +countryPath, jha::LogInterface::LL_ERROR);
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

	jha::GetLog()->Log("Created countries: " +QString().setNum(countryList.size()), jha::LogInterface::LL_INFO);
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

	jha::GetLog()->Log("Loading file: " +filename, jha::LogInterface::LL_INFO);
	//TODO: Holt sich aktuell nur die Farbe raus ...
	QFile file(filename);
	if( file.open(QIODevice::ReadOnly | QIODevice::Text) == false )
	{
		jha::GetLog()->Log("Unable to load file: " +filename, jha::LogInterface::LL_ERROR);
		return false;
	}

	QByteArray data = file.readAll();
	QStringList lines;
	ParseToLines( data, lines );

	//TODO: Dummyimplementierung. Holt nur die Farbe raus ...
	if( lines.isEmpty() == true )
	{
		jha::GetLog()->Log("Unable to parse color: " +filename, jha::LogInterface::LL_ERROR);
		return false;
	}

	QStringList items = lines.at(0).split(" ",QString::SkipEmptyParts);
	if( items.size() < 7 )
	{
		jha::GetLog()->Log("Unable to parse color: " +filename, jha::LogInterface::LL_ERROR);
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
	jha::GetLog()->Log("Parsing directory: " +provincePath, jha::LogInterface::LL_INFO);
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


bool ParserHoI3::SortLinesByTimeline( const QStringList& data, QVector<QStringList>& timeLineParts ) const
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

bool ParserHoI3::CreateTokenMap( const QStringList& lines, QHash<QString,QString> &tokens, const QString& separator ) const
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

bool ParserHoI3::CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem* data ) const
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

bool ParserHoI3::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, int& valueToUpadte ) const
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

bool ParserHoI3::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, double& valueToUpadte ) const
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

bool ParserHoI3::UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, QString& valueToUpadte ) const
{
	QHash<QString,QString>::const_iterator token = tokens.find(tokenName);
	if( token == tokens.end() )
	{
		return false;
	}

	valueToUpadte = token.value();
	return true;
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

	QImage contour(rect.width(),rect.height(),QImage::Format_RGB32);
	image.fill(color);
	for( int i=0;i<pixelClashContour.size();i++ )
	{
		QPoint relativ(pixelClashContour.at(i));
		relativ.setX( relativ.x() - rect.left() );
		relativ.setY( relativ.y() - rect.top() );
		contour.setPixel(relativ,Qt::black);
	}

	QPixmap pixmapContour;
	pixmapContour.convertFromImage( contour );
	pixmapContour.setMask( QBitmap::fromImage(mask,Qt::MonoOnly) );

	ProvinceGraphicsPixmapItem *item = new ProvinceGraphicsPixmapItem( pixmap, pixmapContour, rect, scene );
	item->setOffset( rect.left(), rect.top() );
	return item;
}


