#ifndef PROVINCEITEM_H
#define PROVINCEITEM_H

#include "ItemTypeBase.h"
class ProvinceGraphicsPixmapItem;
class ProvinceItem : public ItemTypeBase
{
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
public:
	int			m_ID;
	QString		m_Name;
	QColor		m_Color;
	QColor		m_ColorNation;
	QPolygon	m_ProvincePixels;
	QPolygon	m_ContourPixels;
	ProvinceGraphicsPixmapItem	*m_GraphicsItem;
	QString		m_FilePath;
};

class ProvinceItemPrototypeRepository : public ItemPrototypeRepository
{
public:
/** */
	virtual void Init();
/** */
	ProvinceItem* CreateProvinceItem( int id, const QString& name, const QColor& color ) const;
public:
 	static const ItemData owner;
	static const ItemData core;
 	static const ItemData controller;
 	static const ItemData infra;
	static const ItemData points;
	static const ItemData metal;
	static const ItemData energy;
	static const ItemData rare_materials;
	static const ItemData crude_oil;

	static const ItemData industry;
	static const ItemData anti_air;
	static const ItemData naval_base;
	static const ItemData air_base;
	static const ItemData manpower;
	static const ItemData leadership;
	static const ItemData land_fort;
	static const ItemData coastal_fort;
	static const ItemData nuclear_reactor;
	static const ItemData radar_station;
	static const ItemData rocket_test;
// 	QVector<QString>	m_CoreFrom;
};

#endif // PROVINCEITEM_H
