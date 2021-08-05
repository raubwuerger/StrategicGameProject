#ifndef MAPVIEWUNITITEM_H
#define MAPVIEWUNITITEM_H

class MapViewUnitItem : public QGraphicsRectItem
{
public:
	/** */
	MapViewUnitItem();
	/** */
	QRectF boundingRect() const;
	/** */
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	/** Set m_TerrainImage */
	void SetUnitItemImage(const QImage* val);
private:
	const QImage* UnitItemImage;
};

#endif
