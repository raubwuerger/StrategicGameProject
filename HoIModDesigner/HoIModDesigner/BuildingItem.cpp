#include "stdafx.h"
#include "BuildingItem.h"
#include "std/LogInterface.h"

ItemTypeBase::ItemTypeBase( const QString& name ) 
	: m_Name(name)
{

}

const QString& ItemTypeBase::GetName() const
{
	return m_Name;
}

const QMap<QString,ItemData>& ItemTypeBase::GetItemMap() const
{
	return m_Items;
}

bool ItemTypeBase::AppendItemData( const QString& key, const ItemData& value )
{
	QMap<QString,ItemData>::Iterator iter = m_Items.find(key);
	if( iter != m_Items.end() )
	{
		return false;
	}
	m_Items.insert(key,value);
	return true;
}

ItemData ItemTypeBase::FindItem( const QString& key ) const
{
	QMap<QString,ItemData>::ConstIterator iter = m_Items.find(key);
	if( iter != m_Items.end() )
	{
		return ItemData();
	}
	return (*iter);
}

bool ItemTypeBase::UpdateItem( const QString& key, const QVariant& data )
{
	QMap<QString,ItemData>::Iterator iter = m_Items.find(key);
	if( iter != m_Items.end() )
	{
		return false;
	}
	if( iter->m_Data.type() != data.type() )
	{
		return false;
	}
	iter->m_Data = data;
	return true;
}

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

BuildingItemPrototypeRepository::BuildingItemPrototypeRepository()
{
	m_PrototypeMap.insert( on_completion.m_Name, on_completion );
	m_PrototypeMap.insert( on_completion.m_Name, on_completion );
	m_PrototypeMap.insert( completion_size.m_Name, completion_size );
	m_PrototypeMap.insert( air_capacity.m_Name, air_capacity );
	m_PrototypeMap.insert( capital.m_Name, capital );
	m_PrototypeMap.insert( onmap.m_Name, onmap );
	m_PrototypeMap.insert( cost.m_Name, cost );
	m_PrototypeMap.insert( time.m_Name, time );
	m_PrototypeMap.insert( max_level.m_Name, max_level );
	m_PrototypeMap.insert( visibility.m_Name, visibility );
	m_PrototypeMap.insert( naval_capacity.m_Name, naval_capacity );
	m_PrototypeMap.insert( port.m_Name, port );
	m_PrototypeMap.insert( coastal_fort_level.m_Name, coastal_fort_level );
	m_PrototypeMap.insert( orientation.m_Name, orientation );
	m_PrototypeMap.insert( fort_level.m_Name, fort_level );
	m_PrototypeMap.insert( local_anti_air.m_Name, local_anti_air );
	m_PrototypeMap.insert( damage_factor.m_Name, damage_factor );
	m_PrototypeMap.insert( radar_level.m_Name, radar_level );
	m_PrototypeMap.insert( local_underground.m_Name, local_underground );
	m_PrototypeMap.insert( show_for_province.m_Name, show_for_province );
	m_PrototypeMap.insert( repair.m_Name, repair );
	m_PrototypeMap.insert( ic.m_Name, ic );
	m_PrototypeMap.insert( infrastructure.m_Name, infrastructure );
}

ItemData BuildingItemPrototypeRepository::CreateItemData( const QString& name, const QString& data ) const
{
	QMap<QString,ItemData>::ConstIterator foundPrototype = m_PrototypeMap.constFind(name);
	if( foundPrototype == m_PrototypeMap.constEnd() )
	{
		jha::GetLog()->Log( "Item not defined: " +name, LEVEL::LL_WARNING );
		return ItemData(name,"???");
	}

	QVariant dataVariant(data);
	if( dataVariant.convert(foundPrototype->m_Data.type() ) == false )
	{
		jha::GetLog()->Log( "Data type invalid: " +data, LEVEL::LL_WARNING );
		return ItemData(name,"???");
	}

	return ItemData( name, dataVariant );
}

BuildingItem::BuildingItem( const QString& name )
	: ItemTypeBase(name)
{

}
