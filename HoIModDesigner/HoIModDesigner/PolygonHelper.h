// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 hj Exp $
// (c) J�rgen Hannuschka
//--------------------------------

#ifndef POLYGONHELPER_H
#define POLYGONHELPER_H

#include <QPolygon>
#include <QRgb>

QT_BEGIN_NAMESPACE
class QImage;
class QPoint;
QT_END_NAMESPACE

/** Helperklasse welche verschiedene Algorithmen zur Verf�gung stellt.*/
class PolygonHelper
{
public:
/** Versucht die �bergebenen Punkt-Liste so zu sortiered das alle Punkte in einer Reihe sind. Problem des n�chsten Nachbarns 
  * Sp�ter in Helperklasse auslagern! */
    QPolygon SortToProvinceContour( QPolygon& firstChancePoints, QPolygon& secondChancePoints ) const;
/** �berpr�ft ob benachbarte Punkte selbe Farbe haben.
  * Wenn ja, werden sie in die Liste eingef�gt */
    void CreateNeigboursByColor( QRgb color, const QPoint &point, QPolygon &toVerify, const QPolygon &sameColor, const QImage &image );
/** Ermittelt zu einer Punktemenge ein MinimalesRechteck in dem alle Punkte Platz haben */
    void FindSurroundingRect( const QPolygon &points, int &width, int &height, int &left, int &top ) const;
/** Liefert true wenn Punkt nur von Punkten mit gleicher Farbe umgeben ist */
	bool IsMiddlePoint( const QPoint &point, const QImage &image, int allowedExternalColors = 0 ) const;
private:
/** �berpr�ft ob ein Punkt mit Farbe �bereinstimmt */
    bool ColorsIdentical( const QPoint &point, const QRgb &color, const QImage &image ) const;
/** Liefert zu Punkt p den n�chsten Nachbarn */
    int FindIndexOfNearestNeigbour( const QPolygon &neigbours, const QPoint &p ) const;
};


#endif //POLYGONHELPER_H
