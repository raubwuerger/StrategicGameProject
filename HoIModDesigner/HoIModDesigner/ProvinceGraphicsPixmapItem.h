#ifndef PROVINCEGRAPHICSPIXMAPITEM_H
#define PROVINCEGRAPHICSPIXMAPITEM_H

class ProvinceItem;
class ExtendedGraphicsScene;

class ProvinceGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
	/** */
	ProvinceGraphicsPixmapItem( const QPixmap & pixmap, const QRect& location, ExtendedGraphicsScene *parent );
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
	void SetAttachedProvinceItem(const ProvinceItem * val);
/** */
	void UpdateColor( const QColor& color );
private:
	QRect	m_Location;
	QPixmap	*m_OrgPixmap;
	const ProvinceItem *m_AttachedProvinceItem;
	ExtendedGraphicsScene *m_Parent;
};

#endif // PROVINCEGRAPHICSPIXMAPITEM_H
