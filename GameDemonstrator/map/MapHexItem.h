#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

class ConnectorMapHexItem;
class HexagonItem;

#include "MapHexItemSetting.h"

//================================================================================
/** Repr�sentiert Kartenteil auf Bildschirm */
class MapHexItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapHexItem(const QPointF& topLeft, const HexagonItem& hexagon);
	/** */
	~MapHexItem();
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	/** Set eventItem */
	void SetEventConnector( ConnectorMapHexItem * eventConnector );
	/** */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/** Get row */
	int GetRow() const;
	/** Set row */
	void SetRowAndCol( int row, int col );
	/** Get col */
	int GetCol() const;
	/** Set m_TerrainImage */
	bool SetTerrainImage( const QImage * val);
	/** */
	void SetGameMapItemId( int gameMapItemId );
	/** */
	int GetId() const;
	/** */
	const QPointF& GetTopLeftPoint() const;
	/** */
	const QPointF& GetCenterPoint() const;
	/** */
	void SetMapHexItemSetting(MapHexItemSetting mapHexItemSetting);
private:
	/** */
	void CreateHexPolygon();
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
	/** */
	void CreateMapHexItemInfoString();
	/** */
	void ShowTextOnItem(QPainter *painter);
private:
	int						Row;
	int						Col;
	QPolygonF				Hexagon;
	QPointF					CenterPoint;
	QPointF					TopLeftPoint;
	ConnectorMapHexItem*	EventItem;
	QRectF					BoundingRect;
	QString					MapHexItemInfoString;
	mutable const QImage*	TerrainImage;
	int						GameMapItemId;
	MapHexItemSetting		MapHexItemSettingObject;
};

#endif // MAPVIEWHEXITEM_H
