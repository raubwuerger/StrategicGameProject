#ifndef MAPVIEWUNITITEM_H
#define MAPVIEWUNITITEM_H

class ConnectorMapUnitItem;

class MapUnitItem : public QGraphicsRectItem
{
public:
	/** */
	MapUnitItem( const QPointF& topLeft );
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** */
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	/** Set UnitItemImage */
	void SetUnitItemImage(const QImage* val);
	/** */
	const QImage* GetUnitItemImage() const;
	/** */
	void SetGameUnitId(int gameUnitId);
	/** */
	int GetGameUnitId();
	/** */
	void SetMapHexItemId(int mapHexItemId);
	/** */
	int GetMapHexItemId() const;
	/** */
	void SetEventConnector(ConnectorMapUnitItem* eventConnector);
private:
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();

private:
	const QImage*	UnitItemImage;
	int				GameUnitId;
	int				MapHexItemId;
	const QPointF&	TopLeft;
	QRectF			BoundingRect;
	ConnectorMapUnitItem*	EventConnector;
};

#endif
