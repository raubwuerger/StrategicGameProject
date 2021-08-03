#include "stdafx.h"
#include "MapCreatorSaveGame.h"
#include <QtXml>
#include "SerializeXMLItems.h"
#include "LogInterface.h"
#include "DomNodeFinder.h"
#include "DomValueExtractor.h"
#include "ModelTerrainTypeRepository.h"
#include "ModelMapItem.h"

MapCreatorSaveGame::MapCreatorSaveGame( const QDomNode mapElements )
	: Rows(-1), Cols(-1)
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

	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::ROWS, Rows ) )
		{
			return false;
		}
	}

	{
		DomValueExtractor domNodeListValueExtractor( settings );
		if( false == domNodeListValueExtractor.ExtractValue( SerializeXMLItems::COLS, Cols ) )
		{
			return false;
		}
	}

	return true;
}

bool MapCreatorSaveGame::CreateMapItems(const QDomNode &mapItems)
{
	return true;
/*	QDomNodeList mapItemNodeList = mapItems.childNodes();
	if( true == mapItemNodeList.isEmpty() )
	{
		jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child elements") );
		return false;
	}

	const ModelTerrainType* defaultTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();

	QVector< QVector<ModelMapItem*> >* theCreatedMap = new QVector< QVector<ModelMapItem*> >();
	theCreatedMap->reserve(Rows);
	for( unsigned int currentRow = 0; currentRow < Rows; currentRow++ )
	{
		QVector<ModelMapItem*> tempRow;
		tempRow.reserve(Cols);
		for( unsigned int currentCol = 0; currentCol < Cols; currentCol++ )
		{
			ModelMapItem* modelMapItem = new ModelMapItem(currentRow,currentCol,++MapItemId);
			modelMapItem->SetModelTerrainType( defaultTerrainType );
			tempRow.append( modelMapItem );
		}
		theCreatedMap->append(tempRow);
	}

	ModelMapRepository::GetInstance()->SetMapItems( theCreatedMap );

	for( int currentDomNode = 0; currentDomNode < mapItemNodeList.size(); currentDomNode++ )
	{
		if( mapItemNodeList.at(currentDomNode).nodeName() != SerializeXMLItems::MAPITEM )
		{
			continue;
		}
		return true;
	}

	jha::GetLog()->Log_WARNING( QObject::tr("QDomNodeList has no child element with name: %1").arg(SerializeXMLItems::MAPITEM) );
	return false;*/
}

ModelMapItem* MapCreatorSaveGame::CreateFromXML(const QDomNode& node)
{
	return nullptr;
}

/*
MapItemId = 0;
unsigned int cols = ModelMapConfig::GetInstance()->Cols;
unsigned int rows = ModelMapConfig::GetInstance()->Rows;

const ModelTerrainType* defaultTerrainType = ModelTerrainTypeRepository::GetInstance()->GetDefaultTerrainType();

QVector< QVector<ModelMapItem*> >* theCreatedMap = new QVector< QVector<ModelMapItem*> >();
theCreatedMap->reserve(rows);
for( unsigned int currentRow = 0; currentRow < rows; currentRow++ )
{
QVector<ModelMapItem*> tempRow;
tempRow.reserve(cols);
for( unsigned int currentCol = 0; currentCol < cols; currentCol++ )
{
ModelMapItem* modelMapItem = new ModelMapItem(currentRow,currentCol,++MapItemId);
modelMapItem->SetModelTerrainType( defaultTerrainType );
tempRow.append( modelMapItem );
}
theCreatedMap->append(tempRow);
}

ModelMapRepository::GetInstance()->SetMapItems( theCreatedMap );
return true;
*/


