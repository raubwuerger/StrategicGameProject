#pragma once
#include <string>

namespace jha
{

class LogLevel
{
public:
/** Konstruktor */
	LogLevel( const LogLevel& rhs );
/** Copy operator */
	LogLevel& operator=( const LogLevel& rhs );
/** Move operator */
	LogLevel& operator=( LogLevel&& rhs );
/** Destructor */
	~LogLevel();
/** Equals operator */
	int operator==( const LogLevel& rhs ) const;
/** Lesser than operator */
	int operator<( const LogLevel& rhs ) const;
/** Liefert Namen */
	const std::string& GetName() const;
/** Liefert LogFilePrefix */
	const std::string& GetLogFilePrefix() const;
/** Liefert MessageBoxType */
	UINT GetMessageBoxType() const;
/** Liefert Farbe */
	COLORREF GetColor() const;
private:
	friend class LogInterface;
/** Default constructor restricted */
	LogLevel();
/** Move Konstruktor restricted */
	LogLevel( LogLevel&& rhs );
/** */
	LogLevel( const std::string& name, const std::string& prefix, UINT messageBoxType, COLORREF color );
private:
	std::string			m_Name;
	std::string			m_LogFilePrefix;
	UINT				m_MessageBoxType;
	COLORREF			m_Color;
};

}