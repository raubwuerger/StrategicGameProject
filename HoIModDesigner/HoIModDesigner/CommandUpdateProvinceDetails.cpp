#include "stdafx.h"
#include "CommandUpdateProvinceDetails.h"

#include "DialogProvinceDetails.h"
#include "ProvinceItem.h"

CommandUpdateProvinceDetails::CommandUpdateProvinceDetails( ProvinceItem *provinceItem )
	: Command("CommandUpdateProvinceDetails"),
	m_ProvinceItem(provinceItem)
{

}

CommandUpdateProvinceDetails::~CommandUpdateProvinceDetails()
{

}

bool CommandUpdateProvinceDetails::DoExecute()
{
	if( m_ProvinceItem == nullptr )
	{
		return false;
	}
		
	DialogProvinceDetails dialog;
	dialog.SetProvinceItem(m_ProvinceItem);
	if( dialog.exec() != QDialog::Accepted )
	{
		return false;
	}
	dialog.UpdateProvinceItem(m_ProvinceItem);
	m_ProvinceItem->SetContentChanged(true);
	return true;
}
