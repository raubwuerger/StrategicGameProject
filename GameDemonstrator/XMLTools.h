#pragma once

class QDomNode;
class QDomElement;

//================================================================================
class CDomElementFinder
{
public:
	/** */
	CDomElementFinder( const QDomNode& node );
	/** */
	void TryFindElement( const QString& elementName, int& value ) const;
	/** */
	void TryFindElement( const QString& elementName, QString& value ) const;
	/** */
	void TryFindElement( const QString& elementName, QColor& value ) const;
private:
	bool ValidateNode( const QString& elementName, QDomElement& element ) const;

private:
	const QDomNode& theNode;
};