#include "stdafx.h"
#include "BuildingItem.h"
#include "std/LogInterface.h"

BuildingItem::BuildingItem( const QString& name )
	: ItemTypeBase("BuildingItem"),
	m_Name(name)
{

}

const QString& BuildingItem::GetName() const
{
	return m_Name;
}

//================================================================================
const ItemData BuildingItemPrototypeRepository::on_completion = ItemData("on_completion",QVariant(QString()));
const ItemData BuildingItemPrototypeRepository::completion_size = ItemData("completion_size",QVariant(QVariant::Double));
const ItemData BuildingItemPrototypeRepository::air_capacity = ItemData("air_capacity",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::capital = ItemData("capital",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::onmap = ItemData("onmap",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::cost = ItemData("cost",QVariant(QVariant::Double));
const ItemData BuildingItemPrototypeRepository::time = ItemData("time",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::max_level = ItemData("max_level",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::visibility = ItemData("visibility",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::naval_capacity = ItemData("naval_capacity",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::port = ItemData("port",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::coastal_fort_level = ItemData("coastal_fort_level",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::orientation = ItemData("orientation",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::fort_level = ItemData("fort_level",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::local_anti_air = ItemData("local_anti_air",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::damage_factor = ItemData("damage_factor",QVariant(QVariant::Double));
const ItemData BuildingItemPrototypeRepository::radar_level = ItemData("radar_level",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::local_underground = ItemData("local_underground",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::show_for_province = ItemData("show_for_province",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::repair = ItemData("repair",QVariant(QVariant::Bool));
const ItemData BuildingItemPrototypeRepository::ic = ItemData("ic",QVariant(QVariant::Int));
const ItemData BuildingItemPrototypeRepository::infrastructure = ItemData("infrastructure",QVariant(QVariant::Double));

void BuildingItemPrototypeRepository::Init()
{
	m_PrototypeMap.clear();
	m_PrototypeMap.insert( on_completion.GetName(), on_completion );
	m_PrototypeMap.insert( on_completion.GetName(), on_completion );
	m_PrototypeMap.insert( completion_size.GetName(), completion_size );
	m_PrototypeMap.insert( air_capacity.GetName(), air_capacity );
	m_PrototypeMap.insert( capital.GetName(), capital );
	m_PrototypeMap.insert( onmap.GetName(), onmap );
	m_PrototypeMap.insert( cost.GetName(), cost );
	m_PrototypeMap.insert( time.GetName(), time );
	m_PrototypeMap.insert( max_level.GetName(), max_level );
	m_PrototypeMap.insert( visibility.GetName(), visibility );
	m_PrototypeMap.insert( naval_capacity.GetName(), naval_capacity );
	m_PrototypeMap.insert( port.GetName(), port );
	m_PrototypeMap.insert( coastal_fort_level.GetName(), coastal_fort_level );
	m_PrototypeMap.insert( orientation.GetName(), orientation );
	m_PrototypeMap.insert( fort_level.GetName(), fort_level );
	m_PrototypeMap.insert( local_anti_air.GetName(), local_anti_air );
	m_PrototypeMap.insert( damage_factor.GetName(), damage_factor );
	m_PrototypeMap.insert( radar_level.GetName(), radar_level );
	m_PrototypeMap.insert( local_underground.GetName(), local_underground );
	m_PrototypeMap.insert( show_for_province.GetName(), show_for_province );
	m_PrototypeMap.insert( repair.GetName(), repair );
	m_PrototypeMap.insert( ic.GetName(), ic );
	m_PrototypeMap.insert( infrastructure.GetName(), infrastructure );
}

BuildingItem* BuildingItemPrototypeRepository::CreateBuildingItem( const QString& name ) const
{
	BuildingItem *newItem = new BuildingItem(name);
	InitWithAllPrototypes( *newItem );
	return newItem;
}

