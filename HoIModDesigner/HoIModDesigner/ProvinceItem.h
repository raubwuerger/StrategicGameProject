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
/** Get m_ID */
	int GetID() const;
/** Get m_Name */
	const QString& GetName() const { return m_Name; }
/** Set m_Name */
	void SetName( const QString& val) { m_Name = val; }
/** Get m_Color */
	const QColor& GetColor() const { return m_Color; }
/** Set m_Color */
	void SetColor( const QColor& val) { m_Color = val; }
/** Get m_ColorNation */
	const QColor& GetColorNation() const { return m_ColorNation; }
/** Set m_ColorNation */
	void SetColorNation( const QColor& val) { m_ColorNation = val; }
/** Get m_ProvincePixels */
	QPolygon& GetProvincePixels() { return m_ProvincePixels; }
/** Set m_ProvincePixels */
	void SetProvincePixels( const QPolygon& val) { m_ProvincePixels = val; }
/** Get m_ContourPixels */
	QPolygon& GetContourPixels() { return m_ContourPixels; }
/** Set m_ContourPixels */
	void SetContourPixels( const QPolygon& val) { m_ContourPixels = val; }
/** Get m_GraphicsItem */
	ProvinceGraphicsPixmapItem * GetGraphicsItem() { return m_GraphicsItem; }
/** Set m_GraphicsItem */
	void SetGraphicsItem( ProvinceGraphicsPixmapItem * val) { m_GraphicsItem = val; }
/** Get m_FilePath */
	const QString& GetFilePath() const { return m_FilePath; }
/** Set m_FilePath */
	void SetFilePath( const QString& val) { m_FilePath = val; }
/** Get m_ContentChanged */
	bool GetContentChanged() const { return m_ContentChanged; }
/** Set m_ContentChanged */
	void SetContentChanged( bool val) { m_ContentChanged = val; }
protected:
	ProvinceItem();
	friend class HoIModDesigner;
private:
	int			m_ID;
	QString		m_Name;
	QColor		m_Color;
	QColor		m_ColorNation;
	QPolygon	m_ProvincePixels;
	QPolygon	m_ContourPixels;
	ProvinceGraphicsPixmapItem	*m_GraphicsItem;
	QString		m_FilePath;
	bool		m_ContentChanged;
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
	static const ItemData add_core;
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
