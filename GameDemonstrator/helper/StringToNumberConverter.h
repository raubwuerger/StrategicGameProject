#ifndef STRINGTONUMBERCONVERTER_H
#define STRINGTONUMBERCONVERTER_H

#include <QString>

class StringToNumberConverter
{
public:
	/** */
	static bool Convert(const QString& text, int &converted);
	/** */
	static bool Convert(const QString& text, double &converted);
	/** */
	static bool Convert(const QString& text, float &converted);
};

#endif // STRINGTONUMBERCONVERTER_H