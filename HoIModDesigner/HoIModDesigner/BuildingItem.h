#ifndef BUILDINGITEM_H
#define BUILDINGITEM_H

#include "ItemTypeBase.h"

class BuildingItem : public ItemTypeBase
{
public:
/** Constructor */
	BuildingItem( const QString& name );
/** Get m_Name */
	const QString& GetName() const;
private:
	QString	m_Name;
};

class BuildingItemPrototypeRepository : public ItemPrototypeRepository
{
public:
/** Initialisiert Repository */
	virtual void Init();
/** Erzeugt neues Item und Initialisiert es */
	BuildingItem* CreateBuildingItem( const QString& name ) const;
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
};
#endif // BUILDINGITEM_H
