#ifndef HOIMODDESIGNER_H
#define HOIMODDESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_hoimoddesigner.h"

class ProvinceGraphicsPixmapItem;
class ProvinceItem;
class ExtendedGraphicsScene;
class ExtendedGraphicsView;
class Nation;

class TableWidgetItemNation : public QTableWidgetItem
{
public:
	TableWidgetItemNation()
		: m_Nation(nullptr)
	{

	}
	TableWidgetItemNation( const QString& text, Nation *nation )
		: QTableWidgetItem(text),
		m_Nation(nation)
	{

	}

public:
	Nation *m_Nation;
};

class LoggingTableWidgetRow
{
public:
	QVector<QTableWidgetItem*> m_Items;
};

class LoggingTableWidget : public QTableWidget
{
	Q_OBJECT
public:
/** */
	LoggingTableWidget(int rows, int columns, QWidget * parent );
/** */
	~LoggingTableWidget();
public slots:
/** */
	void AppendRow( LoggingTableWidgetRow *newRow );
/** */
	void ScrollToBottom();
private:
	QTimer	*m_TimerScrollToBottom;
	bool	m_RowsAdded;
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
	void DisplayItemMap();
/** */
	void ShowOriginalMap();
/** */
	void ShowNationColorMap();
/** */
	void ShowIndustryColorMap();
/** */
	void ShowMetalColorMap();
/** */
	void ShowCrudeOilColorMap();
private:
/** */
	bool CreateColorMap( QHash<int,ProvinceItem*>& result );
/** */
	bool LoadOriginalMap( const QString& fileName );
/** */
	bool ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const;
/** */
	void FillCountryList( const QHash<QString,Nation*>& nations, QTableWidget* widget );
/** */
	bool ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath ) const;
/** */
	Nation* CreateCountryFromString( const QString& line ) const;
/** */
	bool ParseCountryDetailInfo( const QString& filename, Nation* provinceItem ) const;
/** */
	int ParseToLines( const QByteArray& data, QStringList &lines ) const;
/** */
	ProvinceItem* CreateProvinzeItemFromString( const QString& line ) const;
/** */
	ProvinceGraphicsPixmapItem* CreateItemFromPixelClash( const QPolygon& pixelClash, const QColor& color, ExtendedGraphicsScene *scene ) const;
/** */
	void CreateGraphicsItems( QHash<int,ProvinceItem*>& result ) const;
/** */
	void CreateDockWidgets();
/** */
	void FillProvinceList( QHash<int,ProvinceItem*>& provinces, QTableWidget* widget );
/** */
	bool ParseProvinceDetailInfoDirectory( QHash<int,ProvinceItem*>& provinzList, const QString& provincePath ) const;
/** */
	int CreateProvinceIDFromFilename( const QString& filename, const QString& separator = "-" ) const;
/** */
	bool ParseProvinceDetailInfo( const QString& filename, ProvinceItem* provinceItem ) const;
/** */
	bool CreateTokenMap( const QStringList& line, QHash<QString,QString> &tokens, const QString& separator = "=" ) const;
/** */
	bool SortLinesByTimeline( const QStringList& data, QVector<QStringList>& timeLineParts ) const;
/** */
	bool CreateProvinceTimeLineData( const QHash<QString,QString>& tokens, ProvinceItem* data ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, int& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, double& valueToUpadte ) const;
/** */
	bool UpdateTokenValue( const QHash<QString,QString>& tokens, const QString& tokenName, QString& valueToUpadte ) const;
/** */
	void AttachProvinceToNation( ProvinceItem *province, QHash<QString,Nation*>& nations );
/** */
	void AttachProvincesToNations( const QHash<int,ProvinceItem*>& provinces, QHash<QString,Nation*>& nations );
/** */
	void ClearProvinceItems();
/** */
	void ClearNations();
signals:
	void SignalAppendRow(LoggingTableWidgetRow*);
private slots:
	void UpdateProvinceDetail(const ProvinceItem* item);
	void UpdateCountryDetail(QTableWidgetItem* item);
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
	QAction		*m_ShowIndustryProvinces;
	QAction		*m_ShowMetalProvinces;
	QAction		*m_ShowOilProvinces;
	QToolBox	*m_ToolBox;
	ExtendedGraphicsView *m_View;
	QPixmap		m_OriginalMap;
	QPixmap		m_ContourMap;
	QPixmap		m_ContourSortedMap;
	QHash<int,ProvinceItem*>	m_ProvinceMapByRGB;
	QHash<int,ProvinceItem*>	m_ProvinceMapByID;
	QHash<QString,Nation*>	m_Nations;
	QTableWidget *m_DockWidgetProvinceDetails;
	QTableWidget *m_DockWidgetNationList;
	QTableWidget *m_DockWidgetNationDetails;
	QTableWidget *m_DockWidgetProvinceList;
	LoggingTableWidget *m_DockWidgetLogging;
};

#endif // HOIMODDESIGNER_H
