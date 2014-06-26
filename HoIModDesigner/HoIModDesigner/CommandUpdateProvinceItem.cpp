#include "stdafx.h"
#include "CommandUpdateProvinceItem.h"

CommandUpdateProvinceItem::CommandUpdateProvinceItem( ProvinceItem *provinceItem, const ItemData& newValue )
	: Command("CommandUpdateProvinceItem"),
	m_ProvinceItem(provinceItem),
	m_NewValue(newValue)
{

}

CommandUpdateProvinceItem::~CommandUpdateProvinceItem()
{

}

bool CommandUpdateProvinceItem::DoExecute()
{
	if( m_ProvinceItem == nullptr )
	{
		return false;
	}
//TODO: Wofür soll das gut sein? Muss initialisiert sein ... sonst ist vorher schon was falsch gelaufen
// 	if( m_ProvinceItem->FindItem(m_NewValue.GetName()).GetData().isNull() == true )
// 	{
// 		return false;
// 	}

	m_OrgValue = m_ProvinceItem->FindItem( m_NewValue.GetName() );
	if( m_OrgValue.GetData().type() == QVariant::Int )
	{
		m_NewValue.SetData( m_OrgValue.GetData().toInt() + 1 );
	}
	if( m_OrgValue.GetData().type() == QVariant::Double )
	{
		m_NewValue.SetData( m_OrgValue.GetData().toDouble() + 1.0 );
	}
	if( m_OrgValue.GetData().type() == QVariant::String )
	{
		m_NewValue.SetData( "GER" );
	}
	m_ProvinceItem->UpdateItem( m_NewValue.GetName(), m_NewValue.GetData() );
	m_ProvinceItem->SetContentChanged(true);
	return true;
}

bool CommandUpdateProvinceItem::DoUndo()
{
	if( m_OrgValue.IsNull() == true )
	{
		return false;
	}
	m_ProvinceItem->UpdateItem( m_NewValue.GetName(), m_OrgValue.GetData() );
	//TODO: Ist nicht immer richtig! Wenn zwischen Execute und Undo ein anderes Command ausgeführt wird zum Beispiel!
	m_ProvinceItem->SetContentChanged(false);

	return true;
}
