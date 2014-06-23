#pragma once
#include <QString>
#include "std/Command.h"

namespace jha
{

class CommandProvinceItem : public Command
{
public:
/** Constructor */
	CommandProvinceItem();
/** */
	virtual ~CommandProvinceItem();
private:
/**  */
	virtual bool DoExecute();
};

}