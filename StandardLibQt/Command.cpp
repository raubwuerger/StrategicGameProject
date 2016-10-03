#include "stdafx.h"
#include "Command.h"
#include "LogInterface.h"

namespace jha
{
	Command::Command( const QString& name )
		: Name(name)
	{

	}

	Command::~Command()
	{

	}

	bool Command::Execute()
	{
		return DoExecute();
	}

	const QString& Command::GetName() const
	{
		return Name;
	}

	bool Command::DoUndo()
	{
		GetLog()->Log( "DoUndo not implemented: " +Name, jha::LOGLEVEL::LL_WARNING );
		return false;
	}

	bool Command::Undo()
	{
		return DoUndo();
	}

	bool Command::operator==( const Command& rhs ) const
	{
		return this == &rhs;
	}

}