#include "stdafx.h"
#include "DateTime.h"
#include <time.h>
#include <chrono>

namespace jha
{

Time::Time()
{
}

Time::Time( const Time& rhs )
	: m_CurrentTime(rhs.m_CurrentTime)
{
}

Time::~Time()
{
}

std::string Time::TimeToString() const
{
	__int64 millisekunden = std::chrono::duration_cast<std::chrono::milliseconds>(m_CurrentTime.time_since_epoch()).count() - std::chrono::duration_cast<std::chrono::seconds>(m_CurrentTime.time_since_epoch()).count() * 1000;
	time_t tt = std::chrono::system_clock::to_time_t(m_CurrentTime);
	tm local_tm;
	errno_t error = localtime_s(&local_tm,&tt);
	//TODO: Bei Fehler hier exception werfen
	return FillFront(std::to_string(local_tm.tm_hour),4) +":" +FillFront(std::to_string(local_tm.tm_min),2) +":" +FillFront(std::to_string(local_tm.tm_sec),2) +"." +FillFront(std::to_string(millisekunden),3);
}

std::string Time::DateToString() const
{
	time_t tt = std::chrono::system_clock::to_time_t(m_CurrentTime);
	tm local_tm;
	errno_t error = localtime_s(&local_tm,&tt);
	//TODO: Bei Fehler hier exception werfen
	return FillFront(std::to_string(local_tm.tm_year),4) +"-" +FillFront(std::to_string(local_tm.tm_mon),2) +"-" +FillFront(std::to_string(local_tm.tm_mday),2);
}

std::string Time::DateTimeToString() const
{
	return DateToString() +" " +TimeToString();
}

void Time::FetchCurrentDateTime()
{
	m_CurrentTime = std::chrono::system_clock::now();
}

std::string Time::FillFront( const std::string& source, size_t length, const std::string& filler ) const
{
	if( filler.empty() == true )
	{
		return source;
	}
	std::string tmp(source);
	while( tmp.size() < length )
	{
		tmp.insert(0,filler);
	}
	return tmp;
}

}
