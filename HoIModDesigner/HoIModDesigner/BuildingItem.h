#ifndef BUILDINGITEM_H
#define BUILDINGITEM_H

class ItemData
{
public:
	ItemData()
		: m_IsNull(true)
	{

	}
	ItemData( const QString& name, const QVariant& data )
		: m_Name(name),
		m_Data(data),
		m_IsNull(false)
	{
	}
public:
	QString		m_Name;
	QVariant	m_Data;
	bool		m_IsNull;
};

class BuildingItem
{
public:
/** Constructor */
	BuildingItem( const QString& name );
/** Liefert Name */
	const QString& GetName() const;
/** Liefert alle ItemDatas */
	const QMap<QString,ItemData>& GetProvinceDataItem() const;
/** Fügt neues Item hinzu */
	bool AppendItemData( const QString& key, const ItemData& value );
/** */
	ItemData FindItem( const QString& key ) const;
private:
	QString					m_Name;
	QMap<QString,ItemData>	m_ProvinceDataItem;
};

class BuildingItemPrototypeRepository
{
public:
/** Default constructor */
	BuildingItemPrototypeRepository();
/** Erzeugt ein Item aus name und data */	
	ItemData CreateItemData( const QString& name, const QString& data ) const;
public:
	static const ItemData on_completion;
	static const ItemData completion_size;
	static const ItemData air_capacity;
	static const ItemData capital;
	static const ItemData onmap;
	static const ItemData cost;
	static const ItemData time;
	static const ItemData max_level;
	static const ItemData visibility;
	static const ItemData naval_capacity;
	static const ItemData port;
	static const ItemData coastal_fort_level;
	static const ItemData orientation;
	static const ItemData fort_level;
	static const ItemData local_anti_air;
	static const ItemData damage_factor;
	static const ItemData radar_level;
	static const ItemData local_underground;
	static const ItemData show_for_province;
	static const ItemData repair;
	static const ItemData ic;
	static const ItemData infrastructure;
private:
	QMap<QString,ItemData> m_PrototypeMap;
};
#endif // BUILDINGITEM_H
