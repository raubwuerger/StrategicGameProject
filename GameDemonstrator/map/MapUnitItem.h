#ifndef MAPVIEWUNITITEM_H
#define MAPVIEWUNITITEM_H

class MapUnitItem : public QGraphicsRectItem
{
public:
	/** */
	MapUnitItem();
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
