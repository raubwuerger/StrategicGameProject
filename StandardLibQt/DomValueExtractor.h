#ifndef DomValueExtractor_H
#define DomValueExtractor_H

class QDomNode;
class QDomElement;

/**
	Sucht alle Kindknoten nach dem übergebnen Namen durch und liefert den entsprechenden Text
	<Name>Text</Name>
*/

//================================================================================
class DomValueExtractor
{
public:
/** */
	DomValueExtractor( const QDomNode& domNode );
/** */
	bool ExtractValue( const QString& valueName, QString& value );
/** */
	bool ExtractValue( const QString& valueName, QColor& value );
/** */
	bool ExtractValue( const QString& valueName, int& value );
private:
/** */
	bool ValidateInput( const QString& valueName );
private:
	const QDomNode& DomNode;
};

#endif
