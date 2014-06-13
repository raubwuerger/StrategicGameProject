#ifndef PROVINCEITEM_H
#define PROVINCEITEM_H

class ProvinceDataItem
{
public:
	ProvinceDataItem( const QString& name, const QVariant& data )
		: m_Name(name),
		m_Data(data)
	{

	}
public:
	QString		m_Name;
	QVariant	m_Data;
};

class ProvinceTimeLineData
{
public:
	//TODO: Sollte wohl besser ein Datum sein?!
	ProvinceTimeLineData()
		: m_TimeLine("-"),
		m_Points(0),
		m_Metal(0.0),
		m_Energy(0.0),
		m_RareMaterials(0.0),
		m_Industry(0),
		m_AntiAir(0),
		m_Infrastructure(0),
		m_AirBases(0),
		m_Manpower(0.0),
		m_LeaderShip(0.0),
		m_NavalBase(0),
		m_CrudeOil(0.0),
		m_Landfort(0),
		m_Coastalfort(0),
		m_Nuclear(0),
		m_Radar(0),
		m_Rocket(0)
	{

	}
	ProvinceTimeLineData( const QString& timeLine )
		: m_TimeLine(timeLine),
		m_Points(0),
		m_Metal(0.0),
		m_Energy(0.0),
		m_RareMaterials(0.0),
		m_Industry(0),
		m_AntiAir(0),
		m_Infrastructure(0),
		m_AirBases(0),
		m_Manpower(0.0),
		m_LeaderShip(0.0),
		m_NavalBase(0),
		m_CrudeOil(0.0),
		m_Landfort(0),
		m_Coastalfort(0),
		m_Nuclear(0),
		m_Radar(0),
		m_Rocket(0)
	{

	}
	ProvinceTimeLineData( const ProvinceTimeLineData& rhs )
		: m_TimeLine(rhs.m_TimeLine),
		m_Points(rhs.m_Points),
		m_Metal(rhs.m_Metal),
		m_Energy(rhs.m_Energy),
		m_RareMaterials(rhs.m_RareMaterials),
		m_Industry(rhs.m_Industry),
		m_AntiAir(rhs.m_AntiAir),
		m_Infrastructure(rhs.m_Infrastructure),
		m_AirBases(rhs.m_AirBases),
		m_Manpower(rhs.m_Manpower),
		m_LeaderShip(rhs.m_LeaderShip),
		m_NavalBase(rhs.m_NavalBase),
		m_CrudeOil(rhs.m_CrudeOil),
		m_Owner(rhs.m_Owner),
		m_Controller(rhs.m_Controller),
		m_Landfort(rhs.m_Landfort),
		m_Coastalfort(rhs.m_Coastalfort),
		m_Nuclear(rhs.m_Nuclear),
		m_Radar(rhs.m_Radar),
		m_Rocket(rhs.m_Rocket)
	{

	}

	ProvinceTimeLineData& operator=( const ProvinceTimeLineData& rhs )
	{
		m_TimeLine = rhs.m_TimeLine;
		m_Points = rhs.m_Points;
		m_Metal = rhs.m_Metal;
		m_Energy = rhs.m_Energy;
		m_RareMaterials = rhs.m_RareMaterials;
		m_Industry = rhs.m_Industry;
		m_AntiAir = rhs.m_AntiAir;
		m_Infrastructure = rhs.m_Infrastructure;
		m_AirBases = rhs.m_AirBases;
		m_Manpower = rhs.m_Manpower;
		m_LeaderShip = rhs.m_LeaderShip;
		m_NavalBase = rhs.m_NavalBase;
		m_CrudeOil = rhs.m_CrudeOil;
		m_Owner = rhs.m_Owner;
		m_Controller = rhs.m_Controller;
		m_Landfort = rhs.m_Landfort;
		m_Coastalfort = rhs.m_Coastalfort;
		m_Nuclear = rhs.m_Nuclear;
		m_Radar = rhs.m_Radar;
		m_Rocket = rhs.m_Rocket;
		return *this;
	}
public:
	QString	m_TimeLine;
	QMap<QString,ProvinceDataItem> m_ProvinceDataItem;


	QString m_Owner;
	QString	m_Controller;
	QVector<QString>	m_CoreFrom;
	int		m_Points;
	double	m_Metal;
	double	m_Energy;
	double	m_CrudeOil;
	double	m_RareMaterials;
	int		m_Industry;
	int		m_AntiAir;
	int		m_Infrastructure;
	int		m_NavalBase;
	int		m_AirBases;
	double	m_Manpower;
	double	m_LeaderShip;
	int		m_Landfort;
	int		m_Coastalfort;
	int		m_Nuclear;
	int		m_Radar;
	int		m_Rocket;
};

class ProvinceGraphicsPixmapItem;
#include <QObject>
class ProvinceItem : public QObject
{
	Q_OBJECT
public:
/** */
	ProvinceItem( const ProvinceItem& rhs );
/** */
	ProvinceItem( int id, const QString& name, const QColor& color );
/** */
	ProvinceItem& operator=( const ProvinceItem& rhs );
protected:
	ProvinceItem();
	friend class HoIModDesigner;
signals:
 	void SignalProvinceEntered( ProvinceItem* );
 	void SignalProvinceLeft( ProvinceItem* );
public:
	int			m_ID;
	QString		m_Name;
	QColor		m_Color;
	QColor		m_ColorNation;
	QPolygon	m_ProvincePixels;
	QPolygon	m_ContourPixels;
	ProvinceGraphicsPixmapItem	*m_GraphicsItem;
	QVector<ProvinceTimeLineData> m_TimeLineData;
};

#endif // PROVINCEITEM_H
