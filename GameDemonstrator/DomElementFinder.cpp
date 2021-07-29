#include "stdafx.h"
#include "DomElementFinder.h"
#include <QDomNode>
#include "LogInterface.h"

/************************************************************************/
/* CDomElementFinder                                                    */
/************************************************************************/
DomElementFinder::DomElementFinder( const QDomNode& node ) 
	: theNode(node)
{

}

bool DomElementFinder::TryFindElement( const QString& elementName, int& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return false;
	}
	value = element.text().toInt();
	return true;
}

bool DomElementFinder::TryFindElement( const QString& elementName, QString& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return false;
	}
	value = element.text();
	return true;
}

bool DomElementFinder::TryFindElement( const QString& elementName, QColor& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return false;
	}
	value = element.text();
	return true;
}

bool DomElementFinder::ValidateNode( const QString& elementName, QDomElement& element ) const
{
	element = theNode.firstChildElement(elementName);
	if( element.isNull() == true )
	{
		jha::GetLog()->Log("Element missing: " +elementName, LEVEL::LL_WARNING );
		return false;
	}
	return true;
}
