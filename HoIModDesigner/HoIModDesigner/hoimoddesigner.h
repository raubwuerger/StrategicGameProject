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
	bool operator< ( const QTableWidgetItem &other ) const
	{
		return text().toDouble() < other.text().toDouble();
	}
public:
	Nation *m_Nation;
};

class LoggingTableWidgetRow
{
public:
	QVector<QTableWidgetItem*> m_Items;
};

class HoI3Context
{
public:
	HoI3Context()
	: m_BasePath("E:\\Spiele\\HoI3"),
		m_PathTFH("tfh"),
		m_ProvincesBMP("map\\provinces.bmp"),
		m_DefinitionCSV("map\\definition.csv"),
		m_CountriesTXT("common\\countries.txt"),
		m_ProvincesDir("history\\provinces"),
		m_ModPath("mod\\RandomHoi"),
		m_CommonDir("common\\"),
		TRAIL("\\")
	{

	}
	QString GetPathProvinceBMP() const
	{
		return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ProvincesBMP;
	}
	QString GetPathDefinitionCSV() const
	{
		return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_UsedMod +m_DefinitionCSV;
	}
	QString GetPathCountriesTXT() const
	{
		//return m_BasePath +TRAIL +m_CountriesTXT;
		return m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_CountriesTXT;
	}
	QVector<QString> GetPathProvincesDir() const
	{
		QVector<QString> paths;
// 		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ProvincesDir);
// 		paths.push_back(m_BasePath +TRAIL +m_ProvincesDir);
		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_ProvincesDir);
		return paths;
	}
	QVector<QString> GetPathCommonDir() const
	{
		QVector<QString> paths;
		// 		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_CommonDir);
		// 		paths.push_back(m_BasePath +TRAIL +m_ProvincesDir);
		paths.push_back(m_BasePath +TRAIL +m_PathTFH +TRAIL +m_ModPath +TRAIL +m_CommonDir);
		return paths;
	}
public:
	const QString TRAIL;
	QString		m_BasePath;
	QString		m_PathTFH;
	QString		m_ModPath;
	QString		m_DefinitionCSV;
	QString		m_CountriesTXT;
	QString		m_ProvincesDir;
	QString		m_ProvincesBMP;
	QString		m_UsedMod;
	QString		m_CommonDir;
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

#include "ProvinceItem.h"
class TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const = 0;
};

class TimeLineDataCriteriaEnergy : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Energy <= 0;
	}
};

class TimeLineDataCriteriaMetal : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Metal <= 0;
	}
};

class TimeLineDataCriteriaCrudeOil : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_CrudeOil <= 0;
	}
};

class TimeLineDataCriteriaRareMaterial : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_RareMaterials <= 0;
	}
};

class TimeLineDataCriteriaIndustry : public TimeLineDataCriteria
{
public:
	virtual bool CriteriaFullfilled( const ProvinceTimeLineData& timeLineData ) const
	{
		return timeLineData.m_Industry <= 0;
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
	void DisplayItemMap();
/** */
	void ShowOriginalMap();
/** */
	void ShowNationColorMap();
/** */
	void FilterMapEnergy();
/** */
	void FilterMapMetal();
/** */
	void FilterMapCrudeOil();
/** */
	void FilterMapRareMaterial();
/** */
	void FilterMapIndustry();
private:
/** */
	void ShowMapFiltered( const TimeLineDataCriteria& criteria );
/** */
	bool CreateColorMap( QHash<int,ProvinceItem*>& result );
/** */
	bool LoadOriginalMap( const QString& fileName );
/** */
	bool ParseProvinzList( QHash<int,ProvinceItem*>& mapRGB, QHash<int,ProvinceItem*>& mapID, const QString& provincePath ) const;
/** */
	void FillCountryList( const QHash<QString,Nation*>& nations, QTableWidget* widget );
/** */
	bool ParseCountryList( QHash<QString,Nation*>& countryList, const QString& countryPath, const QVector<QString>& pathCountryDetails ) const;
/** */
	Nation* CreateCountryFromString( const QString& line ) const;
/** */
	bool ParseCountryDetailInfo( const QString& filename, Nation* provinceItem ) const;
/** */
	int ParseToLines( const QByteArray& data, QStringList &lines ) const;
/** */
	ProvinceItem* CreateProvinzeItemFromString( const QString& line ) const;
/** */
	ProvinceGraphicsPixmapItem* CreateItemFromPixelClash( const QPolygon& pixelClash, const QPolygon& pixelClashContour, const QColor& color, ExtendedGraphicsScene *scene ) const;
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

	QAction		*m_ShowMetalProvinces;
	QAction		*m_ShowOilProvinces;
	QAction		*m_ShowEnergyProvinces;
	QAction		*m_ShowRareProvinces;

	QAction		*m_ShowIndustryProvinces;
	QAction		*m_ShowAAProvinces;
	QAction		*m_ShowAirbaseProvinces;
	QAction		*m_ShowCoastalfortProvinces;
	QAction		*m_ShowInfraProvinces;
	QAction		*m_ShowLandfortProvinces;
	QAction		*m_ShowNavalbaseProvinces;
	QAction		*m_ShowNuclearProvinces;
	QAction		*m_ShowRadarProvinces;
	QAction		*m_ShowRocketProvinces;

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
