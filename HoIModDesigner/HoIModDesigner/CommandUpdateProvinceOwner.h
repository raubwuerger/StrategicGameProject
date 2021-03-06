#pragma once
#include <QString>
#include "std/Command.h"
class ProvinceItem;

class CommandUpdateProvinceOwner : public jha::Command
{
public:
/** Constructor */
	CommandUpdateProvinceOwner( ProvinceItem *provinceItem, const QString& owner );
/** */
	virtual ~CommandUpdateProvinceOwner();
private:
/**  */
	virtual bool DoExecute();
/** */
	virtual bool DoUndo();
private:
	ProvinceItem	*m_ProvinceItem;
	QString			m_NewOwner;
	QString			m_OrgOwner;
	QString			m_OrgController;
};
