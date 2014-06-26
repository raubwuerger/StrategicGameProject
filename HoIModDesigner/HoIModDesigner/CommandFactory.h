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

#include "ItemTypeBase.h"
class CommandFactoryProvincePainter
{
public:
	CommandFactoryProvincePainter( const ItemData& item )
		: m_ItemData(item)
	{
	}
	/** */
	jha::Command* CreateCommandProvincePainter( ProvinceItem *provinceItem )
	{
		return CommandFactory().CreateCommandUpdateProvinceItem( provinceItem, m_ItemData );
	}

private:
	ItemData	m_ItemData;
};