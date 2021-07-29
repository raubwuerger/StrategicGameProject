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
	jha::GetLog()->Log_DEBUG( QObject::tr("Element <%1> found with value: %2 ").arg(elementName).arg(QString::number(value)) );
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
	jha::GetLog()->Log_DEBUG( QObject::tr("Element <%1> found with value: %2 ").arg(elementName).arg(value) );
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
	jha::GetLog()->Log_DEBUG( QObject::tr("Element <%1> found with value: %2 ").arg(elementName).arg(value.name()) );
	return true;
}

bool DomElementFinder::ValidateNode( const QString& elementName, QDomElement& element ) const
{
	element = theNode.firstChildElement(elementName);
	if( element.isNull() == true )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Element not found: %1").arg(elementName) );
		return false;
	}
	return true;
}
