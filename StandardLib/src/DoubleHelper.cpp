#include "stdafx.h"
#include "DoubleHelper.h"

namespace jha
{

const double POST_DECIMAL_POSITIONS[20] = { 1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19 };
const double ROUND_UP_FACTOR = 0.5;

double DoubleHelper::Round( double toRound, unsigned int pdp ) const
{
	if( pdp > 19 )
	{
		return toRound;
	}
	return floor(toRound * POST_DECIMAL_POSITIONS[pdp] + ROUND_UP_FACTOR) / POST_DECIMAL_POSITIONS[pdp];
}

bool DoubleHelper::IsEqual( double a, double b, double epsilon ) const
{
	return std::fabs(a - b) < epsilon;
}

bool DoubleHelper::IsZero( double a ) const
{
	return IsEqual( a, 0.0 );
}

std::string DoubleHelper::ToString( double rhs, int numDigitsAfterPoint /*=-1 */ ) const
{
	char buf[64];
	char formatBuf[16] = "%f";
	if(numDigitsAfterPoint >= 0)
	{
		sprintf_s(formatBuf, "%%.%df", numDigitsAfterPoint);
	}
	sprintf_s(buf, formatBuf, rhs);
	return buf;
}

}