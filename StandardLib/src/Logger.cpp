#include "stdafx.h"
#include "Logger.h"

namespace jha
{

Logger::Logger( const std::string& name )
	: m_Name(name)
{
}

const std::string& Logger::Name() const
{
	return m_Name;
}

}