#pragma once

#include <string>
#include <chrono>

namespace jha
{

class Time
{
public:
/** Constructor */
	Time();
/** Copy Constructor */
	Time( const Time& time );
/** Constructor */
	~Time();
/** Holt aktuelle Lokale Zeit */
	void FetchCurrentDateTime();
/** */
	std::string TimeToString() const;
/** */
	std::string DateToString() const;
/** */
	std::string DateTimeToString() const;
private:
/** */
	std::string FillFront( const std::string& source, size_t length, const std::string& filler = "0"  ) const;
private:
	std::chrono::time_point<std::chrono::system_clock>	m_CurrentTime;
};

}