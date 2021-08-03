#include "stdafx.h"
#include "MapCreatorSaveGame.h"
#include <QtXml>
#include "SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"

MapCreatorSaveGame::MapCreatorSaveGame( const QDomNode mapElements )
{
	MapElements = new QDomNode(mapElements);
}

MapCreatorSaveGame::~MapCreatorSaveGame()
{

}

bool MapCreatorSaveGame::CreateMap()
{
	DomNodeFinder domNodeFinder(*MapElements);

	if( false == InitializeMap(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::SETTINGS)) )
	{
		return false;
	}

	if( false == CreateMapItems(domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAPITEMS)) )
	{
		return false;
	}

	return true;
}

ModelMapRepository* MapCreatorSaveGame::GetMap()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool MapCreatorSaveGame::InitializeMap(const QDomNode& settings)
{
	QDomNodeList settingsNodeList = settings.childNodes();
	if( true == settingsNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
		return false;
	}

	for( int i=0;i<settingsNodeList.count();i++)
	{
		QString nodeName = settingsNodeList.at(i).nodeName();
		QString doSomethingDifferent;
	}

	int rows = -1;
	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROWS, rows ) )
		{
			return false;
		}
	}

	int cols = -1;
	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COLS, cols ) )
		{
			return false;
		}
	}

	return true;
}

bool MapCreatorSaveGame::CreateMapItems(const QDomNode &mapItems)
{
	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if( true == mapItemNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
		return false;
	}

	for( int currentDomNode = 0; currentDomNode < mapItemNodeList.size(); currentDomNode++ )
	{
		if( mapItemNodeList.at(currentDomNode).nodeName() != SerializeXMLItems::MAPITEM )
		{
			continue;
		}
		return true;
	}

	jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child element with name: %1").arg(SerializeXMLItems::MAPITEM) );
	return false;
}


