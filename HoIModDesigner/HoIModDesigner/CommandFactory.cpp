#include "stdafx.h"
#include "CommandFactory.h"
#include "CommandUpdateProvinceDetails.h"
#include "CommandUpdateProvinceOwner.h"

jha::Command* CommandFactory::CreateCommandUpdateProvinceDetails( ProvinceItem *provinceItem )
{
	return new CommandUpdateProvinceDetails(provinceItem);
}

jha::Command* CommandFactory::CreateCommandUpdateProvinceOwner( ProvinceItem *provinceItem, const QString& newOwner )
{
	return new CommandUpdateProvinceOwner(provinceItem,newOwner);
}
