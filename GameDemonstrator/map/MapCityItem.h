#ifndef MAPCITYITEM_H
#define MAPCITYITEM_H

#include "MapHexItemHexagonData.h"
class ConnectorMapCityItem;

//================================================================================
/** Repräsentiert Kartenteil auf Bildschirm */
class MapCityItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapCityItem( const MapHexItemHexagonData& data, const QPointF& topLeft );
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
private:
	/** */
	void CreateHexPolygon(const MapHexItemHexagonData &data);
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
	/** */
	void CreateMapCityItemInfoString();
private:
	friend class MapCityItemFactory;
	MapHexItemHexagonData	HexData;
	QPointF					CenterPoint;
	QPointF					TopLeftPoint;
	ConnectorMapCityItem*	EventItem;
	mutable const QImage*	TerrainImage;
	int						GameMapItemId;
	int						MapCityItemId;
	QColor					Color;
};

#endif // MAPCITYITEM_H
