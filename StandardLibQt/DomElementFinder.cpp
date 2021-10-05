#include "stdafx.h"
#include "DomElementFinder.h"
#include <QDomNode>
#include "LogInterface.h"
#include "StringToBoolConverter.h"

/************************************************************************/
/* CDomElementFinder                                                    */
/************************************************************************/
DomElementFinder::DomElementFinder( const QDomNode& node ) 
	: DomNode(node)
{

}

bool DomElementFinder::TryFindElement( const QString& elementName, int& value ) const
{
	QDomElement element;
	if( ExtractElement(elementName,element) == false )
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
	if( ExtractElement(elementName,element) == false )
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
	if( ExtractElement(elementName,element) == false )
	{
		return false;
	}
	value = element.text();
	jha::GetLog()->Log_DEBUG( QObject::tr("Element <%1> found with value: %2 ").arg(elementName).arg(value.name()) );
	return true;
}

bool DomElementFinder::TryFindElement(const QString& elementName, bool& value) const
{
	QDomElement element;
	if (ExtractElement(elementName, element) == false)
	{
		return false;
	}

	bool boolValue;
	StringToBoolConverter stringToBoolConverter;
	if (false == stringToBoolConverter.Convert(element.text(), &boolValue))
	{
		return false;
	}
	value = boolValue;
	jha::GetLog()->Log_DEBUG(QObject::tr("Element <%1> found with value: %2 ").arg(elementName).arg(value));
	return true;
}

bool DomElementFinder::ExtractElement( const QString& elementName, QDomElement& element ) const
{
	element = DomNode.firstChildElement(elementName);
	if( element.isNull() == true )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Element not found: %1").arg(elementName) );
		return false;
	}
	return true;
}
