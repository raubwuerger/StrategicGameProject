#pragma once
#include <string>

namespace jha
{

class DoubleHelper
{
public:
	/** Rundet auf x Nachkommastellen (maximal bis 19) */
	double Round( double d, unsigned int pdp ) const;
	/** Prüft ob zwei double gleicht sind */
	bool IsEqual( double a, double b, double epsilon = std::numeric_limits<double>::epsilon() ) const;
	/** Prüft ob zwei double gleicht sind */
	bool IsZero( double a ) const;
	/** Wandelt double in String um */
	std::string ToString( double rhs, int numDigitsAfterPoint =-1 ) const;
};

}