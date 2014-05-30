// ID: $Id: config.properties,v 1.6 2006/10/05 08:51:42 hj Exp $
// (c) Jürgen Hannuschka
//--------------------------------

#ifndef POLYGONHELPER_H
#define POLYGONHELPER_H

#include <QPolygon>
#include <QRgb>

QT_BEGIN_NAMESPACE
class QImage;
class QPoint;
QT_END_NAMESPACE

/** Helperklasse welche verschiedene Algorithmen zur Verfügung stellt.*/
class PolygonHelper
{
public:
/** Versucht die übergebenen Punkt-Liste so zu sortiered das alle Punkte in einer Reihe sind. Problem des nächsten Nachbarns 
  * Später in Helperklasse auslagern! */
    QPolygon SortToProvinceContour( QPolygon& firstChancePoints, QPolygon& secondChancePoints ) const;
/** Überprüft ob benachbarte Punkte selbe Farbe haben.
  * Wenn ja, werden sie in die Liste eingefügt */
    void CreateNeigboursByColor( QRgb color, const QPoint &point, QPolygon &toVerify, const QPolygon &sameColor, const QImage &image );
/** Ermittelt zu einer Punktemenge ein MinimalesRechteck in dem alle Punkte Platz haben */
    void FindSurroundingRect( const QPolygon &points, int &width, int &height, int &left, int &top ) const;
/** Liefert true wenn Punkt nur von Punkten mit gleicher Farbe umgeben ist */
	bool IsMiddlePoint( const QPoint &point, const QImage &image, int allowedExternalColors = 0 ) const;
private:
/** Überprüft ob ein Punkt mit Farbe übereinstimmt */
    bool ColorsIdentical( const QPoint &point, const QRgb &color, const QImage &image ) const;
/** Liefert zu Punkt p den nächsten Nachbarn */
    int FindIndexOfNearestNeigbour( const QPolygon &neigbours, const QPoint &p ) const;
};


#endif //POLYGONHELPER_H
