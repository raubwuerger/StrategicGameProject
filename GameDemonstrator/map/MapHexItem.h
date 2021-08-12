#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include "HexagonData.h"
class ConnectorMapHexItem;

//================================================================================
/** Repräsentiert Kartenteil auf Bildschirm */
class MapHexItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapHexItem( const HexagonData& data, const QPointF& topLeft );
	/** */
	~MapHexItem();
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
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
	int GetGameMapItemId() const;
	/** */
	const QPointF& GetTopLeftPoint() const;
	/** */
	const QPointF& GetCenterPoint() const;
private:
	/** */
	void CreateHexPolygon( const HexagonData &data );
	/** */
	void ShowSelected();
	/** */
	void ShowOriginal();
private:
	int Row;
	int Col;
	HexagonData		HexData;
	QPointF			CenterPoint;
	QPointF			TopLeftPoint;
	ConnectorMapHexItem	*EventItem;
	QString			StringRowCol;
	const QImage	*TerrainImage;
	int				GameMapItemId;
};

#endif // MAPVIEWHEXITEM_H
