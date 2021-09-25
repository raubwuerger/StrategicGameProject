#ifndef MAPCITYITEM_H
#define MAPCITYITEM_H

class ConnectorMapCityItem;

//================================================================================
/** Repräsentiert Kartenteil auf Bildschirm */
class MapCityItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapCityItem(const QPointF& topLeft, const QPolygonF& hexagon);
	/** */
	~MapCityItem();
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	/** Set eventItem */
	void SetEventConnector( ConnectorMapCityItem * eventConnector );
	/** */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/** */
	void SetOwnerColor(const QColor ownerColor);
	/** Set m_TerrainImage */
	bool SetTerrainImage( const QImage * val);
	/** */
	void SetGameMapItemId( int gameMapItemId );
	/** */
	int GetGameMapItemId() const;
	/** */
	const QPointF& GetTopLeftPoint() const;
	/** */
	const QPointF& GetCenterPoint() const;
	/** */
	int GetId() const { return MapCityItemId;  }
protected:
	/** */
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
	/** */
	void CreateHexPolygon();
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
	/** */
	void CreateMapCityItemInfoString();
private:
	friend class MapCityItemFactory;
	QPolygonF				Hexagon;
	QPointF					CenterPoint;
	QPointF					TopLeftPoint;
	QRectF					BoundingRect;
	ConnectorMapCityItem*	EventItem;
	mutable const QImage*	TerrainImage;
	int						GameMapItemId;
	int						MapCityItemId;
	QColor					Color;
};

#endif // MAPCITYITEM_H
