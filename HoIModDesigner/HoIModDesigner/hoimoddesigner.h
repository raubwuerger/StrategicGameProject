#ifndef HOIMODDESIGNER_H
#define HOIMODDESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_hoimoddesigner.h"

class ProvinceGraphicsPixmapItem;
class ProvinceItem;
class ExtendedGraphicsScene;
class ExtendedGraphicsView;
class Nation;
class ProvinceTimeLineData;

class ExtendedGraphicsPolygonItem : public QGraphicsPolygonItem
{
public:
	ExtendedGraphicsPolygonItem( const QPolygonF & polygon, QGraphicsItem * parent = 0 )
		: QGraphicsPolygonItem(polygon,parent)
	{
		setAcceptHoverEvents(true);
	}

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event) 
	{
		QBrush brush;
		brush.setStyle(Qt::SolidPattern); 
		QColor color("brown");
		brush.setColor(color);
		setBrush(brush);
		update(boundingRect());
		QGraphicsPolygonItem::hoverEnterEvent(event);
		event->ignore();
	}
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) 
	{
		QBrush brush;
		brush.setStyle(Qt::NoBrush); 
		// 		QColor color("brown");
		// 		brush.setColor(color);
		setBrush(brush);
		update(boundingRect());
		QGraphicsPolygonItem::hoverLeaveEvent(event);
		event->ignore();
	}


	void mousePressEvent(QGraphicsSceneMouseEvent * event)
	{
			QBrush brush;
			brush.setStyle(Qt::SolidPattern); 
			QColor color("brown");
			brush.setColor(color);
			setBrush(brush);
			update(boundingRect());
			QGraphicsPolygonItem::mousePressEvent(event);
			event->ignore();
	}
};

class HoIModDesigner : public QMainWindow
{
	Q_OBJECT

public:
	HoIModDesigner(QWidget *parent = 0);
	~HoIModDesigner();
private slots:
	void LoadMap();
/** */
	void DisplayOriginalMap();
/** */
	void DisplayContourMap();
/** */
	void DisplayContourSortedMap();
/** */
	void DisplayItemMap();
/** */
	void ShowOriginalMap();
/** */
	void ShowNationColorMap();
private:
/** */
	bool CreateColorMap( QHash<int,ProvinceItem>& result );

	int Smooth( QImage &mapImage, int level = 3 );

	bool SmoothColor( QImage &mapImage, const QPoint& org, const QPoint& updateFrom );

	/** */
	bool CreateContourImage( QHash<int,ProvinceItem>& result, QPixmap& pixmap );
/** */
	bool CreateContourSortedMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap );
/** */
	bool LoadOriginalMap( const QString& fileName );
/** Erzeugt aus der Kontour-Karte Polygonobjekte */
	bool CreateContourPolygons( QHash<int,ProvinceItem>& result ) const;
/** */
	bool ParseProvinzList( QHash<int,ProvinceItem>& mapRGB, QHash<int,ProvinceItem>& mapID, const QString& provincePath ) const;
/** */
	bool ParseCountryList( QHash<QString,Nation>& countryList, const QString& countryPath ) const;
/** */
	int ParseToLines( const QByteArray& data, QStringList &lines ) const;
/** */
	bool CreateProvinzeItemFromString( const QString& line, ProvinceItem& item ) const;
/** */
	bool CreateNationFromString( const QString& line, Nation& nation ) const;
/** */
	ProvinceGraphicsPixmapItem* CreateItemFromPixelClash( const QPolygon& pixelClash, const QColor& color, ExtendedGraphicsScene *scene ) const;
/** */
	void CreateGraphicsItems( QHash<int,ProvinceItem>& result ) const;
/** */
	void CreateDockWidgets();
/** */
	void FillNationList( const QHash<QString,Nation>& nations, QTableWidget* widget );
/** */
	void FillProvinceList( QHash<int,ProvinceItem>& provinces, QTableWidget* widget );
/** */
	bool ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem>& provinzList, const QString& provincePath ) const;
/** */
	int CreateProvinceIDFromFilename( const QString& filename ) const;
/** */
	bool ParseProvinceDetailInfo( const QString& filename, ProvinceItem& provinceItem ) const;
/** */
	bool CreateTokenMap( const QStringList& line, QHash<QString,QString> &tokens, const QString& separator = "=" ) const;
/** */
	bool SortLinesByTimeline( const QStringList& data, QVector<QStringList>& timeLineParts ) const;
/** */
	bool CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem& data ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, int& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, double& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, QString& valueToUpadte ) const;

private slots:
	void UpdateProvinceDetail(const ProvinceItem* item);
private:
	Ui::HoIModDesignerClass ui;
	QMenu		*m_FileMenu;
	QMenu		*m_HilfeMenu;
	QMenu		*m_DockWidgetsMenu;
	QToolBar	*m_FileToolBar;
	QToolBar	*m_MapFilterToolBar;
	QAction		*m_ExitAction;
	QAction		*m_LoadMapAction;
	QAction		*m_AboutAction;
	QAction		*m_ShowOriginalMap;
	QAction		*m_ShowNationColorMap;
	QToolBox	*m_ToolBox;
	ExtendedGraphicsView *m_View;
	QPixmap		m_OriginalMap;
	QPixmap		m_ContourMap;
	QPixmap		m_ContourSortedMap;
	QHash<int,ProvinceItem>	m_ProvinceMapByRGB;
	QHash<int,ProvinceItem>	m_ProvinceMapByID;
	QHash<QString,Nation>	m_Nations;
	QTableWidget *m_DockWidgetProvinceDetails;
	QTableWidget *m_DockWidgetNationList;
	QTableWidget *m_DockWidgetProvinceList;
};

#endif // HOIMODDESIGNER_H
