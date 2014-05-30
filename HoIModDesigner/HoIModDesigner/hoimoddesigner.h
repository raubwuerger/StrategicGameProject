#ifndef HOIMODDESIGNER_H
#define HOIMODDESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_hoimoddesigner.h"

class ProvinceItem
{
public:
	ProvinceItem( int id, const QString& name, const QColor& color )
		: m_ID(id),
		m_Name(name),
		m_Color(color)
	{

	}
protected:
	friend class HoIModDesigner;
	ProvinceItem()
		: m_ID(-1),
		m_Name("prototype"),
		m_Color(Qt::white)
	{

	}
public:
	int			m_ID;
	QString		m_Name;
	QColor		m_Color;
	QPolygon	m_Contour;
	QPolygon	m_ContourSecondChance;
	QVector<QPolygonF> m_SortedContours;
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
	void DisplayContourSecondChanceMap();
/** */
	void DisplayContourSortedMap();
/** */
	void DisplayItemMap();
private:
/** */
	bool CreateColorMap( QHash<int,ProvinceItem>& result );
/** */
	bool CreateContourMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap );
/** */
	bool CreateContourSortedMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap );
/** */
	bool CreateContourSecondChanceMap( QHash<int,ProvinceItem>& result, QPixmap& pixmap );
/** */
	bool LoadOriginalMap( const QString& fileName );
/** Erzeugt aus der Kontour-Karte Polygonobjekte */
	bool CreateContourPolygons( QHash<int,ProvinceItem>& result ) const;
/** */
	bool ReadProvinzList( QHash<int,ProvinceItem>& provinzList, const QString& provincePath ) const;
/** */
	int ParseToLines( const QByteArray& data, QStringList &lines ) const;
/** */
	bool CreateProvinzeItemFromString( const QString& line, ProvinceItem& item ) const;
private:
	Ui::HoIModDesignerClass ui;
	QMenu		*m_FileMenu;
	QMenu		*m_HilfeMenu;
	QToolBar	*m_FileToolBar;
	QAction		*m_ExitAction;
	QAction		*m_LoadMapAction;
	QAction		*m_AboutAction;
	QToolBox	*m_ToolBox;
	QGraphicsScene *m_Scene;
	QGraphicsView *m_View;
	QPixmap		m_OriginalMap;
	QPixmap		m_ContourMap;
	QPixmap		m_ContourSecondChanceMap;
	QPixmap		m_ContourSortedMap;
	QHash<int,ProvinceItem>	m_ProvinceMapByRGB;
};

#endif // HOIMODDESIGNER_H
