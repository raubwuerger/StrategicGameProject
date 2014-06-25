#pragma once
#include <QString>
#include "std\Command.h"

class ProvinceItem;
class ItemData;

class CommandFactory
{
public:
	/** */
	jha::Command* CreateCommandUpdateProvinceDetails( ProvinceItem *provinceItem );
	/** */
	jha::Command* CreateCommandUpdateProvinceOwner( ProvinceItem *provinceItem, const QString& newOwner );
	/** */
	jha::Command* CreateCommandUpdateProvinceItem( ProvinceItem *provinceItem, const ItemData& item );
};
