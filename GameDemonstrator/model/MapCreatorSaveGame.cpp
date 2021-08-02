#include "stdafx.h"
#include "MapCreatorSaveGame.h"
#include <QtXml>
#include "SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeListValueExtractor.h"
#include "DomNodeFinder.h"

MapCreatorSaveGame::MapCreatorSaveGame( const QDomNode& mapElements )
	: MapElements(mapElements)
{
}

MapCreatorSaveGame::~MapCreatorSaveGame()
{

}

bool MapCreatorSaveGame::CreateMap()
{
	DomNodeFinder domNodeFinder(MapElements);

	if( false == InitializeMap(MapElements) )
//	if( false == InitializeMap(domNodeFinder.FindDomeNodeByNameClone(SerializeXMLItems::SETTINGS)) )
	{
		return false;
	}

	const QDomNode *mapItems = domNodeFinder.FindDomeNodeByName(SerializeXMLItems::MAPITEMS);
	if( nullptr == mapItems )
	{
		return false;
	}

	if( false == CreateMapItems(mapItems) )
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

	int rows = -1;
	{
		DomNodeListValueExtractor domNodeListValueExtractor( settings.childNodes() );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROWS, rows ) )
		{
			return false;
		}
	}

	int cols = -1;
	{
		DomNodeListValueExtractor domNodeListValueExtractor( settings.childNodes() );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COLS, cols ) )
		{
			return false;
		}
	}

	return true;
}

bool MapCreatorSaveGame::CreateMapItems(const QDomNode *mapItems)
{
	QDomNodeList mapItemNodeList = mapItems->childNodes();
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


