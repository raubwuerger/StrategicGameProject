#include "stdafx.h"
#include "DomNodeListValueExtractor.h"
#include "DomValueExtractor.h"
#include <QDomNodeList>
#include "LogInterface.h"


DomNodeListValueExtractor::DomNodeListValueExtractor( const QDomNodeList& domNodeList )
	: DomNodeList(domNodeList)
{

}

bool DomNodeListValueExtractor::ExtractValue( const QString& valueName, QString& value )
{
	for( int currentDomNodeIndex = 0; currentDomNodeIndex < DomNodeList.size(); currentDomNodeIndex++ )
	{
		DomValueExtractor domValueExtractor(DomNodeList.at(currentDomNodeIndex));
		if( false == domValueExtractor.ExtractValue(valueName,value) )
		{
			continue;
		}
		return true;
	}
	return false;
}

bool DomNodeListValueExtractor::ExtractValue( const QString& valueName, QColor& value )
{
	for( int currentDomNodeIndex = 0; currentDomNodeIndex < DomNodeList.size(); currentDomNodeIndex++ )
	{
		DomValueExtractor domValueExtractor(DomNodeList.at(currentDomNodeIndex));
		if( false == domValueExtractor.ExtractValue(valueName,value) )
		{
			continue;
		}
		return true;
	}
	return false;
}

bool DomNodeListValueExtractor::ExtractValue( const QString& valueName, int& value )
{
	for( int currentDomNodeIndex = 0; currentDomNodeIndex < DomNodeList.size(); currentDomNodeIndex++ )
	{
		DomValueExtractor domValueExtractor(DomNodeList.at(currentDomNodeIndex));
		if( false == domValueExtractor.ExtractValue(valueName,value) )
		{
			continue;
		}
		return true;
	}
	return false;
}

bool DomNodeListValueExtractor::ValidateInput( const QString& valueName )
{
	if( true == valueName.isEmpty() )
	{
		jha::GetLog()->Log_MESSAGE( QObject::tr("Handover parameter <valueName> is empty!") );
		return false;
	}
	return true;
}
