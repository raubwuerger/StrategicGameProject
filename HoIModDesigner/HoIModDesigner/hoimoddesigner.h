#ifndef HOIMODDESIGNER_H
#define HOIMODDESIGNER_H

#include <QtWidgets/QMainWindow>
#include "ui_hoimoddesigner.h"

class ProvinceItem;
class ExtendedGraphicsScene;
class ExtendedGraphicsView;
class Nation;
class TimeLineDataCriteria;

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

class HoIModDesigner : public QMainWindow
{
	Q_OBJECT

public:
	HoIModDesigner(QWidget *parent = 0);
	~HoIModDesigner();
private slots:
/** */
	void LoadMap();
/** */
	void OpenConfigurationDialog();
/** */
	void DisplayContourMap();
/** */
	void DisplayItemMap( const QHash<int,ProvinceItem*>* items );
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
	void CreateDockWidgets();
/** */
	void CreateColumn( QTreeWidgetItem* parent, const HoI3Token& token ) const;
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
	QAction		*m_FileConfigurationAction;
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
	QTableWidget *m_DockWidgetProvinceDetails;
	QTableWidget *m_DockWidgetNationList;
	QTableWidget *m_DockWidgetNationDetails;
	QTableWidget *m_DockWidgetProvinceList;
	LoggingTableWidget *m_DockWidgetLogging;

	PropertyEditor::PropertyEditor *m_PropertyEdit;
	QTreeWidget	*m_TreeView;

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

