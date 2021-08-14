#ifndef MAPVIEWUNITITEM_H
#define MAPVIEWUNITITEM_H

class ConnectorMapUnitItem;
class KeyEventController;

class MapUnitItem : public QGraphicsPolygonItem
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
	virtual void keyPressEvent(QKeyEvent * event);
	/** */
	virtual void keyReleaseEvent(QKeyEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	/** */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
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
	/** */
	void SetKeyEventController(KeyEventController* eventController);
private:
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
	/** */
	void CreatRect();
private:
	const QImage*	UnitItemImage;
	int				GameUnitId;
	int				MapHexItemId;
	const QPointF&	TopLeft;
	QSize			ImageRect;
	QRectF			BoundingRect;
	ConnectorMapUnitItem*	EventConnector;
	KeyEventController*		EventController;
};

#endif
