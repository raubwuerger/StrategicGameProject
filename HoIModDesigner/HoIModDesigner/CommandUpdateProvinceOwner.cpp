#include "stdafx.h"
#include "CommandUpdateProvinceOwner.h"
#include "ProvinceItem.h"

CommandUpdateProvinceOwner::CommandUpdateProvinceOwner( ProvinceItem *provinceItem, const QString& owner )
	: Command("CommandUpdateProvinceOwner"),
	m_ProvinceItem(provinceItem),
	m_NewOwner(owner)
{

}

CommandUpdateProvinceOwner::~CommandUpdateProvinceOwner()
{

}

bool CommandUpdateProvinceOwner::DoExecute()
{
	if( m_ProvinceItem == nullptr )
	{
		return false;
	}
	if( m_ProvinceItem->FindItem(ProvinceItemPrototypeRepository::owner.GetName()).GetData().isNull() == true )
	{
		return false;
	}

	m_OrgOwner = m_ProvinceItem->FindItem( ProvinceItemPrototypeRepository::owner.GetName() ).GetData().toString();
	m_OrgController = m_ProvinceItem->FindItem( ProvinceItemPrototypeRepository::controller.GetName() ).GetData().toString();

	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::owner.GetName(), m_NewOwner );
	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::controller.GetName(), m_NewOwner );
	m_ProvinceItem->SetContentChanged(true);
	return true;
}

bool CommandUpdateProvinceOwner::DoUndo()
{
	if( m_OrgOwner.isEmpty() == true || m_OrgController.isEmpty() == true )
	{
		return false;
	}
	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::owner.GetName(), m_OrgOwner );
	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::controller.GetName(), m_OrgController );

	return true;
}
