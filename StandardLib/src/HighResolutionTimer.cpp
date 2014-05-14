#include "stdafx.h"
#include "HighResolutionTimer.h"
#include "LogInterface.h"


namespace jha
{

const double HighResolutionTimer::MILLISECONDS_PER_SECOND = 1000.0;
const double HighResolutionTimer::MICROSECONDS_PER_SECOND = 1000000.0;

HighResolutionTimer::HighResolutionTimer( bool start )
{
	Clear();
	BOOL highResolution = QueryPerformanceFrequency( &m_Frequency );
	if( highResolution == TRUE )
	{
		jha::log->Log("High resolution timer available [Ticks per second]: " +int(m_Frequency.QuadPart),jha::LogInterface::LL_DEBUG, "planet_gui" );
		if( start )
		{
			Start();
		}
	}
	else
	{
		jha::log->Log("High resolution timer not available!",jha::LogInterface::LL_ERROR, "JHAHighResolutionTimer" );
	}
}

void HighResolutionTimer::Start()
{
	QueryPerformanceCounter(&m_Start);
}

void HighResolutionTimer::Stop()
{
	QueryPerformanceCounter(&m_Stop);
}

void HighResolutionTimer::Clear()
{
	m_Difference = 0;
	m_Start.QuadPart = 0;
	m_Stop.QuadPart = 0;
}

double HighResolutionTimer::GetElapsedTimeSecond() const
{
	return GetElapsedTime();
}

double HighResolutionTimer::GetElapsedTimeMillisecond() const
{
	return GetElapsedTime() * MILLISECONDS_PER_SECOND;
}

double HighResolutionTimer::GetElapsedTimeMicrosecond() const
{
	return GetElapsedTime() * MICROSECONDS_PER_SECOND;
}

double HighResolutionTimer::GetDifferenceTimeSecond() const
{
	double oldValue = m_Difference;
	double newValue = GetElapsedTime();
	return newValue - oldValue;
}

double HighResolutionTimer::GetDifferenceTimeMillisecond() const
{
	return GetDifferenceTimeSecond() * MILLISECONDS_PER_SECOND;
}

double HighResolutionTimer::GetDifferenceTimeMicrosecond() const
{
	return GetDifferenceTimeSecond() * MICROSECONDS_PER_SECOND;
}

double HighResolutionTimer::GetElapsedTime() const
{
	LARGE_INTEGER time;
	if( m_Stop.QuadPart != 0 )
	{
		time.QuadPart = m_Stop.QuadPart - m_Start.QuadPart;
	}
	else
	{
		LARGE_INTEGER temp;
		QueryPerformanceCounter(&temp);
		time.QuadPart = temp.QuadPart - m_Start.QuadPart;
	}
	m_Difference = (double)time.QuadPart /(double)m_Frequency.QuadPart;
	return m_Difference;
}

}