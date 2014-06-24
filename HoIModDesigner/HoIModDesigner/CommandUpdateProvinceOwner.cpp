#include "stdafx.h"
#include "CommandUpdateProvinceOwner.h"

#include "HoI3Scriptparser.h"
#include "ParserHoI3.h"
#include "ProvinceItem.h"
#include "ProvinceGraphicsPixmapItem.h"

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

	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::owner.GetName(), m_NewOwner );
	m_ProvinceItem->UpdateItem( ProvinceItemPrototypeRepository::controller.GetName(), m_NewOwner );
		
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
