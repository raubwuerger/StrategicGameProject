#pragma once
#include <QString>
#include "std\Command.h"

class ProvinceItem;
namespace jha
{
	class Command;
}

class CommandCache
{
public:
/** */
	void AddCommand( jha::Command *command );
/** */
	jha::Command* FindCommand( jha::Command *command );
/** */
	void ClearCommandCache();
private:
	QVector<jha::Command*> m_CommandCache;
};
