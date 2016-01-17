#include "stdafx.h"
#include "XMLTools.h"
#include <QDomNode>
#include "LogInterface.h"

/************************************************************************/
/* CDomElementFinder                                                    */
/************************************************************************/
CDomElementFinder::CDomElementFinder( const QDomNode& node ) 
	: theNode(node)
{

}

void CDomElementFinder::TryFindElement( const QString& elementName, int& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	return;	value = element.text().toInt();
}

void CDomElementFinder::TryFindElement( const QString& elementName, QString& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text();
}

void CDomElementFinder::TryFindElement( const QString& elementName, QColor& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text();
}

bool CDomElementFinder::ValidateNode( const QString& elementName, QDomElement& element ) const
{
	element = theNode.firstChildElement(elementName);
	if( element.isNull() == true )
	{
		jha::GetLog()->Log("Element missing: " +elementName, LEVEL::LL_WARNING );
		return false;
	}
	return true;
}
