// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 hj Exp $
// (c) Jürgen Hannuschka
//--------------------------------

#include "stdafx.h"
#include "PolygonHelper.h"
//#include "..\HJStandardLib\HJMessageManager.h"
#include <QImage>
#include <QPoint>

//=================================================================================================
QRect PolygonHelper::FindSurroundingRect( const QPolygon &points ) const
{
	QRect result(0,0,0,0);
    if( points.isEmpty() == true )
    {
        return result;
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
	result.setX(minX);
	result.setY(minY);
	result.setWidth((maxX - minX) + 1);
	result.setHeight((maxY - minY) + 1);
	return result;
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
        std::vector<int> found = FindIndexOfNearestNeigbour(firstChancePoints,sorted.last());
        if( found.empty() == true )
        {
			found = FindIndexOfNearestNeigbour( secondChancePoints, sorted.last());
			if( found.empty() == true )
			{
				//HJMessageManager::Instance()->DoPostMessage(HJMessage::mtDEBUG,"Kein nächster Punkt gefunden");
				return sorted;
			}
			const QPoint &p = secondChancePoints.at(found.at(0));
			sorted.append(p);
			secondChancePoints.remove(found.at(0));
        }
		else
		{
			const QPoint &p = firstChancePoints.at(found.at(0));
			sorted.append(p);
			firstChancePoints.remove(found.at(0));
		}
    }
    return sorted;
}

//================================================================================
QPolygon PolygonHelper::SortToProvinceContour( QPolygon& firstChancePoints ) const 
{
	QPolygon sorted;
	const QPoint &first = firstChancePoints.at(0);
	sorted.append(first);
	firstChancePoints.remove(0);
	while(!firstChancePoints.isEmpty())
	{
		std::vector<int> found = FindIndexOfNearestNeigbour(firstChancePoints,sorted.last());
		if( found.empty() == true )
		{
			//HJMessageManager::Instance()->DoPostMessage(HJMessage::mtDEBUG,"Kein nächster Punkt gefunden");
			return sorted;
		}
		const QPoint &p = firstChancePoints.at(found.at(0));
		sorted.append(p);
		firstChancePoints.remove(found.at(0));
	}
	return sorted;
}

//================================================================================
QPolygon PolygonHelper::SortToProvinceContourFlip( QPolygon& firstChancePoints ) const 
{
	QPolygon sorted;
	const QPoint &first = firstChancePoints.at(0);
	sorted.append(first);
	firstChancePoints.remove(0);
	std::vector<int> lastFound;
	while(!firstChancePoints.isEmpty())
	{
		lastFound = FindIndexOfNearestNeigbour(firstChancePoints,sorted.last());
		if( lastFound.empty() == true )
		{
			//HJMessageManager::Instance()->DoPostMessage(HJMessage::mtDEBUG,"Kein nächster Punkt gefunden");
			if( sorted.size() > 1 )
			{
				const QPoint last = sorted.at(sorted.size()-1);
				const QPoint beforeLast = sorted.at(sorted.size()-2);
				sorted.setPoint(sorted.size()-1, beforeLast);
				sorted.setPoint(sorted.size()-2, last);
			}

			lastFound = FindIndexOfNearestNeigbour(firstChancePoints,sorted.last());
			if( lastFound.empty() == true )
			{
				return sorted;
			}
		}
		const QPoint &p = firstChancePoints.at(lastFound.at(0));
		sorted.append(p);
		firstChancePoints.remove(lastFound.at(0));
	}
	return sorted;
}

//================================================================================
std::vector<int> PolygonHelper::FindIndexOfNearestNeigbour( const QPolygon &neigbours, const QPoint &p ) const
{
	std::vector<int> result;
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
            result.push_back(found);
        }
    }

    return result;
}

//================================================================================
int PolygonHelper::CalcNeigboursColorCount( const QPoint &point, const QImage &image ) const
{
	if( image.isNull() == true )
	{
		return -1;
	}
	QRgb colorOfPoint = image.pixel( point );
	int externalsColorCount = 0;
	if( ColorsIdentical( QPoint(point.x()-1,point.y()-1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x(),point.y()-1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()-1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x()-1,point.y()), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x()-1,point.y()+1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x(),point.y()+1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	if( ColorsIdentical( QPoint(point.x()+1,point.y()+1), colorOfPoint, image ) == true )
	{
		externalsColorCount++;
	}

	return externalsColorCount;
}

// End of file PolygonHelper.cpp
