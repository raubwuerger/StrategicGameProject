#pragma once
#include <vector>
#include <string>

namespace jha
{
class LogMessage;

class Logger
{
public:
/** Konstruktor */
	Logger( const std::string& name );
/** */
	virtual bool Init() = 0;
/** */
	virtual bool LogMessage( const std::vector<LogMessage*>& logMessage ) = 0;
/** */
	const std::string& Name() const;
private:
	std::string	m_Name;
};

}