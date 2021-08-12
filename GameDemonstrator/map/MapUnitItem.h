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
	const QImage* GetUnitItemImage() const;
	/** */
	void SetGameUnitId(int gameUnitId);
	/** */
	int GetGameUnitId() { return GameUnitId;  }
	/** */
	void SetMapHexItemId(int mapHexItemId) { MapHexItemId = mapHexItemId;  }
	/** */
	int GetMapHexItemId() const { return MapHexItemId; }
private:
	const QImage*	UnitItemImage;
	int				GameUnitId;
	int				MapHexItemId;
	const QPointF&	TopLeft;
};

#endif
