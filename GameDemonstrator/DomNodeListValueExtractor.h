#pragma once

class QDomNodeList;

//================================================================================
class DomNodeListValueExtractor
{
public:
/** */
	DomNodeListValueExtractor( const QDomNodeList& domNodeList );
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
	const QDomNodeList& DomNodeList;
};
