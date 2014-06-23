#include "stdafx.h"
#include "Command.h"

namespace jha
{
	Command::Command( const QString& name )
		: m_Name(name)
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
		return m_Name;
	}

}