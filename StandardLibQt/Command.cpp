#include "stdafx.h"
#include "Command.h"
#include "LogInterface.h"

namespace jha
{
	//==============================================================================
	Command::Command( const QString& name )
		: Name(name)
	{
		//QAssert(Name.empty() == true)
	}

	//==============================================================================
	Command::~Command()
	{

	}

	//==============================================================================
	bool Command::Execute()
	{
		return DoExecute();
	}

	//==============================================================================
	const QString& Command::GetName() const
	{
		return Name;
	}

	//==============================================================================
	bool Command::DoUndo()
	{
		GetLog()->Log_WARNING( QObject::tr("DoUndo not implemented: ").arg(Name) );
		return false;
	}

	//==============================================================================
	bool Command::Undo()
	{
		return DoUndo();
	}

	//==============================================================================
	bool Command::operator==( const Command& rhs ) const
	{
		return this == &rhs;
	}

}