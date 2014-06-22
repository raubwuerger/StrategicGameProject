#ifndef PROVINCEGRAPHICSPIXMAPITEM_H
#define PROVINCEGRAPHICSPIXMAPITEM_H

class ProvinceItem;
class ExtendedGraphicsScene;

class ProvinceGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
	/** */
	ProvinceGraphicsPixmapItem( const QPixmap & pixmap, const QPixmap & contour, const QRect& location, ExtendedGraphicsScene *parent );
	/** */
	ProvinceGraphicsPixmapItem( const ProvinceGraphicsPixmapItem& rhs );
	/** */
	~ProvinceGraphicsPixmapItem();
	/** */
	const QRect& GetLocation() const;
	/** */
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	/** */
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	/** */
	void ShowSelected();
	/** Zeigt Provinz in der Farbe aus Originaldatei an */
	void ShowOriginal();
	const ProvinceItem * GetAttachedProvinceItem() const;
	void SetAttachedProvinceItem(ProvinceItem * val);
/** */
	void UpdateColor( const QColor& color );
	const QPolygon& GetContourPolygon() const { return m_ContourPolygon; }
	void SetContourPolygon( const QPolygon& obj ) { m_ContourPolygon = obj; }
private:
	QPixmap ApplyContour( const QPixmap& pixmap ) const;
private:
	QRect	m_Location;
	QPixmap	m_OrgPixmap;
	QPixmap	m_Contour;
	QPixmap	m_LastPixmap;
	QPolygon m_ContourPolygon;
	ProvinceItem *m_AttachedProvinceItem;
	ExtendedGraphicsScene *m_Parent;
	QColor	m_ColorBeforeEnter;
	bool	m_ShowContour;
};

#endif // PROVINCEGRAPHICSPIXMAPITEM_H
