#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include <QGraphicsPolygonItem>

class MapViewHexItem : public QGraphicsPolygonItem
{
//	Q_OBJECT
public:
	MapViewHexItem(QGraphicsPolygonItem *parent = 0, int size = 10, double h = 17.32);
	~MapViewHexItem();
	void paint();
	QRectF boundingRect() const;
private:
	int m_Size;
	double m_Height;
	QRectF	m_BoundingRect;
};

#endif // MAPVIEWHEXITEM_H
