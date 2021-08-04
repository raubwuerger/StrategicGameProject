#ifndef MAPVIEWHEXITEM_H
#define MAPVIEWHEXITEM_H

#include "HexagonData.h"
class HexItemEventManager;

//================================================================================
/** Repräsentiert Kartenteil auf Bildschirm */
class MapViewHexItem : public QGraphicsPolygonItem
{
public:
	/** */
	MapViewHexItem( const HexagonData& data, const QPointF& topLeft );
	/** */
	~MapViewHexItem();
	/** */
	QRectF boundingRect() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** Set eventItem */
	void SetHexItemEventManager( HexItemEventManager * val) { EventItem = val; }
	/** */
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/** Get row */
	int GetRow() const { return Row; }
	/** Set row */
	void SetRowAndCol( int row, int col );
	/** Get col */
	int GetCol() const { return Col; }
	/** Set m_TerrainImage */
	void SetTerrainImage( const QImage * val);
	/** */
	void SetModelMapItemId( int modelMapItemId );
	/** */
	int GetModelMapItemId() const;
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
	HexItemEventManager	*EventItem;
	QString			StringRowCol;
	const QImage	*TerrainImage;
	int				ModelMapItemId;
};

#endif // MAPVIEWHEXITEM_H
