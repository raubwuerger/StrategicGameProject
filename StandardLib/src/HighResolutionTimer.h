#pragma once

#include "windows.h"

namespace jha
{

class HighResolutionTimer
{
public:
/** Constructor */
	HighResolutionTimer( bool start = true );
/** Starts timer */
	void Start();
/** Stopps timer */
	void Stop();
/** Löscht alle Werte */
	void Clear();
/** Liefert die aktuelle */
	double GetElapsedTimeSecond() const;
/** Liefert die aktuelle */
	double GetElapsedTimeMillisecond() const;
/** Liefert die aktuelle */
	double GetElapsedTimeMicrosecond() const;
/** Liefert die aktuelle */
	double GetDifferenceTimeSecond() const;
/** Liefert die aktuelle */
	double GetDifferenceTimeMillisecond() const;
/** Liefert die aktuelle */
	double GetDifferenceTimeMicrosecond() const;
public:
	static const double MILLISECONDS_PER_SECOND;
	static const double MICROSECONDS_PER_SECOND;
private:
/** Liefert die aktuelle */
	double GetElapsedTime() const;
/** */
	double LIToSecs( LARGE_INTEGER & L);
/** Copy constructor restricted */
	HighResolutionTimer( const HighResolutionTimer& rhs );
/** Move constructor restricted */
	HighResolutionTimer( HighResolutionTimer&& rhs );
/** Assignment operator restricted */
	HighResolutionTimer& operator=( const HighResolutionTimer& rhs );
/** Move operator restricted */
	HighResolutionTimer& operator=( HighResolutionTimer&& rhs );
private:
	LARGE_INTEGER m_Frequency;
	mutable LARGE_INTEGER m_Start;
	mutable LARGE_INTEGER m_Stop;
	mutable double m_Difference;
};

}