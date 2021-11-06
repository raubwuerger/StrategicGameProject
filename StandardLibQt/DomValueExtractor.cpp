#include "stdafx.h"
#include "DomValueExtractor.h"
#include "DomElementFinder.h"
#include <QDomNode>
#include "LogInterface.h"


DomValueExtractor::DomValueExtractor( const QDomNode& domNode )
	: DomNode(domNode)
{

}

bool DomValueExtractor::ExtractValue( const QString& valueName, QString& value )
{
	if( false == ValidateInput(valueName) )
	{
		return false;
	}

	DomElementFinder finder(DomNode);
	if( false == finder.TryFindElement( valueName, value ) )
	{
		return false;
	}

	jha::GetLog()->Log_DEBUG( QObject::tr("XML element (QString) found %1 with value: %2 ").arg(valueName).arg(value) );
	return true;
}

bool DomValueExtractor::ExtractValue( const QString& valueName, QColor& value )
{
	if( false == ValidateInput(valueName) )
	{
		return false;
	}

	DomElementFinder finder(DomNode);
	if( false == finder.TryFindElement( valueName, value ) )
	{
		return false;
	}

	jha::GetLog()->Log_DEBUG( QObject::tr("XML element (QColor) found %1 with value: %2 ").arg(valueName).arg(value.name()) );
	return true;
}

bool DomValueExtractor::ExtractValue( const QString& valueName, int& value )
{
	if( false == ValidateInput(valueName) )
	{
		return false;
	}

	DomElementFinder finder(DomNode);
	if( false == finder.TryFindElement( valueName, value ) )
	{
		return false;
	}

	jha::GetLog()->Log_DEBUG( QObject::tr("XML element (int) found %1 with value: %2 ").arg(valueName).arg(QString::number(value)) );
	return true;
}

bool DomValueExtractor::ExtractValue(const QString& valueName, bool& value)
{
	if (false == ValidateInput(valueName))
	{
		return false;
	}

	DomElementFinder finder(DomNode);
	if (false == finder.TryFindElement(valueName, value))
	{
		return false;
	}

	jha::GetLog()->Log_DEBUG(QObject::tr("XML element (bool) found %1 with value: %2 ").arg(valueName).arg(QString::number(value)));
	return true;
}

bool DomValueExtractor::ExtractValue(const QString& valueName, double& value)
{
	if (false == ValidateInput(valueName))
	{
		return false;
	}

	DomElementFinder finder(DomNode);
	if (false == finder.TryFindElement(valueName, value))
	{
		return false;
	}

	jha::GetLog()->Log_DEBUG(QObject::tr("XML element (double) found %1 with value: %2 ").arg(valueName).arg(QString::number(value)));
	return true;
}

bool DomValueExtractor::ValidateInput( const QString& valueName )
{
	if( true == valueName.isEmpty() )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Handover parameter <valueName> is empty!") );
		return false;
	}
	return true;
}
