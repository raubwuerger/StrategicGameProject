#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include "MapHexItemHexagonData.h"
class ConnectorMapHexItem;

//================================================================================
/** Repräsentiert Kartenteil auf Bildschirm */
class MapHexItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapHexItem( const MapHexItemHexagonData& data, const QPointF& topLeft );
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
	void SetShowId(bool show) { ShowId = show;  }
	/** */
	void SetShowRowAndCol(bool show) { ShowRowAndCol = show; }
	/** */
	void SetShowCoordinates(bool show) { ShowCoordinates = show; }
	/** */
	void SetShowTextBorder(bool show) { ShowTextBorder = show; }
	/** */
	void SetShowText(bool show) { ShowText = show; }
	/** */
	void SetShowHexBorder(bool show) { DrawHexBorder = show; }
private:
	/** */
	void CreateHexPolygon( const MapHexItemHexagonData &data );
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
	/** */
	void CreateMapHexItemInfoString();
	/** */
	void ShowTextOnItem(QPainter *painter);
private:
	int Row;
	int Col;
	MapHexItemHexagonData	HexData;
	QPointF					CenterPoint;
	QPointF					TopLeftPoint;
	ConnectorMapHexItem*	EventItem;
	QString					MapHexItemInfoString;
	mutable const QImage*	TerrainImage;
	int						GameMapItemId;
	bool					ShowId;
	bool					ShowRowAndCol;
	bool					ShowCoordinates;
	bool					ShowTextBorder;
	bool					ShowText;
	bool					DrawHexBorder;
};

#endif // MAPVIEWHEXITEM_H
