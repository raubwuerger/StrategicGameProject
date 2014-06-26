#include "stdafx.h"
#include "ItemTypeBase.h"
#include "std/LogInterface.h"

//================================================================================
ItemData::ItemData()
	: m_ValueActive(false)
{

}

ItemData::ItemData( const QString& name, const QVariant& data )
	: m_Name(name),
	m_Data(data)
{
	m_ValueActive = data.isValid();
}

ItemData::ItemData( const QString& name )
	: m_Name(name),
	m_ValueActive(false)
{
}

const QString& ItemData::GetName() const
{
	return m_Name;
}

void ItemData::SetName( const QString& val )
{
	m_Name = val;
}

const QVariant& ItemData::GetData() const
{
	return m_Data;
}

void ItemData::SetData( const QVariant& val )
{
	m_ValueActive = true;
	m_Data = val;
}

bool ItemData::GetValueActive() const
{
	return m_ValueActive;
}

bool ItemData::IsNull() const
{
	return m_Name.isEmpty() && m_Data.isNull();
}

//================================================================================
ItemTypeBase::ItemTypeBase( const QString& id ) 
	: m_ItemID(id)
{

}

const QString& ItemTypeBase::GetItemID() const
{
	return m_ItemID;
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
	if( iter == m_Items.end() )
	{
		return ItemData();
	}
	return (*iter);
}

bool ItemTypeBase::UpdateItem( const QString& key, const QVariant& data )
{
	QMap<QString,ItemData>::Iterator iter = m_Items.find(key);
	if( iter == m_Items.end() )
	{
		return false;
	}

	QVariant dataVariant(data);
	if( dataVariant.convert(iter->GetData().type() ) == false )
	{
		return false;
	}

	if( iter->GetData().type() == QVariant::StringList )
	{
		QStringList old = iter->GetData().toStringList();
		QStringList append = dataVariant.toStringList();
		old.append( append );
		iter->SetData(old);
	}
	else
	{
		iter->SetData(dataVariant);
	}

	return true;
}

bool ItemTypeBase::SetItem( const QString& key, const QVariant& data )
{
	QMap<QString,ItemData>::Iterator iter = m_Items.find(key);
	if( iter == m_Items.end() )
	{
		return false;
	}

	QVariant dataVariant(data);
	if( dataVariant.convert(iter->GetData().type() ) == false )
	{
		return false;
	}

	iter->SetData(data);
	return true;
}

//================================================================================

QMap<QString,ItemData> ItemPrototypeRepository::m_PrototypeMap;

ItemData ItemPrototypeRepository::CreateItemData( const QString& name, const QString& data ) const
{
	QMap<QString,ItemData>::ConstIterator foundPrototype = m_PrototypeMap.constFind(name);
	if( foundPrototype == m_PrototypeMap.constEnd() )
	{
		jha::GetLog()->Log( "Item not defined: " +name, LEVEL::LL_WARNING );
		return ItemData(name,"???");
	}

	QVariant dataVariant(data);
	if( dataVariant.convert(foundPrototype->GetData().type() ) == false )
	{
		jha::GetLog()->Log( "Data type invalid: " +data, LEVEL::LL_WARNING );
		return ItemData(name,"???");
	}

	return ItemData( name, dataVariant );
}

void ItemPrototypeRepository::InitWithAllPrototypes( ItemTypeBase& baseType ) const
{
	QMap<QString,ItemData>::ConstIterator iter;
	for( iter = m_PrototypeMap.constBegin(); iter != m_PrototypeMap.constEnd(); iter++ )
	{
		baseType.AppendItemData( iter->GetName(), ItemData(iter->GetName(), iter->GetData()) );
	}
}

