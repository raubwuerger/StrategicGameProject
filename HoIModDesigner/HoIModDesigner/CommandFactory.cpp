#include "stdafx.h"
#include "CommandFactory.h"
#include "CommandUpdateProvinceDetails.h"
#include "CommandUpdateProvinceOwner.h"
#include "CommandUpdateProvinceItem.h"

jha::Command* CommandFactory::CreateCommandUpdateProvinceDetails( ProvinceItem *provinceItem )
{
	return new CommandUpdateProvinceDetails(provinceItem);
}

jha::Command* CommandFactory::CreateCommandUpdateProvinceOwner( ProvinceItem *provinceItem, const QString& newOwner )
{
	return new CommandUpdateProvinceOwner(provinceItem,newOwner);
}

jha::Command* CommandFactory::CreateCommandUpdateProvinceItem( ProvinceItem *provinceItem, const ItemData& item )
{
	return new CommandUpdateProvinceItem(provinceItem,item);
}
