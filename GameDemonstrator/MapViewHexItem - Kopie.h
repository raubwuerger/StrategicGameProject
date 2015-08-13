#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include <QGraphicsPolygonItem>

class MapViewHexItem : public QGraphicsPolygonItem
{
	Q_OBJECT
public:
	MapViewHexItem(QGraphicsPolygonItem *parent = 0, const int size = 1, const double h = 1.73);
	~MapViewHexItem();
	void paint();
	QRectF boundingRect() const;
private:
	int m_Size;
	double m_Height;
};

#endif // MAPVIEWHEXITEM_H
