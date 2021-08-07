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
private:
	bool ExtractElement( const QString& elementName, QDomElement& element ) const;

private:
	const QDomNode& DomNode;
};

#endif