#include "stdafx.h"
#include "ProvinceItem.h"

//================================================================================
ProvinceItem::ProvinceItem()
	: ItemTypeBase("ProvinceItem"),
	m_ID(-1),
	m_Name("prototype"),
	m_Color(Qt::white),
	m_ColorNation(Qt::white),
	m_GraphicsItem(nullptr),
	m_ContentChanged(false)
{
}


ProvinceItem::ProvinceItem( const ProvinceItem& rhs )
	: ItemTypeBase(rhs),
	m_ID(rhs.m_ID),
	m_Name(rhs.m_Name),
	m_Color(rhs.m_Color),
	m_GraphicsItem( rhs.m_GraphicsItem),
	m_ProvincePixels(rhs.m_ProvincePixels),
	m_ContourPixels(rhs.m_ContourPixels),
	m_ColorNation(rhs.m_ColorNation),
	m_ContentChanged(rhs.m_ContentChanged)
{

}

ProvinceItem::ProvinceItem( int id, const QString& name, const QColor& color )
	: ItemTypeBase("ProvinceItem"),
	m_ID(id),
	m_Name(name),
	m_Color(color),
	m_GraphicsItem(nullptr),
	m_ColorNation(Qt::white),
	m_ContentChanged(false)
{

}

ProvinceItem& ProvinceItem::operator=( const ProvinceItem& rhs )
{
	m_ID = rhs.m_ID;
	m_Name = rhs.m_Name;
	m_Color = rhs.m_Color;
	m_GraphicsItem = rhs.m_GraphicsItem;
	m_ProvincePixels = rhs.m_ProvincePixels;
	m_ColorNation = rhs.m_ColorNation;
	m_ContourPixels = rhs.m_ContourPixels;
	m_ContentChanged = rhs.m_ContentChanged;
	ItemTypeBase::operator=(rhs);
	return *this;
}

int ProvinceItem::GetID() const
{
	return m_ID;
}

//================================================================================
const ItemData ProvinceItemPrototypeRepository::owner = ItemData("owner",QVariant(QString()));
const ItemData ProvinceItemPrototypeRepository::controller = ItemData("controller",QVariant(QString()));
const ItemData ProvinceItemPrototypeRepository::infra = ItemData("infra",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::points = ItemData("points",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::metal = ItemData("metal",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::energy = ItemData("energy",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::rare_materials = ItemData("rare_materials",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::crude_oil = ItemData("crude_oil",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::industry = ItemData("industry",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::anti_air = ItemData("anti_air",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::naval_base = ItemData("naval_base",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::air_base = ItemData("air_base",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::manpower = ItemData("manpower",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::leadership = ItemData("leadership",QVariant(QVariant::Double));
const ItemData ProvinceItemPrototypeRepository::land_fort = ItemData("land_fort",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::coastal_fort = ItemData("coastal_fort",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::nuclear_reactor = ItemData("nuclear_reactor",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::radar_station = ItemData("radar_station",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::rocket_test = ItemData("rocket_test",QVariant(QVariant::Int));
const ItemData ProvinceItemPrototypeRepository::add_core = ItemData("add_core",QVariant(QStringList()));


void ProvinceItemPrototypeRepository::Init()
{
	m_PrototypeMap.clear();
	m_PrototypeMap.insert( owner.GetName(), owner );
	m_PrototypeMap.insert( controller.GetName(), controller );
	m_PrototypeMap.insert( add_core.GetName(), add_core );
	m_PrototypeMap.insert( infra.GetName(), infra );
	m_PrototypeMap.insert( points.GetName(), points );
	m_PrototypeMap.insert( metal.GetName(), metal );
	m_PrototypeMap.insert( energy.GetName(), energy );
	m_PrototypeMap.insert( rare_materials.GetName(), rare_materials );
	m_PrototypeMap.insert( crude_oil.GetName(), crude_oil );
	m_PrototypeMap.insert( industry.GetName(), industry );
	m_PrototypeMap.insert( anti_air.GetName(), anti_air );
	m_PrototypeMap.insert( naval_base.GetName(), naval_base );
	m_PrototypeMap.insert( air_base.GetName(), air_base );
	m_PrototypeMap.insert( manpower.GetName(), manpower );
	m_PrototypeMap.insert( leadership.GetName(), leadership );
	m_PrototypeMap.insert( land_fort.GetName(), land_fort );
	m_PrototypeMap.insert( coastal_fort.GetName(), coastal_fort );
	m_PrototypeMap.insert( nuclear_reactor.GetName(), nuclear_reactor );
	m_PrototypeMap.insert( radar_station.GetName(), radar_station );
	m_PrototypeMap.insert( rocket_test.GetName(), rocket_test );
}

ProvinceItem* ProvinceItemPrototypeRepository::CreateProvinceItem( int id, const QString& name, const QColor& color ) const
{
	ProvinceItem *newItem = new ProvinceItem( id, name, color );
	InitWithAllPrototypes(*newItem);
	return newItem;
}
