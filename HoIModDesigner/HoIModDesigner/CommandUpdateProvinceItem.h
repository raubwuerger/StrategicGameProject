#pragma once
#include <QString>
#include "std/Command.h"
#include "ProvinceItem.h"

class CommandUpdateProvinceItem : public jha::Command
{
public:
/** Constructor */
	CommandUpdateProvinceItem( ProvinceItem *provinceItem, const ItemData& newValue );
/** */
	virtual ~CommandUpdateProvinceItem();
private:
/**  */
	virtual bool DoExecute();
/** */
	virtual bool DoUndo();
private:
	ProvinceItem	*m_ProvinceItem;
	ItemData		m_OrgValue;
	ItemData		m_NewValue;
};
