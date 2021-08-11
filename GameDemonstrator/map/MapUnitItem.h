#ifndef MAPVIEWUNITITEM_H
#define MAPVIEWUNITITEM_H

class MapUnitItem : public QGraphicsRectItem
{
public:
	/** */
	MapUnitItem( const QPointF& topLeft );
	/** */
	QRectF boundingRect() const;
	/** */
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	/** Set UnitItemImage */
	void SetUnitItemImage(const QImage* val);
	/** */
	void SetGameUnitId(int gameUnitId);
private:
	const QImage*	UnitItemImage;
	int				GameUnitId;
	const QPointF&	TopLeft;
};

#endif
