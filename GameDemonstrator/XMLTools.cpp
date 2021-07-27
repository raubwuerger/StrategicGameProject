#include "stdafx.h"
#include "XMLTools.h"
#include <QDomNode>
#include "LogInterface.h"

/************************************************************************/
/* CDomElementFinder                                                    */
/************************************************************************/
DomElementFinder::DomElementFinder( const QDomNode& node ) 
	: theNode(node)
{

}

void DomElementFinder::TryFindElement( const QString& elementName, int& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text().toInt();
}

void DomElementFinder::TryFindElement( const QString& elementName, QString& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text();
}

void DomElementFinder::TryFindElement( const QString& elementName, QColor& value ) const
{
	QDomElement element;
	if( ValidateNode(elementName,element) == false )
	{
		return;
	}
	value = element.text();
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
