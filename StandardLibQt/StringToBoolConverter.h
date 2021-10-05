#ifndef STRINGTOBOOLCONVERTER_H
#define STRINGTOBOOLCONVERTER_H

class StringToBoolConverter
{
public:
	/** */
	bool Convert(const QString& text, bool* value) const;
private:
	/** Can find following values:
	*   0, "false", "nok" -> false
	*	1, "true", "ok"  -> true
	*/
	bool DoConvert(const QString& text, bool* value) const;
	/** */
	bool IsInteger(const QString& text) const;
	/** */
	bool ConvertBooleanFromString(const QString& text, bool* value) const;
	/** */
	bool ConvertBooleanFromInteger(const QString& text, bool* value) const;
};

#endif // STRINGTOBOOLCONVERTER_H