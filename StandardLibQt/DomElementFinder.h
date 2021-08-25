#ifndef DOMELEMENTFINDER_H
#define DOMELEMENTFINDER_H

class QDomNode;
class QDomElement;

//================================================================================
class DomElementFinder
{
public:
	/** */
	DomElementFinder( const QDomNode& node );
	/** */
	bool TryFindElement( const QString& elementName, int& value ) const;
	/** */
	bool TryFindElement( const QString& elementName, QString& value ) const;
	/** */
	bool TryFindElement( const QString& elementName, QColor& value ) const;
	/** */
	bool TryFindElement(const QString& elementName, bool& value) const;
private:
	/** */
	bool ExtractElement( const QString& elementName, QDomElement& element ) const;
	/** Can find following values: 
	*   0, "false", "yes" -> false
	*	1, "true", "no"  -> true
	*/
	bool IsTextBoolean(const QString& text, bool* value) const;
private:
	const QDomNode& DomNode;
};

#endif