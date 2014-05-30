// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 hj Exp $
// (c) Jürgen Hannuschka
//--------------------------------

#include "stdafx.h"
#include "PolygonHelper.h"
//#include "..\HJStandardLib\HJMessageManager.h"
#include <QImage>
#include <QPoint>

//=================================================================================================
void PolygonHelper::FindSurroundingRect( const QPolygon &points, int &width, int &height, int &left, int &top ) const
{
    width   = 0;
    height  = 0;
    left    = 0;
    top     = 0;
    if( points.isEmpty() == true )
    {
        return;
    }
    int minX = points.at(0).x();
    int maxX = points.at(0).x();
    int minY = points.at(0).y();
    int maxY = points.at(0).y();
    for( int i=0;i<points.size();i++ )
    {
        int x = points.at(i).x();
        int y = points.at(i).y();
        if( x < minX )
        {
            minX = x;
        }
        else
        {
            if( x > maxX )
            {
                maxX = x;
            }
        }
        if( y < minY )
        {
            minY = y;
        }
        else
        {
            if( y > maxY )
            {
                maxY = y;
            }
        }
    }
    width   = (maxX - minX) + 1;
    height  = (maxY - minY) + 1;
    left    = minX;
    top     = minY;
}

//================================================================================
bool PolygonHelper::ColorsIdentical( const QPoint &point, const QRgb &color, const QImage &image ) const
{
	if( image.isNull() == true )
	{
		return true; //TODO: Ist eigentlich falsch
	}
    
	if( image.valid( point ) == false )
    {
        return false;
    }

    QRgb colorToVerify = image.pixel( point );
    return colorToVerify == color;
}

//================================================================================
void PolygonHelper::CreateNeigboursByColor( QRgb color, const QPoint &point, QPolygon &toVerify, const QPolygon &sameColor, const QImage &image )
{
    QPoint top( point.x(), point.y() + 1 );
    if( ColorsIdentical( top, color, image ) == true && sameColor.indexOf(top) == -1 && toVerify.indexOf(top) == -1 )
    {
        toVerify.append( top );
    }

    QPoint bottom( point.x(), point.y() - 1 );
    if( ColorsIdentical( bottom, color, image ) == true && sameColor.indexOf(bottom) == -1 && toVerify.indexOf(bottom) == -1 )
    {
        toVerify.append( bottom );
    }

    QPoint left( point.x() - 1, point.y() );
    if( ColorsIdentical( left, color, image ) == true && sameColor.indexOf(left) == -1 && toVerify.indexOf(left) == -1 )
    {
        toVerify.append( left );
    }

    QPoint right( point.x() + 1, point.y() );
    if( ColorsIdentical( right, color, image ) == true && sameColor.indexOf(right) == -1 && toVerify.indexOf(right) == -1 )
    {
        toVerify.append( right );
    }
}

//================================================================================
QPolygon PolygonHelper::SortToProvinceContour( QPolygon& firstChancePoints, QPolygon& secondChancePoints ) const 
{
    QPolygon sorted;
    const QPoint &first = firstChancePoints.at(0);
    firstChancePoints.remove(0);
    sorted.append(first);
    while(!firstChancePoints.isEmpty())
    {
        int found = FindIndexOfNearestNeigbour(firstChancePoints,sorted.last());
        if( found == -1 )
        {
			int foundInSecondChance = FindIndexOfNearestNeigbour( secondChancePoints, sorted.last());
			if( foundInSecondChance == -1 )
			{
				//HJMessageManager::Instance()->DoPostMessage(HJMessage::mtDEBUG,"Kein nächster Punkt gefunden");
				return sorted;
			}
			const QPoint &p = secondChancePoints.at(foundInSecondChance);
			sorted.append(p);
			secondChancePoints.remove(foundInSecondChance);
        }
		else
		{
			const QPoint &p = firstChancePoints.at(found);
			sorted.append(p);
			firstChancePoints.remove(found);
		}
    }
    return sorted;
}

//================================================================================
int PolygonHelper::FindIndexOfNearestNeigbour( const QPolygon &neigbours, const QPoint &p ) const
{
    QPolygon surroundOrdered; //Zuerst die Horizontal/Vertikalen, dann die diagonalen
    surroundOrdered.append(QPoint(p.x()+1,p.y()));
    surroundOrdered.append(QPoint(p.x(),p.y()-1));
    surroundOrdered.append(QPoint(p.x()-1,p.y()));
    surroundOrdered.append(QPoint(p.x(),p.y()+1));
	surroundOrdered.append(QPoint(p.x()+1,p.y()+1));
	surroundOrdered.append(QPoint(p.x()+1,p.y()-1));
	surroundOrdered.append(QPoint(p.x()-1,p.y()-1));
	surroundOrdered.append(QPoint(p.x()-1,p.y()+1));
    for(int i=0;i<surroundOrdered.size();i++)
    {
        int found = neigbours.indexOf(surroundOrdered.at(i));
        if( found != -1 )
        {
            return found;
        }
    }

    return -1;
}

//================================================================================
bool PolygonHelper::IsMiddlePoint( const QPoint &point, const QImage &image, int allowedExternalColors ) const
{
	if( image.isNull() == true )
	{
		return false;
	}
	QRgb colorOfPoint = image.pixel( point );
	int externalsColorCount = 0;
	if( ColorsIdentical( QPoint(point.x()-1,point.y()-1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x(),point.y()-1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()-1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x()-1,point.y()), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x()-1,point.y()+1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x(),point.y()+1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()+1), colorOfPoint, image ) == false )
	{
		externalsColorCount++;
	}
	if( externalsColorCount > allowedExternalColors )
	{
		return false;
	}
	return true;
}

// End of file PolygonHelper.cpp
