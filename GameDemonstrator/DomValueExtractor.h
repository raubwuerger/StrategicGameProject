#pragma once

class QDomNode;
class QDomElement;

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
