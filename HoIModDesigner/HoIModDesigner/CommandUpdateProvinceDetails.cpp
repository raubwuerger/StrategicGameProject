#include "stdafx.h"
#include "CommandUpdateProvinceDetails.h"

#include "DialogProvinceDetails.h"
#include "HoI3Scriptparser.h"
#include "ParserHoI3.h"
#include "ProvinceItem.h"
#include "ProvinceGraphicsPixmapItem.h"

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

	HoI3Script provinceScript( m_ProvinceItem->m_FilePath );

	QMap<QString,ItemData>::ConstIterator iter;
	for( iter = m_ProvinceItem->GetItemMap().constBegin(); iter != m_ProvinceItem->GetItemMap().constEnd(); iter++ )
	{
		if( iter->GetData().type() == QVariant::StringList )
		{
			QStringList stringList = iter->GetData().toStringList();
			for( int i=0;i<stringList.size();i++ )
			{
				provinceScript.m_TokenList.append( HoI3Token( iter->GetName(), stringList.at(i)) );
			}
		}
		else
		{
			provinceScript.m_TokenList.append( HoI3Token( iter->GetName(), iter->GetData().toString()) );
		}
	}

	HoI3Scriptparser scriptParser;
	scriptParser.SaveScript( provinceScript );
	return true;
}
