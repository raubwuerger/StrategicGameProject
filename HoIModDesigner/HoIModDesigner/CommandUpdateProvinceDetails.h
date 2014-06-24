#pragma once
#include <QString>
#include "std/Command.h"
class ProvinceItem;

class CommandUpdateProvinceDetails : public jha::Command
{
public:
/** Constructor */
	CommandUpdateProvinceDetails( ProvinceItem *provinceItem );
/** */
	virtual ~CommandUpdateProvinceDetails();
private:
/**  */
	virtual bool DoExecute();
private:
	ProvinceItem	*m_ProvinceItem;
};
