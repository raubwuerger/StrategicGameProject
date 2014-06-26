#ifndef HOIMODDESIGNER_H
#define HOIMODDESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_hoimoddesigner.h"

class ProvinceItem;
class ExtendedGraphicsScene;
class ExtendedGraphicsView;
class Nation;
class TimeLineDataCriteria;
class BuildingItem;

class TableWidgetItemNation;
class TableWidgetItemComparator
{
public:
	virtual bool Compare( const QTableWidgetItem &lhs, const QTableWidgetItem &rhs ) const = 0;
};

class TableWidgetItemComparatorDouble : public TableWidgetItemComparator
{
public:
	virtual bool Compare( const QTableWidgetItem &lhs, const QTableWidgetItem &rhs ) const;
};

class TableWidgetItemComparatorString: public TableWidgetItemComparator
{
public:
	virtual bool Compare( const QTableWidgetItem &lhs, const QTableWidgetItem &rhs ) const;
};

class TableWidgetItemNation : public QTableWidgetItem
{
public:
	TableWidgetItemNation( const TableWidgetItemNation& rhs )
		: QTableWidgetItem(""),
		m_Comparator( rhs.m_Comparator ),
		m_Nation( rhs.m_Nation )
	{

	}

	~TableWidgetItemNation()
	{
		delete m_Comparator;
	}

	TableWidgetItemNation( TableWidgetItemComparator* comparator = new TableWidgetItemComparatorDouble() )
		: QTableWidgetItem(""),
		m_Nation(nullptr),
		m_Comparator(comparator)
	{

	}
	TableWidgetItemNation( const QString& text, Nation *nation, TableWidgetItemComparator* comparator = new TableWidgetItemComparatorDouble() )
		: QTableWidgetItem(text),
		m_Nation(nation),
		m_Comparator(comparator)
	{

	}
	bool operator< ( const QTableWidgetItem &other ) const
	{
		return m_Comparator->Compare(*this,other);
	}
public:
	Nation *m_Nation;
private:
	TableWidgetItemComparator *m_Comparator;
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

namespace PropertyEditor
{
	class PropertyEditor;
}

class HoI3Token;
class ParserHoI3;

class HoIModDesigner : public QMainWindow
{
	Q_OBJECT

public:
	HoIModDesigner(QWidget *parent = 0);
	~HoIModDesigner();
public slots:
	void UpdateProvinceColor( ProvinceItem *item );
	void SlotProvinceMouseReleased(ProvinceItem *item );
private slots:
/** */
	void LoadMap();
/** */
	void SaveChanges();
/** */
	void OpenConfigurationDialog();
/** */
	void DisplayContourMap();
/** */
	void DisplayItemMap( const QHash<int,ProvinceItem*>& items );
/** */
	void ShowOriginalMap();
/** */
	void ShowNationColorMap();
/** */
	void ShowMapFiltered( const TimeLineDataCriteria* criteria );
private:
/** */
	void FillCountryList( const QHash<QString,Nation*>& nations, QTableWidget* widget );
/** */
	void FillProvinceList( QHash<int,ProvinceItem*>& provinces, QTableWidget* widget );
/** */
	void FillBuildinsList( QHash<QString,BuildingItem*>& buildings, QTableWidget* widget );
/** */
	void CreateDockWidgets();
/** */
	void CreateColumn( QTreeWidgetItem* parent, const HoI3Token& token ) const;
/** */
	QWidget *CreatePaintButton(const QString &text, const QString& iconPath, QButtonGroup *group, int buttonID );
signals:
	void SignalAppendRow(LoggingTableWidgetRow*);
private slots:
	void UpdateProvinceDetail(ProvinceItem* item);
	void UpdateCountryDetail(QTableWidgetItem* item);
	void ParsingFinished();
	void SetFactoryForExtendedScene( int id );
private:
	Ui::HoIModDesignerClass ui;
	QMenu		*m_FileMenu;
	QMenu		*m_HilfeMenu;
	QMenu		*m_DockWidgetsMenu;
	QToolBar	*m_FileToolBar;
	QToolBar	*m_MapFilterToolBar;
	QAction		*m_FileConfigurationAction;
	QAction		*m_ExitAction;
	QAction		*m_LoadMapAction;
	QAction		*m_SaveChangesAction;
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
	QTableWidget *m_DockWidgetProvinceDetails;
	QTableWidget *m_DockWidgetNationList;
	QTableWidget *m_DockWidgetNationDetails;
	QTableWidget *m_DockWidgetProvinceList;
	QTableWidget *m_DockWidgetBuildingTypes;
	LoggingTableWidget *m_DockWidgetLogging;

	PropertyEditor::PropertyEditor *m_PropertyEdit;
	QTreeWidget	*m_TreeView;
	QVector<QWidget*> m_PainterWidgets;

	ParserHoI3	*m_Parser;
};

class PropTestClass : public QObject
{
	Q_OBJECT
public:
	PropTestClass(QObject* parent = 0)
		: QObject(parent)
	{

	}
	virtual ~PropTestClass() {}
};
#endif // HOIMODDESIGNER_H

class FilterAction : public QAction
{
	Q_OBJECT
public:
	FilterAction( const QIcon & icon, const QString & text, const TimeLineDataCriteria* filterCriteria, HoIModDesigner * parent )
		: QAction(icon,text,parent),
		m_FilterCriteria(filterCriteria)
	{
		connect(this, SIGNAL(triggered()), this, SLOT(RedirectTriggered()));
		connect(this, SIGNAL(ApplyFilter( const TimeLineDataCriteria* )), parent, SLOT(ShowMapFiltered( const TimeLineDataCriteria* )) );
	}
	~FilterAction()
	{
		delete m_FilterCriteria;
	}
	private slots:
		void RedirectTriggered() 
		{
			emit ApplyFilter(m_FilterCriteria);
		}
signals:
		void FilterTriggered();
		void ApplyFilter( const TimeLineDataCriteria* );
private:
	const TimeLineDataCriteria* m_FilterCriteria;
};

